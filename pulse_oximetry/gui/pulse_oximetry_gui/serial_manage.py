# This Python file uses the following encoding: utf-8

from PySide6 import QtCore
from PySide6.QtCore import Signal
import serial
import threading

class serial_manage(QtCore.QObject):
    packet = Signal(bytes)
    error_message = Signal(str)

    def __init__(self, port, baudrate):
        super().__init__()

        # Array for store all data
        self.temp_data = bytearray()

        self.port = port
        self.baudrate = baudrate
        self.running = False
        self.thread = threading.Thread(target=self.run, daemon=True)
        self.serial_connection = None

    def start(self):
        if not self.running:
            self.running = True
            self.serial_connection = serial.Serial(self.port, self.baudrate, timeout=1)
            self.thread.start()

    def stop(self):
        self.running = False
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()

    def run(self):
        try:
            while self.running:
                if self.serial_connection.in_waiting > 0:
                    data = self.serial_connection.read(self.serial_connection.in_waiting)
                    self.temp_data.extend(data)
                    exit_outer_loop = False

                    while len(self.temp_data) > 0:
                        while self.temp_data[0] == 0x01:
                            if len(self.temp_data) < 8:
                                exit_outer_loop = True
                                break
                            if self.temp_data[7] == 0x04:
                                self.packet.emit(self.temp_data[:8])
                                self.temp_data = self.temp_data[8:]
                            else:
                                self.temp_data = self.temp_data[1:]
                            if len(self.temp_data) == 0:
                                exit_outer_loop = True
                                break
                        if exit_outer_loop:
                            break

                        while self.temp_data[0] != 0x01:
                            self.temp_data = self.temp_data[1:]
                            if len(self.temp_data) == 0:
                                exit_outer_loop = True
                                break
                            if self.temp_data[0] == 0x01:
                                if len(self.temp_data) < 8:
                                    exit_outer_loop = True
                                    break
                                if self.temp_data[7] == 0x04:
                                    self.packet.emit(self.temp_data[:8])
                                    self.temp_data = self.temp_data[8:]
                                else:
                                    self.temp_data = self.temp_data[1:]
                                if len(self.temp_data) == 0:
                                    exit_outer_loop = True
                                    break
                        if exit_outer_loop:
                            break
        except serial.SerialException:
            self.error_message.emit("Error: COM Port forcibly disconnected")

    def send(self, command_bytes):
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.write(command_bytes)
