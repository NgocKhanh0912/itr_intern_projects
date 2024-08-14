# This Python file uses the following encoding: utf-8
# Important:
# You need to run the following command to generate the ui_dev.py file
#     pyside6-uic dev.ui -o ui_dev.py, or
#     pyside2-uic dev.ui -o ui_dev.py

# And similarly for the user UI:
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py.py

import sys
import serial
import threading
import serial.tools.list_ports
import pyqtgraph as pg
from PySide6.QtWidgets import QApplication, QMainWindow, QStackedWidget, QMessageBox, QVBoxLayout, QWidget
from PySide6.QtWidgets import QPushButton, QGroupBox, QCalendarWidget, QTimeEdit, QLineEdit, QTextEdit
from PySide6.QtCore import Slot, QTimer, QDateTime
from PySide6.QtGui import QIcon
from dev_ui_manage import Widget
from ui_form import Ui_User_UI
from serial_manage import serial_manage

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.stacked_widget = QStackedWidget()
        self.setCentralWidget(self.stacked_widget)

        # Set up the QWidget from dev.ui
        self.dev_widget = Widget(self)

        # Set up the QMainWindow from form.ui
        self.user_ui = QMainWindow()
        self.ui_user = Ui_User_UI()
        self.ui_user.setupUi(self.user_ui)

        # Set the window title for the User UI window
        self.set_window_title("User UI")
        # Load icon
        self.setWindowIcon(QIcon('ice.ico'))

        # Add the dev_widget (dev.ui) and user_ui (form.ui) to the stacked widget
        self.stacked_widget.addWidget(self.dev_widget)
        self.stacked_widget.addWidget(self.user_ui)

        # Set the initial widget to user_ui
        self.stacked_widget.setCurrentWidget(self.user_ui)

        self.base_info = {}
        self.store_base_info(self)
        # Set the window to maximized
        self.showMaximized()

        # Thread
        self.thread_plot_raw_ppg_graph = threading.Thread(target=self.update_raw_ppg_graph, daemon=True)
        self.thread_plot_filtered_ppg_graph = threading.Thread(target=self.update_filtered_ppg_graph, daemon=True)

        # Initialize serial communication
        self.ui_user.cbb_baudrate.setCurrentText("115200")
        self.serial_connection = None
        self.update_available_ports()

        # Connect the buttons to the methods
        self.ui_user.btn_connect_com.clicked.connect(self.toggle_serial_connection)
        self.ui_user.btn_switch_to_dev_ui.clicked.connect(self.show_dev_ui)
        self.ui_user.btn_set_interval.clicked.connect(self.send_interval_code)
        self.ui_user.btn_set_threshold.clicked.connect(self.send_threshold_code)
        self.ui_user.btn_read_record.clicked.connect(self.send_read_record_code)
        self.ui_user.btn_clear_record.clicked.connect(self.send_clear_record_code)
        self.ui_user.btn_clear_graph.clicked.connect(self.clear_heart_rate_graph)
        self.ui_user.btn_check_com.clicked.connect(self.send_check_com_code)

        # Add the heart rate plot to the layout in user.ui
        self.heart_rate_graph = pg.PlotWidget()
        layout_hr = QVBoxLayout(self.ui_user.Heart_rate_graph)
        self.ui_user.Heart_rate_graph.setLayout(layout_hr)
        layout_hr.addWidget(self.heart_rate_graph)

        self.heart_rate_graph.setBackground("w")
        self.heart_rate_graph.setTitle("Heart Rate Graph", color="black", size="10pt")

        styles = {"color": "black", "font-size": "13px"}
        self.heart_rate_graph.setLabel("left", "Heart Rate (bpm)", **styles)
        self.heart_rate_graph.setLabel("bottom", "Time (h)", **styles)
        self.heart_rate_graph.setXRange(0, 24) # X-Axis from 0h to 24h

        # ScatterPlotItem for scatter points
        self.heart_rate_scatter = pg.ScatterPlotItem(size=10, pen=None, brush=(255, 0, 0))
        self.heart_rate_graph.addItem(self.heart_rate_scatter)

        # Data lists for plotting heart rate
        self.heart_rate_time = []
        self.heart_rate_value = []

        # Time data lists for plotting heart rate and displaying record
        self.dayofweek = []
        self.day = []
        self.month = []
        self.year = []
        self.hour = []
        self.minute = []
        self.second = []
        self.records = []
        self.data_value = 0

        # PlotDataItem for lines
        # self.heart_rate_pen = pg.mkPen(color=(0, 0, 255))
        # self.heart_rate_plot_lines = pg.PlotDataItem(pen=self.heart_rate_pen)
        # self.heart_rate_graph.addItem(self.heart_rate_plot_lines)

        # Initialize and start the timer to check for COM port updates
        self.port_check_timer = QTimer(self)
        self.port_check_timer.timeout.connect(self.update_available_ports)
        self.port_check_timer.start(1000)  # Check every 1000 ms (1 second)

        # Initialize and start the timer to plot PPG signal
        self.ppg_graph_index = 0
        self.plot_ppg_timer = QTimer(self)
        self.plot_ppg_timer.timeout.connect(self.update_ppg_graph)
        self.plot_ppg_timer.start(50)

        self.thread_plot_raw_ppg_graph.start()
        self.thread_plot_filtered_ppg_graph.start()

    def store_base_info(self, widget):
        for child in widget.findChildren(QWidget):
            if isinstance(child, QWidget):
                geom = child.geometry()
                font = child.font()
                margins = child.contentsMargins()

                self.base_info[child] = {
                    'geometry': (geom.x(), geom.y(), geom.width(), geom.height()),
                    'font': font.pointSize() * (864/793),
                    'margins': (margins.left(), margins.top(), margins.right(), margins.bottom())
                }

                self.dev_widget.ui_dev.te_mode_12.setStyleSheet(
                    "padding: 1px;"
                )
                self.dev_widget.ui_dev.te_mode_24.setStyleSheet(
                    "padding: 1px;"
                )

    @Slot()
    def reset_scale_element(self, widget):
        for child in widget.findChildren(QWidget):
            if isinstance(child, QWidget) and child in self.base_info:
                base_info = self.base_info[child]

                geom = base_info['geometry']
                font_size = base_info['font']
                margins = base_info['margins']

                child.setGeometry(
                    geom[0],
                    geom[1],
                    geom[2],
                    geom[3]
                )

                font = child.font()
                font.setPointSize(font_size)
                child.setFont(font)

                child.setContentsMargins(
                    margins[0],
                    margins[1],
                    margins[2],
                    margins[3]
                )

                if isinstance(child, (QPushButton, QGroupBox, QCalendarWidget, QTimeEdit, QLineEdit, QTextEdit)):
                    style_sheet = f"font-size: {font_size}px;"
                    child.setStyleSheet(style_sheet)

    @Slot()
    def resizeEvent(self, event):
        self.reset_scale_element(self.dev_widget)
        self.reset_scale_element(self.ui_user.centralwidget)
        self.scale_ui_elements(self.screen().size())
        self.scale_ui_elements(self.size())
        super().resizeEvent(event)

    @Slot()
    def scale_ui_elements(self, size):
        base_width = 1536
        base_height = 864

        screen_width = size.width()
        screen_height = size.height() * (864/793)

        scale_x = screen_width / base_width
        scale_y = screen_height / base_height

        self.scale_widget(self.dev_widget, scale_x, scale_y)
        self.scale_widget(self.ui_user.centralwidget, scale_x, scale_y)

    @Slot()
    def scale_widget(self, widget, scale_x, scale_y):    
        for child in widget.findChildren(QWidget):
            if isinstance(child, QWidget) and child in self.base_info:
                base_info = self.base_info[child]

                geom = base_info['geometry']
                font_size = base_info['font']
                margins = base_info['margins']

                child.setGeometry(
                    geom[0] * scale_x,
                    geom[1] * scale_y,
                    geom[2] * scale_x,
                    geom[3] * scale_y
                )

                font = child.font()
                font.setPointSize(font_size * scale_y)
                child.setFont(font)

                child.setContentsMargins(
                    margins[0] * scale_x,
                    margins[1] * scale_y,
                    margins[2] * scale_x,
                    margins[3] * scale_y
                )

                if isinstance(child, (QPushButton, QGroupBox, QCalendarWidget, QTimeEdit, QLineEdit, QTextEdit)):
                    style_sheet = f"font-size: {font_size}px;"
                    child.setStyleSheet(style_sheet)

    @Slot()
    def set_window_title(self, title):
        self.setWindowTitle(title)

    @Slot()
    def show_dev_ui(self):
        self.stacked_widget.setCurrentWidget(self.dev_widget)
        self.set_window_title("Dev UI")

    @Slot()
    def update_available_ports(self):
        # Update available COM ports
        available_ports = [port.device for port in serial.tools.list_ports.comports()]
        current_ports = [self.ui_user.cbb_com.itemText(i) for i in range(self.ui_user.cbb_com.count())]

        # Update the combobox only if there is a change in available ports
        if set(available_ports) != set(current_ports):
            self.ui_user.cbb_com.clear()
            self.ui_user.cbb_com.addItems(available_ports)

    @Slot()
    def toggle_serial_connection(self):
        if self.serial_connection:
            self.disconnect_serial()
            QMessageBox.information(self, "Disconnection", "Serial port disconnected.")
        else:
            self.connect_serial()

    @Slot()
    def connect_serial(self):
        port = self.ui_user.cbb_com.currentText()
        baudrate = self.ui_user.cbb_baudrate.currentText()

        if port == "":
            QMessageBox.warning(self, "Error", "Serial port not found.")
            return

        try:
            self.serial_connection = serial_manage(port, baudrate)
            self.serial_connection.packet.connect(self.process_serial_packet)
            self.serial_connection.error_message.connect(self.send_error_mess)
            self.serial_connection.start()
            self.ui_user.btn_connect_com.setText("Disconnect")
            QMessageBox.information(self, "Connection", f"Connected to {port} at {baudrate} baudrate.")
        except Exception:
            self.disconnect_serial()
            QMessageBox.warning(self, "Error", f"{port} is used by another software.")

    @Slot()
    def disconnect_serial(self):
        if self.serial_connection:
            self.serial_connection.stop()
            self.serial_connection = None
            self.ui_user.btn_connect_com.setText("Connect")

    @Slot()
    def send_interval_code(self):
        # Send the interval code based on the value in line_set_interval.
        try:
            if not self.serial_connection:
                raise Exception("Serial port not connected.")

            interval_value = int(self.ui_user.line_set_interval.text())

            if interval_value <= 0:
                raise ValueError("Interval value must be a positive integer.")

            # Convert the integer value to an 8-character hex string
            interval_hex = f'{interval_value:08X}'

            # Create the command string by concatenating the start code (0x01), cmd (0x03), hex value, threshold (0xFF) and end code (0x04)
            interval_command = f'0103{interval_hex}FF04'

            # Convert the command string to bytes for sending over serial
            interval_command_bytes = bytes.fromhex(interval_command)

            if self.serial_connection:
                self.serial_connection.send(interval_command_bytes)
                QMessageBox.information(self, "Success", f"Sent: {interval_command}")
            else:
                QMessageBox.warning(self, "Error", "Serial port is not connected.")

        except ValueError:
            QMessageBox.warning(self, "Error", "Invalid interval value. Please enter a valid positive integer.")

        except Exception:
            QMessageBox.warning(self, "Error", "Serial port not connected.")

    @Slot()
    def send_threshold_code(self):
        # Send the threshold code based on the value in line_high_level and line_low_level.
        try:
            if not self.serial_connection:
                raise Exception("Serial port not connected.")

            threshold_high_value = int(self.ui_user.line_high_level.text())
            threshold_low_value = int(self.ui_user.line_low_level.text())

            if (threshold_high_value <= 0) or (threshold_low_value <= 0):
                raise ValueError("Threshold value must be a positive integer.")

            # Convert the integer values to an 2-character hex string
            threshold_high_hex = f'{threshold_high_value:02X}'
            threshold_low_hex = f'{threshold_low_value:02X}'

            # Create the command string by concatenating the start code (0x01), cmd (0x02), hex value, threshold (0xFF) and end code (0x04)
            threshold_command = f'0102FFFF{threshold_high_hex}{threshold_low_hex}FF04'

            # Convert the command string to bytes for sending over serial
            threshold_command_bytes = bytes.fromhex(threshold_command)

            if self.serial_connection:
                self.serial_connection.send(threshold_command_bytes)
                QMessageBox.information(self, "Success", f"Sent: {threshold_command}")
            else:
                QMessageBox.warning(self, "Error", "Serial port is not connected.")

        except ValueError:
            QMessageBox.warning(self, "Error", "Invalid threshold value. Please enter a valid positive integer.")

        except Exception:
            QMessageBox.warning(self, "Error", "Serial port not connected.")

    @Slot()
    def send_check_com_code(self):
        try:
            if not self.serial_connection:
                raise Exception("Serial port not connected.")

            # Create the command string by concatenating the start code (0x01), cmd (0x00), hex value, threshold (0xFF) and end code (0x04)
            check_com_hex_command = '0100FFFFFFFFFF04'
            check_com_command_bytes = bytes.fromhex(check_com_hex_command)

            if self.serial_connection:
                self.serial_connection.send(check_com_command_bytes)
                QMessageBox.information(self, "Success", f"Sent: {check_com_hex_command}")
            else:
                QMessageBox.warning(self, "Error", "Serial port is not connected.")

        except Exception:
            QMessageBox.warning(self, "Error", "Serial port not connected.")

    @Slot()
    def send_read_record_code(self):
        try:
            if not self.serial_connection:
                raise Exception("Serial port not connected.")

            # Create the command string by concatenating the start code (0x01), cmd (0x01), hex value, threshold (0xFF) and end code (0x04)
            read_record_hex_command = '0101FFFFFFF0FF04'
            read_record_command_bytes = bytes.fromhex(read_record_hex_command)

            if self.serial_connection:
                self.serial_connection.send(read_record_command_bytes)
                QMessageBox.information(self, "Success", f"Sent: {read_record_hex_command}")
            else:
                QMessageBox.warning(self, "Error", "Serial port is not connected.")

        except Exception:
            QMessageBox.warning(self, "Error", "Serial port not connected.")

    @Slot()
    def send_clear_record_code(self):
        try:
            if not self.serial_connection:
                raise Exception("Serial port not connected.")

            # Create the command string by concatenating the start code (0x01), cmd (0x05), hex value, threshold (0xFF) and end code (0x04)
            clear_record_hex_command = '0105FFFFFFFFFF04'
            clear_record_command_bytes = bytes.fromhex(clear_record_hex_command)

            if self.serial_connection:
                self.serial_connection.send(clear_record_command_bytes)
                QMessageBox.information(self, "Success", f"Sent: {clear_record_hex_command}")

                # Reset the arrays
                self.dayofweek.clear()
                self.day.clear()
                self.month.clear()
                self.year.clear()
                self.hour.clear()
                self.minute.clear()
                self.second.clear()
                self.records.clear()
                self.heart_rate_time.clear()
                self.heart_rate_value.clear()
                self.ui_user.txt_record.clear()
            else:
                QMessageBox.warning(self, "Error", "Serial port is not connected.")

        except Exception:
            QMessageBox.warning(self, "Error", "Serial port not connected.")

    @Slot()
    def clear_heart_rate_graph(self):
        self.heart_rate_scatter.clear()
        self.heart_rate_graph.clear()

        self.heart_rate_graph.setBackground("w")
        self.heart_rate_graph.setTitle("Heart Rate Graph", color="black", size="10pt")

        styles = {"color": "black", "font-size": "13px"}
        self.heart_rate_graph.setLabel("left", "Heart Rate (bpm)", **styles)
        self.heart_rate_graph.setLabel("bottom", "Time (h)", **styles)

        # self.heart_rate_pen = pg.mkPen(color=(0, 0, 255))  # Blue
        self.heart_rate_graph.setXRange(0, 24) # X-Axis from 0h to 24h

        # ScatterPlotItem for scatter points
        self.heart_rate_scatter = pg.ScatterPlotItem(size=10, pen=None, brush=(255, 0, 0))
        self.heart_rate_graph.addItem(self.heart_rate_scatter)

    @Slot(str)
    def send_error_mess(self, error_message):
        self.disconnect_serial()
        QMessageBox.warning(self, "Error", f"{error_message}")

    @Slot(bytes)
    def process_serial_packet(self, packet):
        if not self.serial_connection:
            return
        try:
            packet = packet.hex().upper()

            if not (packet.startswith("01") and packet.endswith("04")):
                QMessageBox.warning(self, "Error", "Invalid frame of data packet")
                return

            cmd = packet[2:4]
            data_reverse = packet[4:12]
            data = ''.join(reversed([data_reverse[i:i+2] for i in range(0, len(data_reverse), 2)]))
            self.data_value = int(data, 16)
            threshold = packet[12:14]

            if not (threshold in ["FF", "0F", "F0"]):
                QMessageBox.warning(self, "Error", "Invalid threshold byte")
                return

            if not (cmd in ["00", "01", "11", "21", "04", "06"]):
                QMessageBox.warning(self, "Error", "Invalid command")
                return

            if threshold == "0F":
                self.ui_user.line_thre_noti.setText("Heart rate too high")
            elif threshold == "F0":
                self.ui_user.line_thre_noti.setText("Heart rate too low")
            elif threshold == "FF":
                self.ui_user.line_thre_noti.setText("Normal heart rate")

            # Check UART
            if cmd == "00":
                if data == "FFFFFFFF":
                    QMessageBox.information(self, "Success", "UART DONE")
                    return
                else:
                    QMessageBox.warning(self, "Error", "Invalid data")
                    return

            # Plot heart rate
            elif cmd == "01":
                self.update_heart_rate()

            # Plot raw PPG signal
            elif cmd == "11":
                if self.dev_widget.raw_ppg_time:
                    raw_ppg_new_time = self.dev_widget.raw_ppg_time[-1] + 0.01
                else:
                    raw_ppg_new_time = 0

                self.dev_widget.raw_ppg_time.append(raw_ppg_new_time)
                self.dev_widget.raw_ppg_value.append(self.data_value)

                # Keep only the last 500 samples
                if len(self.dev_widget.raw_ppg_time) > 500:
                    self.dev_widget.raw_ppg_time.pop(0)
                    self.dev_widget.raw_ppg_value.pop(0)

            # Plot filtered PPG signal
            elif cmd == "21":
                self.data_value = self.data_value - 1000
                if self.dev_widget.filtered_ppg_time:
                    filtered_ppg_new_time = self.dev_widget.filtered_ppg_time[-1] + 0.01
                else:
                    filtered_ppg_new_time = 0

                self.dev_widget.filtered_ppg_time.append(filtered_ppg_new_time)
                self.dev_widget.filtered_ppg_value.append(self.data_value)

                # Keep only the last 500 samples
                if len(self.dev_widget.filtered_ppg_time) > 500:
                    self.dev_widget.filtered_ppg_time.pop(0)
                    self.dev_widget.filtered_ppg_value.pop(0)

            # Error notification
            elif cmd == "06":
                if data == "FFFFFFFF":
                    self.dev_widget.ui_dev.line_err_noti.setText("Error occurred")
                else:
                    QMessageBox.warning(self, "Error", "Invalid data")
                    return

            # Get epoch time from STM32, convert epoch time to date time for print record            
            elif cmd == "04":
                epoch_value = int(data, 16)
                dt = QDateTime.fromSecsSinceEpoch(epoch_value)

                self.dayofweek.append(dt.date().dayOfWeek() - 1)  # QDate.dayOfWeek(): 1 (Monday) to 7 (Sunday)
                self.day.append(dt.date().day())
                self.month.append(dt.date().month())
                self.year.append(dt.date().year())
                self.hour.append(dt.time().hour())
                self.minute.append(dt.time().minute())
                self.second.append(dt.time().second())
            
        except Exception as e:
            QMessageBox.warning(self, "Error", f"Failed to read serial data: {str(e)}")

    @Slot()
    def update_heart_rate(self):
        if not self.serial_connection:
            return

        if (len(self.hour) >= 1) and (len(self.minute) >= 1) and (len(self.second) >= 1):
            time_in_hours = self.hour[-1] + self.minute[-1] / 60 + self.second[-1] / 3600
        else:
            time_in_hours = 0

        self.heart_rate_time.append(time_in_hours)
        self.heart_rate_value.append(self.data_value)

        if (len(self.day) >= 2) and (len(self.month)) >= 2 and (len(self.year)) >= 2:
            if (self.day[-1] != self.day[-2]) or (self.month[-1] != self.month[-2]) or (self.year[-1] != self.year[-2]):
                self.clear_heart_rate_graph()
                # Clear old data
                self.heart_rate_time = self.heart_rate_time[-1:]
                self.heart_rate_value = self.heart_rate_value[-1:]

        # Update the PlotDataItem
        # self.heart_rate_plot_lines.setData(self.heart_rate_time, self.heart_rate_value)

        # Update the ScatterPlotItem
        self.heart_rate_scatter.setData(self.heart_rate_time, self.heart_rate_value)

        # Print the records from the arrays
        record = f"{self.day[-1]:02}/{self.month[-1]:02}/{self.year[-1]:04} {self.hour[-1]:02}:{self.minute[-1]:02}:{self.second[-1]:02} Heart rate: {self.heart_rate_value[-1]} bpm"
        self.records.append(record)

        # Join records with newline characters and print to txt_record
        records_text = "\n".join(self.records)
        self.ui_user.txt_record.setPlainText(records_text)

        heart_rate_graph_title = f"Heart Rate Graph in {self.day[-1]:02}/{self.month[-1]:02}/{self.year[-1]:04}"
        self.heart_rate_graph.setTitle(heart_rate_graph_title, color="black", size="10pt")

    def update_raw_ppg_graph(self):
        self.dev_widget.raw_ppg_graph.plot(self.dev_widget.raw_ppg_time[0:self.ppg_graph_index], self.dev_widget.raw_ppg_value[0:self.ppg_graph_index], pen=self.dev_widget.raw_ppg_pen, clear=True)
        self.dev_widget.raw_ppg_graph.autoRange()

    def update_filtered_ppg_graph(self):
        self.dev_widget.filtered_ppg_graph.plot(self.dev_widget.filtered_ppg_time[0:self.ppg_graph_index], self.dev_widget.filtered_ppg_value[0:self.ppg_graph_index], pen=self.dev_widget.filtered_ppg_pen, clear=True)
        self.dev_widget.filtered_ppg_graph.autoRange()

    Slot()
    def update_ppg_graph(self):
        if (len(self.dev_widget.raw_ppg_value) != 0) and (len(self.dev_widget.filtered_ppg_value) != 0):
            if (len(self.dev_widget.raw_ppg_value) > self.ppg_graph_index) and (len(self.dev_widget.filtered_ppg_value) > self.ppg_graph_index):
                self.ppg_graph_index += 1
                self.update_raw_ppg_graph()
                self.update_filtered_ppg_graph()
            else:
                self.update_raw_ppg_graph()
                self.update_filtered_ppg_graph()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec())
