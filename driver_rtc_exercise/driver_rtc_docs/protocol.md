# RTC EXERCISE PROTCOL

# Table of Contents
  1. [Frame of Protocol](#1-frame-of-protocol)
  2. [Start of frame](#2-start-of-frame)
  3. [Packet type](#3-packet-type)
  4. [Total length](#4-total-length)
  5. [Data](#5-data)
  6. [Stop of frame](#6-stop-of-frame)
  7. [Example](#7-example)

## 1. Frame of Protocol

**Frame**

| **Start Byte** | **Tag** | **Length** |    **Data**    | **Stop Byte** |
|:------:|:-------:|:----------:|:--------------:|:------:|
| 1 byte |  3 bits |   5 bits   | 32 bytes (max) | 1 byte |

## 2. Start of frame
Start bytes **(2 byte)** : the beginning of the frame **_default 0x55_**

## 3. Tag

|   **Tag**  | **Value** |                              **Description**                              |
|:------------------:|:---------:|:-------------------------------------------------------------------------:|
|    SET_TIME_24H    |     0     | Set time in mode 24h for RTC<br>Example:@@02301h02p03s04d05m2024ysun&&    |
|    SET_TIME_12H    |     1     | Set time in mode 12h for RTC<br>Example: @@125am01h02p03s04d05m2024ysun&& |
|   SET_EPOCH_TIME   |     2     | Set epoch time for RTC<br>Example: @@2101721644946&&                      |
|      GET_TIME      |     3     | Get current time from RTC<br>Example: @@305gettm&&                        |
|   SET_TIME_FORMAT  |     4     | Set time RTC in mode 12h or 24h<br>Example: @@40312h&&, @@40324h&&        |
| SET_ALARM_MODE_12H |     5     | Set alarm time in mode 12h<br>Example: @@508am12h34p&&                    |
| SET_ALARM_MODE_24H |     6     | Set alarm time in mode 24h<br>Example: @@60612h34p&&                      |
| CANCEL_ALARM       |     7     | Cancel alarm<br>Example: @@706cancel&&                                    |

## 4. Length
Total length: Indicates the number of bytes in the data (not including header).
## 5. Data
Data (nbytes) : Data of packet type
## 6. Stop of frame
Stop bytes **( 1 byte)** : The end of the frame **_default 0xAA_**
## 7. Example
    55 04 abcd AA
- Start byte: 55
- Tag: 0
- Length: 4
- Data : "abcd"
- Stop byte : AA