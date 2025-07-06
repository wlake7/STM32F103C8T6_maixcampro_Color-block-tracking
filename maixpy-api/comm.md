# maix.comm

maix.comm module

You can use maix.comm to access this module with MaixPyThis module is generated from MaixPy and MaixCDK

# 1. Module

<table><tr><td>module</td><td>brief</td></tr><tr><td>modbus</td><td>maix.comm.modbus module</td></tr></table>

# 2. Enum

# 3. Variable

# 4. Function

# 4.1. add_default_comm_listener

Add default CommProtocol listener.\nWhen the application uses this port, the listening thread will immediately\nrelease the port resources and exit. If you need to start the default listening thread

again,\nplease release the default port resources and then call this function.

$\mathtt{C + + }$  defination code:

1 | void add_default_comm_listener()

# 4.2. rm_default_comm_listener

Remove default CommProtocol listener.

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>bool type.</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | bool rm_default_comm_listener()

# 5. Class

# 5.1. CommProtocol

Class for communication protocol

$\mathtt{C + + }$  defination code:

1 | class CommProtocol

# 5.1.1. _init_

1 | def __init__(self, buff_size: int = 1024, header: int = 3148663466,

method_none_raise: bool = False) - > None

Construct a new CommProtocol object  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>buff_size: buffer size, default to 1024 bytes
header: Customize header, default is maix.protocolHEADER
method_none_raise: If method set to &quot;none&quot;, raise err.Exception() if method_none_raise is true. Default false, if method is &quot;none&quot; and this arg is false, valid() function will return false and get_msg() always return none.</td></tr><tr><td>throw</td><td>Initialize failed will raise err::Exception()</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

CommProtocol(int buff_size = 1024, uint32_t header=maix::protocol::HEADER, bool method_none_raise = false)

# 5.1.2. get_msg

1 def get_msg(self, timeout: int = 0) - >

Read data to buffer, and try to decode it as maix.protocol.MSG object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>timeout: unit ms, 0 means return
immediately, -1 means block until have msg, &amp;gt;0 means block until have msg or timeout.</td></tr><tr><td>return</td><td>decoded data, if nullptr, means no valid frame found.
Attentionin, delete it after use in C++.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | protocol::MSG *get_msg(int timeout = 0)</td></tr></table>

# 5.1.3. resp_ok

1 | def resp_ok(self, cmd: int, body: maix.Bytes(bytes) = None) - > maix.err.Err

Send response ok(success) message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>cmd: CMD value
body: response body, can be null</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err.
Attention, delete it after use in C++.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err resp_ok(uint8_t cmd, Bytes *body = nullptr)

# 5.1.4. report

1 def report(self, cmd: int, body: maix.Bytes(bytes) = None) - > maix.err.Err

Send report message

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cmd: CMD value
body: report body, can be null</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err.
Attention, delete it after use in C++.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err report(uint8_t cmd, Bytes *body = nullptr)

# 5.1.5. resp_err

1 def resp_err(self, cmd: int, code: maix.err.Err, msg: str) - > maix.err.Err

Encode response error message to buffer

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cmd: CMD value
code: error code
msg: error message</td></tr><tr><td>return</td><td>encoded data, if nullptr, means error, and the error code is -err.Err.
Attention, delete it after use in C++.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err resp_err(uint8_t cmd, err::Err code, const std::string &msg)

# 5.1.6. valid

Is CommProtocol valid, only not valid when method not set to "none".

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>false if commprotocol method is &quot;none&quot;.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/6dc0a552-f532-425e-9858-1ff9c8560c9e/17343a48a81c8d2f5acedbf1f1bfb477dd1901072725c53493ac85e61b5dbf4b.jpg)

# 5.1.7. set_method

![](https://cdn-mineru.openxlab.org.cn/extract/6dc0a552-f532-425e-9858-1ff9c8560c9e/33d0d7ad8eb92b338277df32a700c9f62bed4b09f0f6a875197c540f3f3830c6.jpg)

Set CommProtocol method

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>method: Can be &quot;uart&quot; or &quot;none&quot;, &quot;none&quot; means not use CommProtocol.</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

static err::Err set_method(const std::string &method)

# 5.1.8. get_method

1 | def get_method() - > str

Get CommProtocol method

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>method Can be &quot;uart&quot; or &quot;none&quot;, &quot;none&quot; means not use CommProtocol.</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | static std::string get_method()