# maix.touchscreen

maix.touchscreen module

You can use maix.touchscreen to access this module with MaixPy This module is generated from MaixPy and MaixCDK

# 1. Module

No module

2. Enum  
3. Variable  
4. Function  
5. Class

# 5.1. TouchScreen

TouchScreen class

$\zeta + +$  defination code:

# 5.1.1. init

1 | def init_(self, device: str = '', open: bool = True) - > None

Construct a new TouchScreen object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>device: touchscreen device path, you can get devices by list_devices method, by default(value is NULL(None in MaixPy)) means the first device
open: If true, touchscreen will automatically call open() after creation. default is true.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

TouchScreen(const std::string &device = "", bool open = true)

# 5.1.2. open

1 | def open(self) - > maix.err.Err

open touchscreen device

https://wiki.sipeed.com/maixpy/api/maix/touchscreen.html

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 err::Err open

# 5.1.3. close

1 def close(self) - > maix.err.Err

close touchscreen device

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 err::Err close

# 5.1.4. read

1 def read(self) - > list[int]

read touchscreen device

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will discard same event in buffer, that is:
if too many move event in buffer
when call this method, it will only return the last one,
and if read pressed or released event, it will return immediately.</td></tr><tr><td>return</td><td>Returns a list include x, y, pressed state</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/bca0c74a-829b-413f-b402-433958e85270/431292c76eaf8b99a2941466e87342dea5058be81194b34df2e5c897f34dac4b.jpg)

# 5.1.5. read0

![](https://cdn-mineru.openxlab.org.cn/extract/bca0c74a-829b-413f-b402-433958e85270/28b6495237f16d87e72621d2234ec65c9fdf2dca8e4bb00f8b12e9f5fc60db10.jpg)

read touchscreen device

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will return immediately if have event, so it&#x27;s better to use available() to check if have more</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>event in buffer,
or too much event in buffer when your program call this read() interval is too long will make your program slow.</td></tr><tr><td>return</td><td>Returns a list include x, y, pressed state</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<int> read0()

# 5.1.6. available

If we need to read from touchscreen, for event driven touchscreen means have event or not

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>timeout: -1 means block, 0 means no block, &amp;gt;0 means timeout, default is 0, unit is ms.</td></tr><tr><td>return</td><td>true if need to read(have event), false if not</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | bool available(int timeout = 0)

# 5.1.7. is_opened

1 | def is_opened(self) - > bool

Check if touchscreen is opened

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>true if touchscreen is opened, false if not</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | bool is_opened()