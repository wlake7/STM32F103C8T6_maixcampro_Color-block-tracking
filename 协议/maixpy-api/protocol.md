# maix.protocol

maix.protocol module

You can use maix_protocol to access this module with MaixPyThis module is generated from MaixPy and MaixCDK

# 1. Module

No module

# 2. Enum

# 2.1. CMD

protocol cmd, more doc see MaixCDK document's convention doc

<table><tr><td>item</td><td>describe</td></tr><tr><td>note</td><td>max app custom CMD value should &amp;lt; CMD_APP_MAX</td></tr><tr><td>values</td><td>CMD_APP_MAX: 200, max app custom CMD value should &amp;lt; CMD_APP_MAX CMD_SET_REPORT: set auto upload data mode CMD_APP_LIST:</td></tr></table>

<table><tr><td>item</td><td>describe</td></tr><tr><td></td><td>CMD_START_APP:
CMD_EXIT_APP:
CMD_CUR_APP_INFO:
CMD_APP_INFO:
CMD_KEY:
CMD_TOUCH:</td></tr></table>

$\zeta + +$  definition code:

<table><tr><td>1</td><td>enum CMD</td></tr><tr><td>2</td><td>{</td></tr><tr><td>3</td><td>CMD_APP_MAX = 0xC8,</td></tr><tr><td>4</td><td>// 200, max app custom CMD value</td></tr><tr><td>5</td><td>should &amp;lt; CMD_APP_MAX</td></tr><tr><td>6</td><td></td></tr><tr><td>7</td><td>CMD_SET_REPORT = 0xF8,</td></tr><tr><td>8</td><td>// set auto upload data mode</td></tr><tr><td>9</td><td>CMD_APP_LIST = 0xF9,</td></tr><tr><td>10</td><td>CMD_START_APP = 0xFA,</td></tr><tr><td>11</td><td>CMD_EXIT_APP = 0xFB,</td></tr><tr><td>12</td><td>CMD_CUR_APP_INFO = 0xFC,</td></tr><tr><td>13</td><td>CMD_APP_INFO = 0xFD,</td></tr><tr><td></td><td>CMD_KEY = 0xFE,</td></tr><tr><td></td><td>CMD_TOUCH = 0xFF,</td></tr></table>

# 2.2. FLAGS

protocol flags, more doc see MaixCDK document's convention doc

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>FLAG_REQ:
FLAG_RESP:</td></tr></table>

<table><tr><td>item</td><td>describe</td></tr><tr><td></td><td>FLAG_IS_RESP_MASK:
FLAG_RESP_OK:
FLAG_RESP_ERR:
FLAG_RESP_OK_MASK:
FLAG_REPORT:
FLAG_REPORT_MASK:
FLAG_VERSION_MASK:</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1</td><td>enum FLAGS</td></tr><tr><td>2</td><td>{</td></tr><tr><td>3</td><td>FLAG_REQ = 0x00,</td></tr><tr><td>4</td><td>FLAG_RESP = 0x80,</td></tr><tr><td>5</td><td>FLAG_IS_RESP_MASK = 0x80,</td></tr><tr><td>6</td><td></td></tr><tr><td>7</td><td>FLAG_RESP_OK = 0x40,</td></tr><tr><td>8</td><td>FLAG_RESP_ERR = 0x00,</td></tr><tr><td>9</td><td>FLAG_RESP_OK_MASK = 0x40,</td></tr><tr><td>10</td><td></td></tr><tr><td>11</td><td>FLAG_REPORT = 0x20,</td></tr><tr><td>12</td><td>FLAG_REPORT_MASK = 0x20,</td></tr><tr><td>13</td><td></td></tr><tr><td>14</td><td>FLAG_VERSION_MASK = 0x03</td></tr><tr><td>15</td><td>}</td></tr></table>

# 3. Variable

# 3.1. VERSION

protocol version

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>1</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 const uint8_t VERSION = 1

# 3.2.HEADER

protocol header

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 extern uint32_tHEADER

# 4. Function

# 4.1. crc16_IBM

1 def crc16_IBM(data: maix.Bytes(bytes)) - > int

CRC16- IBM

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>data: data, bytes type.</td></tr><tr><td>return</td><td>CRC16-IBM value, uint16_t type.</td></tr></table>

$\mathtt{C + + }$  defination code:

1 uint16_t crc16_IBM(const Bytes *data)

# 5. Class

# 5.1. MSG

protocol msg

$\mathtt{C + + }$  defination code:

1 class MSG

# 5.1.1. version

protocol version

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 uint8_t version

# 5.1.2. resp_ok

Indicate response message type, true means CMD valid and the CMD processed correctly, (only for response msg)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 uint8_t resp_ok

# 5.1.3.has_been_replyd

Flag whether CMD has been processed and responded to CMD sender.\nE.g. CMD CMD_START_APP will be automatically processed in CommProtocol.get_msg function,\nso the return msg will set this flag to true.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

bool has_been_replyd{false}

# 5.1.4.cmd

CMD value

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 uint8_t cmd

# 5.1.5. is_resp

message is response or not, contrast with is_req

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool is_resp

# 5.1.6. is_req

message is request or not, contrast with is_resp

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

bool is_req

# 5.1.7. is_report

message is request or not, contrast with is_resp

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

bool is_report

# 5.1.8. body_len

Message body length, read only, use set_body() to update

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>attention</td><td>DO NOT manually change this value</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int body_len

# 5.1.9. encode_resp_ok

1 def encode_resp_ok(\*args, \*\*kwargs)

Encode response ok(success) message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>body: response body, can be null</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 Bytes \*encode_resp_ok(Bytes \*body  $=$  nullptr)

# 5.1.10. encode_report

1 def encode_report(\*args, \*\*kwargs)

Encode proactively report message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>body: report body, can be null</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -errErr</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defnati on code:

1 | Bytes *encode_report(Bytes *body = nullptr)

# 5.1.11. encode resp err

Encode response error message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>code: error code
msg: error message</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -errErr</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defnati on code:

1 | Bytes *encode(resp_err(err::Err code, const std::string &msg)

# 5.1.12. set_body

1 | def set_body(self, body_new: maix.Bytes(bytes)) - > None

Update message body

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>body_new: new body data</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void set_body(Bytes *body_new)

# 5.1.13. get_body

1 | def get_body(*args, **kwargs)

Get message body

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>message body, bytes type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | Bytes *get_body()

# 5.2. Protocol

Communicate protocol

$\mathtt{C + + }$  definition code:

1 | class Protocol

# 5.2.1. init

1 | def init__(self, buff_size: int = 1024, header: int = 3148663466) - > None

Construct a new Protocol object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>buff_size: Data queue buffer size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | Protocol(int buff_size = 1024, uint32_t header=maix::protocol::HEADER)

# 5.2.2. buff_size

![](https://cdn-mineru.openxlab.org.cn/extract/860a7017-a484-4a6c-b79d-0500f88d3caf/325f49b2befa661d2ee454054f4da1e8d3f2e3863f5022150b025d63b1dc0984.jpg)

Data queue buffer size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int buff_size()

# 5.2.3.push_data

1 def push_data(self, new_data: maix.Bytes(bytes)) - > maix.err.Err

Add data to data queue

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>new_data: new data</td></tr><tr><td>return</td><td>error code, maybe err.Err. ERR_BUFF_FULL</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err push_data(const Bytes *new_data)

# 5.2.4. decode

1 | def decode(self, new_data: maix.Bytes(bytes) = None) - > MSG

Decode data in data queue and return a message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>new_data: new data add to data queue, if null, only decode.</td></tr><tr><td>return</td><td>decoded message, if nullptr, means no message decoded.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | protocol::MSG *decode(const Bytes *new_data = nullptr)

# 5.2.5. encode_resp_ok

1 | def encode_resp_ok(*args, **kwargs)

Encode response ok(success) message to buffer

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cmd: CMD value
body: response body, can be null</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Bytes *encode_resp_ok(uint8_t cmd, Bytes *body = nullptr)

# 5.2.6. encode_report

1 | def encode_report(*args, **kwargs)

Encode proactively report message to buffer

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cmd: CMD value
body: report body, can be null</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Bytes *encode_report(uint8_t cmd, Bytes *body = nullptr)

# 5.2.7. encode_resp_err

![](https://cdn-mineru.openxlab.org.cn/extract/860a7017-a484-4a6c-b79d-0500f88d3caf/b5f87cb9dae246f77e8e20a43fb5c341ffcb56e5b57f86a6cf1cc76234deac73.jpg)

Encode response error message to buffer

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cmd: CMD value
code: error code
msg: error message</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ defination code:</td></tr><tr><td>1</td><td>Bytes *encode_resp_err(uint8_t cmd,
err::Err code, const std::string &amp;amp;msg)</td></tr></table>