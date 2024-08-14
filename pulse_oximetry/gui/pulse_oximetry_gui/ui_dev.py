# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'dev.ui'
##
## Created by: Qt User Interface Compiler version 6.7.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QCalendarWidget, QComboBox, QGroupBox,
    QLabel, QLineEdit, QPushButton, QSizePolicy,
    QTimeEdit, QWidget)

class Ui_Dev_UI(object):
    def setupUi(self, Dev_UI):
        if not Dev_UI.objectName():
            Dev_UI.setObjectName(u"Dev_UI")
        Dev_UI.resize(1535, 814)
        self.Filtered_PPG = QGroupBox(Dev_UI)
        self.Filtered_PPG.setObjectName(u"Filtered_PPG")
        self.Filtered_PPG.setGeometry(QRect(680, 390, 821, 331))
        self.btn_switch_to_user_ui = QPushButton(Dev_UI)
        self.btn_switch_to_user_ui.setObjectName(u"btn_switch_to_user_ui")
        self.btn_switch_to_user_ui.setGeometry(QRect(690, 730, 141, 41))
        self.Raw_PPG = QGroupBox(Dev_UI)
        self.Raw_PPG.setObjectName(u"Raw_PPG")
        self.Raw_PPG.setGeometry(QRect(680, 20, 821, 351))
        self.Set_RTC = QGroupBox(Dev_UI)
        self.Set_RTC.setObjectName(u"Set_RTC")
        self.Set_RTC.setGeometry(QRect(30, 20, 631, 601))
        self.btn_set_rtc = QPushButton(self.Set_RTC)
        self.btn_set_rtc.setObjectName(u"btn_set_rtc")
        self.btn_set_rtc.setGeometry(QRect(270, 560, 93, 29))
        self.cbb_mode_time = QComboBox(self.Set_RTC)
        self.cbb_mode_time.addItem("")
        self.cbb_mode_time.addItem("")
        self.cbb_mode_time.addItem("")
        self.cbb_mode_time.addItem("")
        self.cbb_mode_time.setObjectName(u"cbb_mode_time")
        self.cbb_mode_time.setGeometry(QRect(170, 30, 231, 26))
        self.lbl_epoch_time = QLabel(self.Set_RTC)
        self.lbl_epoch_time.setObjectName(u"lbl_epoch_time")
        self.lbl_epoch_time.setGeometry(QRect(20, 520, 141, 21))
        self.lbl_mode_time = QLabel(self.Set_RTC)
        self.lbl_mode_time.setObjectName(u"lbl_mode_time")
        self.lbl_mode_time.setGeometry(QRect(20, 30, 81, 20))
        self.line_epoch_time = QLineEdit(self.Set_RTC)
        self.line_epoch_time.setObjectName(u"line_epoch_time")
        self.line_epoch_time.setGeometry(QRect(170, 520, 291, 26))
        self.lbl_date_time = QLabel(self.Set_RTC)
        self.lbl_date_time.setObjectName(u"lbl_date_time")
        self.lbl_date_time.setGeometry(QRect(20, 70, 131, 20))
        self.te_mode_24 = QTimeEdit(self.Set_RTC)
        self.te_mode_24.setObjectName(u"te_mode_24")
        self.te_mode_24.setGeometry(QRect(220, 430, 191, 26))
        self.lbl_set_ddmy = QLabel(self.Set_RTC)
        self.lbl_set_ddmy.setObjectName(u"lbl_set_ddmy")
        self.lbl_set_ddmy.setGeometry(QRect(60, 100, 201, 20))
        self.lbl_mode_24 = QLabel(self.Set_RTC)
        self.lbl_mode_24.setObjectName(u"lbl_mode_24")
        self.lbl_mode_24.setGeometry(QRect(60, 430, 151, 20))
        self.lbl_mode_12 = QLabel(self.Set_RTC)
        self.lbl_mode_12.setObjectName(u"lbl_mode_12")
        self.lbl_mode_12.setGeometry(QRect(60, 470, 151, 20))
        self.te_mode_12 = QTimeEdit(self.Set_RTC)
        self.te_mode_12.setObjectName(u"te_mode_12")
        self.te_mode_12.setGeometry(QRect(220, 470, 191, 26))
        self.Calendar = QGroupBox(self.Set_RTC)
        self.Calendar.setObjectName(u"Calendar")
        self.Calendar.setGeometry(QRect(100, 130, 431, 281))
        self.calendar_widget = QCalendarWidget(self.Calendar)
        self.calendar_widget.setObjectName(u"calendar_widget")
        self.calendar_widget.setGeometry(QRect(20, 30, 392, 236))
        self.Notification = QGroupBox(Dev_UI)
        self.Notification.setObjectName(u"Notification")
        self.Notification.setGeometry(QRect(30, 630, 631, 91))
        self.lbl_err_noti = QLabel(self.Notification)
        self.lbl_err_noti.setObjectName(u"lbl_err_noti")
        self.lbl_err_noti.setGeometry(QRect(28, 40, 91, 20))
        self.line_err_noti = QLineEdit(self.Notification)
        self.line_err_noti.setObjectName(u"line_err_noti")
        self.line_err_noti.setGeometry(QRect(150, 40, 451, 26))

        self.retranslateUi(Dev_UI)

        QMetaObject.connectSlotsByName(Dev_UI)
    # setupUi

    def retranslateUi(self, Dev_UI):
        Dev_UI.setWindowTitle(QCoreApplication.translate("Dev_UI", u"Form", None))
        self.Filtered_PPG.setTitle(QCoreApplication.translate("Dev_UI", u"Filtered PPG signal", None))
        self.btn_switch_to_user_ui.setText(QCoreApplication.translate("Dev_UI", u"Switch to User UI", None))
        self.Raw_PPG.setTitle(QCoreApplication.translate("Dev_UI", u"Raw PPG signal", None))
        self.Set_RTC.setTitle(QCoreApplication.translate("Dev_UI", u"Set RTC", None))
        self.btn_set_rtc.setText(QCoreApplication.translate("Dev_UI", u"Set time", None))
        self.cbb_mode_time.setItemText(0, QCoreApplication.translate("Dev_UI", u"None", None))
        self.cbb_mode_time.setItemText(1, QCoreApplication.translate("Dev_UI", u"Date time mode 12h", None))
        self.cbb_mode_time.setItemText(2, QCoreApplication.translate("Dev_UI", u"Date time mode 24h", None))
        self.cbb_mode_time.setItemText(3, QCoreApplication.translate("Dev_UI", u"Epoch time", None))

        self.lbl_epoch_time.setText(QCoreApplication.translate("Dev_UI", u"Epoch time (GMT0):", None))
        self.lbl_mode_time.setText(QCoreApplication.translate("Dev_UI", u"Mode time:", None))
        self.lbl_date_time.setText(QCoreApplication.translate("Dev_UI", u"Date time (GMT7):", None))
        self.te_mode_24.setDisplayFormat(QCoreApplication.translate("Dev_UI", u"hh:mm:ss", None))
        self.lbl_set_ddmy.setText(QCoreApplication.translate("Dev_UI", u"Set day, date, month, year:", None))
        self.lbl_mode_24.setText(QCoreApplication.translate("Dev_UI", u"Set time (mode 24h):", None))
        self.lbl_mode_12.setText(QCoreApplication.translate("Dev_UI", u"Set time (mode 12h):", None))
        self.te_mode_12.setDisplayFormat(QCoreApplication.translate("Dev_UI", u"hh:mm:ss AP", None))
        self.Calendar.setTitle(QCoreApplication.translate("Dev_UI", u"Calendar", None))
        self.Notification.setTitle(QCoreApplication.translate("Dev_UI", u"Error Notification", None))
        self.lbl_err_noti.setText(QCoreApplication.translate("Dev_UI", u"Error Status:", None))
    # retranslateUi

