# maix.display

maix.display module, control display device and show image on it

You can use maix. display to access this module with MaixPy This module is generated from MaixPy and MaixCDK

# 1. Module

No module

2. Enum

3. Variable

4. Function

# 4.1. send_to_maixvision

1 def send_to_maixvision(img: maix.image.Image) - > None

Send image to MaixVision work station if connected.\n\nYou want to debug your program and don't want to initialize display, use this method.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>img: image to send, image.Image object</td></tr></table>

$\mathtt{C + + }$  defination code:

void send_to_maixvision(image::Image &img)

# 4.2. set_trans_image_quality

1 def set_trans_image_quality(value: int) - > None

Set image transport quality(only for JPEG)

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>quality: default 95, value from 51 ~ 100</td></tr></table>

$\mathtt{C + + }$  defination code:

void set_trans_image_quality(const int value)

# 5. Class

# 5.1. Display

Display class

$\mathtt{C + + }$  defination code:

1 class Display

# 5.1.1. init

1 def init_(self, width: int = - 1, height: int = - 1, format: maix.image.Format = ..., device: str = '', open: bool = True) - > None

Construct a new Display object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: display width, by default(value is -1) means auto detect,
if width &amp;gt; max device supported width,
will auto set to max device supported width
height: display height, by default(value is -1) means auto detect,
if height &amp;gt; max device supported height,
will auto set to max device supported height
device: display device name, you can get devices by list_devices method, by default(value is NULL(None in MaixPy)) means the first device
open: If true, display will automatically call open() after creation. default is true.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

Display(int width  $\equiv$  - 1,int height  $\equiv$  - 1,image::Format format  $\equiv$  image::FMT_RGB888,const std::string &device  $=$  "",bool open  $=$  true)

# 5.1.2.width

1 def width(self) - > int

Get display width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int width()

# 5.1.3.height

1 def height(self) - > int

Get display height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>ch: channel to get, by default(value is 0) 
means the first channel</td></tr><tr><td>return</td><td>height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 int height()

# 5.1.4. size

Get display size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>ch: channel to get, by default(value is 0) 
means the first channel</td></tr><tr><td>return</td><td>size A list type in MaixPy, [width, height]</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 std::vector<int> size()

# 5.1.5. format

![](https://cdn-mineru.openxlab.org.cn/extract/3b7509bf-710f-482c-8c4f-db8f2b575be1/58a83fbf7bd58089f2ba7753a48a346ab251aa87a3fb0c5334e65f2132ec3cf7.jpg)

Get display format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>format</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format format()

# 5.1.6. open

1 def open(self, width: int = - 1, height: int = - 1, format: maix.image.Format = ...) - > maix.err.Err

open display device, if already opened, will return err.ERR_NONE.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: display width, default is -1, means auto, mostly means max width of display support
height: display height, default is -1, means auto, mostly means max height of display support</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>format: display output format, default is RGB888</td></tr><tr><td>return</td><td>error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 err::Err open(int width = - 1, int height = - 1, image::Format format = image::FMT_INVALID)

# 5.1.7. close

1 def close(self) - > maix.err.Err

close display device

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 err::Err close()

# 5.1.8. add_channel

1 def add_channel(self, width: int = - 1, height: int = - 1, format: maix.image.Format = ..., open: bool = True) - > Display

Add a new channel and return a new Display object, you can use close() to close this channel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>If a new disp channel is created, it is recommended to set fit=image::FIT_COVER or fit=image::FIT_FILL when running show for the main channel, otherwise the display of the new disp channel may be abnormal.</td></tr><tr><td>param</td><td>width: display width, default is -1, means auto, mostly means max width of display support. Maximum width must not exceed the main channel. height: display height, default is -1, means auto, mostly means max height of display support. Maximum height must not exceed the main channel. format: display output format, default is FMT_BGRA8888 open: If true, display will automatically call open() after creation. default is true.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>new Display object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | display::Display *add_channel(int width = - 1, int height = - 1, image::Format format = image::FMT_BGRA8888, bool open = true)

# 5.1.9. is_opened

1 | def is_opened(self) - > bool

check display device is opened or not

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>opened or not, bool type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | bool is_opened()

# 5.1.10. is closed

1 | def is_closed(self) - > bool

check display device is closed or not

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>closed or not, bool type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool is_closed()

# 5.1.11. show

1 def show(self, img: maix.image.Image, fit: maix.image.Fit = ...) - > maix.err. Err

show image on display device, and will also send to MaixVision work station if connected.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image to show, image.Image object, if the size of image smaller than display size, will show in the center of display; if the size of image bigger than display size, will auto resize to display size and keep ratio, fill blank with black color. 
fit: image in screen fit mode, by default(value is image.FIT_CONTAIN), @see image.Fit for more details</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>e.g. image.FIT_CONTAIN means resize image to fit display size and keep ratio, fill blank with black color.</td></tr><tr><td>return</td><td>error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err show(image::Image &img, image::Fit fit = image::FIT_CONTAIN)

# 5.1.12. device

def device(self) - > str

Get display device path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>display device path</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string device()

# 5.1.13. set_backlight

![](https://cdn-mineru.openxlab.org.cn/extract/3b7509bf-710f-482c-8c4f-db8f2b575be1/b2370d40e887632529ad5179f3926a6803ba18f70d89c35fd2807de8f507bb60.jpg)

Set display backlight

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>value: backlight value, float type, range is [0, 100]</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | void set backlight(float value)</td></tr></table>

# 5.1.14. get backlight

<table><tr><td>1 | def get backlight(self) -&amp;gt; float</td></tr></table>

Get display backlight

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>value backlight value, float type, range is [0, 100]</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3b7509bf-710f-482c-8c4f-db8f2b575be1/d8c53aa16ea0d85c62add80d6c5755b871b5244989a04f99fc7188b86379eb24.jpg)

# 5.1.15.set_hmirror

1 def set_hmirror(self, en: bool) - > maix.err.Err

Set display mirror

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>en: enable/disable mirror</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err set_hmirror(bool en)

# 5.1.16.set vflip

1 def set_vflip(self, en: bool) - > maix.err.Err

Set display flip

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>en: enable/disable flip</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code: