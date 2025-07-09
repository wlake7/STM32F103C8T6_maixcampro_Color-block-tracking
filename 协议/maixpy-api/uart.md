当然，这里是您提供的文档的 Markdown 格式版本。

***

# maix.peripheral.uart

maix uart peripheral driver

> You can use `maix.peripheral.uart` to access this module with MaixPy
> This module is generated from MaixPy and MaixCDK

## 1. Module
No module

## 2. Enum

### 2.1. PARITY
uart parity enum

| item | describe |
| :--- | :--- |
| values | **`PARITY_NONE`**: no parity<br>**`PARITY_ODD`**: odd parity<br>**`PARITY_EVEN`**: even parity<br>**`PARITY_MAX`**: |

**C++ defination code:**
```cpp
1 enum PARITY
2 {
3     PARITY_NONE = 0x00, // no
4     parity
5     PARITY_ODD = 0x01,
6     parity
7     PARITY_EVEN = 0x02, // even
8     parity
9     PARITY_MAX
10 }
```

### 2.2. STOP
uart stop bits

| item | describe |
| :--- | :--- |
| values | **`STOP_1`**: 1 stop bit<br>**`STOP_2`**: 2 stop bits<br>**`STOP_1_5`**: 1.5 stop bits<br>**`STOP_MAX`**: |

**C++ defination code:**
```cpp
1 enum STOP
2 {
3     STOP_1 = 0x01, // 1 stop
4     bit
5     STOP_2 = 0x02, // 2 stop
6     bits
7     STOP_1_5 = 0x03, // 1.5 stop
8     bits
9     STOP_MAX
10 }
```

### 2.3. BITS
uart data bits (The title on the OCR page was "uart stop bits", which is likely a typo and should be "uart data bits").

| item | describe |
| :--- | :--- |
| values | **`BITS_5`**: 5 data bits<br>**`BITS_6`**: 6 data bits<br>**`BITS_7`**: 7 data bits<br>**`BITS_8`**: 8 data bits<br>**`BITS_MAX`**: |

**C++ defination code:**
```cpp
1 enum BITS
2 {
3     BITS_5 = 5,  // 5 data bits
4     BITS_6 = 6,  // 6 data bits
5     BITS_7 = 7,  // 7 data bits
6     BITS_8 = 8,  // 8 data bits
7     BITS_MAX
8 }
```

### 2.4. FLOW_CTRL
uart flow control

| item | describe |
| :--- | :--- |
| values | **`FLOW_CTRL_NONE`**: no flow control<br>**`FLOW_CTRL_HW`**: hardware flow control<br>**`FLOW_CTRL_MAX`**: |

**C++ defination code:**
```cpp
1 enum FLOW_CTRL
2 {
3     FLOW_CTRL_NONE = 0, // no
4     flow control
5     FLOW_CTRL_HW = 1, //
6     hardware flow control
7     FLOW_CTRL_MAX
8 }
```

## 3. Variable
(No content provided)

## 4. Function

### 4.1. list_devices
```python
def list_devices() -> list[str]
```
Get supported uart ports.

| item | description |
| :--- | :--- |
| **return** | uart ports list, string type. |

**C++ defination code:**
```cpp
std::vector<std::string> list_devices()
```

## 5. Class

### 5.1. UART
maix uart peripheral driver

**C++ defination code:**
```cpp
class UART : public comm::CommBase
```

#### 5.1.1. __init__
```python
def __init__(self, port: str = '', baudrate: int = 115200, databits: ... = ..., parity: PARITY = ..., stopbits: STOP = ..., flow_ctrl: FLOW_CTRL = ...) -> None
```
UART constructor. You need to call `open()` to open the device.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`port`**: uart port. string type, can get it by `uart.list_devices()`. If empty, will not open device in constructor, default empty. if not empty, will auto open device in constructor, open fail will throw err.Exception.<br>**`baudrate`**: baudrate of uart. int type, default 115200.<br>**`databits`**: databits, values @see uart.DATA_BITS<br>**`parity`**: parity, values @see uart.PARITY<br>**`stopbits`**: stopbits, values @see uart.STOP_BITS<br>**`flow_control`**: flow_control, values @see uart.FLOW_CTRL |
| **static** | False |

**C++ defination code:**
```cpp
UART(const std::string &port = "",
     int baudrate = 115200, uart::BITS
     databits = uart::BITS_8,
     uart::PARITY parity = uart::PARITY_NONE, uart::STOP
     stopbits = uart::STOP_1,
     uart::FLOW_CTRL
     flow_ctrl = uart::FLOW_CTRL_NONE)
```

#### 5.1.2. set_port
```python
def set_port(self, port: str) -> maix.err.Err
```
Set port.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`port`**: uart port. string type, can get it by `uart.list_devices()`. |
| **return** | set port error code, err.Err type. |
| **static** | False |

**C++ defination code:**
```cpp
err::Err set_port(const std::string &port)
```

#### 5.1.3. get_port
```python
def get_port(self) -> str
```
Get port.

| item | description |
| :--- | :--- |
| **type** | func |
| **return** | uart port, string type. |
| **static** | False |

**C++ defination code:**
```cpp
std::string get_port()
```

#### 5.1.4. set_baudrate
```python
def set_baudrate(self, baudrate: int) -> maix.err.Err
```
Set baud rate.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`baudrate`**: baudrate of uart. int type, default 115200. |
| **return** | set baud rate error code, err.Err type. |
| **static** | False |

**C++ defination code:**
```cpp
err::Err set_baudrate(int baudrate)
```

#### 5.1.5. get_baudrate
```python
def get_baudrate(self) -> int
```
Get baud rate.

| item | description |
| :--- | :--- |
| **type** | func |
| **return** | baud rate, int type. |
| **static** | False |

**C++ defination code:**
```cpp
int get_baudrate()
```

#### 5.1.6. open
```python
def open(self) -> maix.err.Err
```
Open uart device, before open, port must be set in constructor or by `set_port()`. If already opened, do nothing and return `err.ERR_NONE`.

| item | description |
| :--- | :--- |
| **type** | func |
| **return** | open device error code, err.Err type. |
| **static** | False |

**C++ defination code:**
```cpp
err::Err open()
```

#### 5.1.7. is_open
```python
def is_open(self) -> bool
```
Check if device is opened.

| item | description |
| :--- | :--- |
| **type** | func |
| **return** | true if opened, false if not opened. |
| **static** | False |

**C++ defination code:**
```cpp
bool is_open()
```

#### 5.1.8. close
```python
def close(self) -> maix.err.Err
```
Close uart device, if already closed, do nothing and return `err.ERR_NONE`.

| item | description |
| :--- | :--- |
| **type** | func |
| **return** | close device error code, err.Err type. |
| **static** | False |

**C++ defination code:**
```cpp
err::Err close()
```

#### 5.1.9. set_received_callback
```python
def set_received_callback(self, callback: typing.Callable[[UART, maix.Bytes(bytes)], None]) -> None
```
Set received callback function.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`callback`**: function to call when received data. |
| **static** | False |

**C++ defination code:**
```cpp
void set_received_callback(std::function<void(Bytes&)> callback)
```

#### 5.1.10. write_str
```python
def write_str(self, str: str) -> int
```
Send string data.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`str`**: string data. |
| **return** | sent data length, < 0 means error, value is `-err.Err`. |
| **static** | False |

**C++ defination code:**
```cpp
int write_str(const std::string &str)
```

#### 5.1.11. write
```python
def write(self, data: maix.Bytes(bytes)) -> int
```
Send data to uart.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`data`**: direction [in], data to send, bytes type. If you want to send str type, use `str.encode()` to convert. |
| **return** | sent length, int type, if < 0 means error, value is `-err.Err`. |
| **static** | False |

**C++ defination code:**
```cpp
int write(Bytes &data)
```

#### 5.1.12. available
```python
def available(self, timeout: int = 0) -> int
```
Check if data available or wait data available.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`timeout`**: unit ms, timeout to wait data, default 0.<br> `0` means check data available and return immediately,<br> `> 0` means wait until data available or timeout.<br> `-1` means wait until data available. |
| **return** | available data number, 0 if timeout or no data, <0 if error, value is `-err.Err`, can be `err::ERR_IO`, `err::ERR_CANCEL`, `err::ERR_NOT_OPEN`. |
| **throw** | `err.Exception` if fatal error. |
| **static** | False |

**C++ defination code:**
```cpp
int available(int timeout = 0)
```

#### 5.1.13. read
```python
def read(*args, **kwargs)
```
Recv data from uart.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`len`**: max data length want to receive, default -1.<br> `-1` means read data in uart receive buffer.<br> `>0` means read len data want to receive. other values is invalid.<br>**`timeout`**: unit ms, timeout to receive data, default 0.<br> `0` means read data in uart receive buffer and return immediately,<br> `-1` means block until read len data,<br> `>0` means block until read len data or timeout. |
| **return** | received data, bytes type. Attention, you need to delete the returned object yourself in C++. |
| **throw** | Read failed will raise `err.Exception` error. |
| **static** | False |

**C++ defination code:**
```cpp
Bytes *read(int len = -1, int timeout = 0)
```

#### 5.1.14. readline
```python
def readline(*args, **kwargs)
```
Read line from uart, that is read until `\n` or `\r\n`.

| item | description |
| :--- | :--- |
| **type** | func |
| **param** | **`timeout`**: unit ms, timeout to receive data, default -1 means block until read `\n` or `\r\n`. `> 0` means block until read `\n` or `\r\n` or timeout. |
| **return** | received data, bytes type. If timeout will return the current received data despite not read `\n` or `\r\n`. e.g. If we want to read `b'123\n'`, but when we only read `b'12'`, timeout, then return `b'12'`. |
| **static** | False |

**C++ defination code:**
```cpp
Bytes *readline(int timeout = -1)
```