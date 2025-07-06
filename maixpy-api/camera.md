# maix.camera

maix.camera module, access camera device and get image from it

You can use maixcamera to access this module with MaixPy This module is generated from MaixPy and MaixCDK

# 1. Module

No module

2. Enum3. Variable4. Function

# 4.1. list_devices

1 | def list_devices() - > list[str]

List all supported camera devices.

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the path to the camera device.</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::string> list_devices()

# 4.2. set_regs_enable

1 | def set_regs_enable(enable: bool = True) - > None

Enable set camera registers, default is false, if set to true, will not set camera registers, you can manually set registers by write_reg API.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>enable: enable/disable set camera registers</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void set_regs_enable(bool enable = true)

# 4.3. get_device_name

1 | def get_device_name() - > str

Get device name. Most of the time, the returned name is the name of the sensor.

$\mathtt{C + + }$  definition code:

1 | std::string get_device_name()

# 5. Class

# 5.1. Camera

Camera class

$\mathtt{C + + }$  definition code:

1 | class Camera

# 5.1.1. __init__

1 | def __init__(self, width: int = - 1, height: int = - 1, format: maix.image.Format = ..., device: str = None, fps: float = - 1, buff_num: int = 3, open: bool = True, raw: bool = False) - > None

Construct a new Camera object.\nMaximum resolution support 2560x1440.

https://wiki.sipeed.com/maixpy/api/maix/camera.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: camera width, default is -1,
means auto, mostly means max width of camera support
height: camera height, default is -1,</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>means auto, mostly means max height of camera support
format: camera output format, default is image.Format.FMT_RGB888
device: camera device path, you can get devices by list_devices method, by default(value is NULL(None in MaixPy)) means the first device
fps: camera fps, default is -1, means auto, mostly means max fps of camera support
buff_num: camera buffer number, default is 3, means 3 buffer, one used by user, one used for cache the next frame, more than one buffer will accelerate image read speed, but will cost more memory
open: If true, camera will automatically call open() after creation. default is true. raw: If true, you can use read_raw() to capture the raw image output from the sensor.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Camera(int width = - 1, int height = - 1, image::Format format = image::FMT_RGB888, const char *device = nullptr, double fps = - 1, int buff_num = 3, bool open = true, bool

# 5.1.2. get_ch_nums

Get the number of channels supported by the camera.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the maximum number of channels.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int get_ch_nums()</td></tr></table>

# 5.1.3. open

<table><tr><td>1 | def open(self, width: int = -1, height: int = -1, format: maix.image.Format = ..., fps: float = -1, buff_num: int = -1) -&amp;gt; maix.err.Err</td></tr></table>

Open camera and run

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: camera width, default is -1, 
means auto, mostly means max width of</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>camera support
height: camera height, default is -1,
means auto, mostly means max height of camera support
format: camera output format, default same as the constructor&#x27;s format argument
fps: camera fps, default is -1, means auto, mostly means max fps of camera support
buff_num: camera buffer number,
default is 3, means 3 buffer, one used by user, one used for cache the next frame, more than one buffer will accelerate image read speed, but will cost more memory.</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err open(int width = - 1, int height = - 1, image::Format format = image::FMT_INVALID, double fps = - 1, int buff_num = - 1)

# 5.1.4. read

def read(self, buff: capsule = None, buff_size: int = 0, block: bool = True,

block_ms: int = - 1) - > maix.image.Image

Get one frame image from camera buffer, must call open method before read.\nIf open method not called, will call it automatically, if open failed, will throw exception!\nSo call open method before read is recommended.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>buff: buffer to store image data, if buff is nullptr, will alloc memory automatically.
In MaixPy, default to None, you can create a image.Image object, then pass img.data() to buff.
block: block read, default is true, means block until read image successfully, if set to false, will return nullptr if no image in buffer
block_ms: block read timeout</td></tr><tr><td>return</td><td>image::Image object, if failed, return nullptr, you should delete if manually in C++</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *read(void *buff = nullptr, size_t buff_size = 0, bool block = true, int block_ms = - 1)

# 5.1.5. read_raw

1 | def read_raw(self) - > maix.image.Image

Read the raw image and obtain the width, height, and format of the raw image through the returned Image object.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>The raw image is in a Bayer format, and its width and height are affected by the driver. Modifying the size and format is generally not allowed.</td></tr><tr><td>return</td><td>image::Image object, if failed, return nullptr; you should delete if manually in C++</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *read_raw()

# 5.1.6. clear_buff

1 | def clear_buff(self) - > None

Clear buff to ensure the next read image is the latest image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

void clear_buff()

# 5.1.7.skip_frames

1 def skip_frames(self, num: int) - > None

Read some frames and drop, this is usually used avoid read not stable image when camera just opened.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>num: number of frames to read and drop</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

void skip_frames(int num)

# 5.1.8.close

1 def close(self) - > None

Close camera

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

void close()

# 5.1.9. add_channel

1 def add_channel(self, width: int = - 1, height: int = - 1, format: maix.image.Format = ..., fps: float = - 1, buff_num: int = 3, open: bool = True) - > Camera

Add a new channel and return a new Camera object, you can use close() to close this channel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: camera width, default is -1,
means auto, mostly means max width of camera support
height: camera height, default is -1,
means auto, mostly means max height of camera support
format: camera output format, default is RGB888
fps: camera fps, default is -1, means auto, mostly means max fps of camera</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>support
buff_num: camera buffer number,
default is 3, means 3 buffer, one used by user, one used for cache the next frame, more than one buffer will accelerate image read speed, but will cost more memory.
open: If true, camera will automatically call open() after creation. default is true.</td></tr><tr><td>return</td><td>new Camera object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 camera::Camera *add_channel(int width = - 1, int height = - 1, image::Format format = image::FMT_RGB888, double fps = - 1, int buff_num = 3, bool open = true)

# 5.1.10. is_opened

1 def is_opened(self) - > bool

Check if camera is opened

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>true if camera is opened, false if not</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool is_opened()

# 5.1.11. is closed

1 def is_closed(self) - > bool

check camera device is closed or not

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>closed or not, bool type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool is closed()

# 5.1.12. width

1 def width(self) - > int

Get camera width

https://wiki.sipeed.com/maixpy/api/maix/camera.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>camera width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int width()

# 5.1.13.height

Get camera height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int height()

# 5.1.14.fps

def fps(self) - > float

Get camera fps

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera fps</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 double fps()

# 5.1.15. format

1 def format(self) - > maix.image.Format

Get camera output format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera output format, image::Format object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Format format()

# 5.1.16. buff_num

1 def buff_num(self) - > int

Get camera buffer number

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera buffer number</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int buff_num()

# 5.1.17. hmirror

Set/Get camera horizontal mirror

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera horizontal mirror</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int hmirror(int value = - 1)

# 5.1.18. vflip

1 def vflip(self, value: int = - 1) - > int

Set/Get camera vertical flip

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera vertical flip</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int vflip(int value = - 1)

# 5.1.19. device

1 def device(self) - > str

Get camera device path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>camera device path</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::string device()

# 5.1.20. write_reg

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/8523adaf7a95f80fc64ae0ad5f1768c5eda924f91b6a9a7511374073be910280.jpg)

Write camera register

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>addr: register address
data: register data
bit_width: register data bit width,
default is 8</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err write_reg(int addr, int data, int bit_width = 8)

# 5.1.21. read_reg

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/3b11b34f33fc3aee302d72f0188f0724bbabe5af039cb6bd334d2d4b928fd7a8.jpg)

Read camera register

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>addr: register address
bit_width: register data bit width,
default is 8</td></tr><tr><td>return</td><td>register data, -1 means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int read_reg(int addr, int bit_width = 8)

# 5.1.22.show_colorbar

Camera output color bar image for test

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>enable: enable/disable color bar</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err show_colorbar(bool enable)

# 5.1.23. get_channel

1 | def get_channel(self) - > int

Get channel of camera

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>channel number</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int get_channel()

# 5.1.24. set_resolution

1 | def set_resolution(self, width: int, height: int) - > maix.err.Err

Set camera resolution

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: new width
height: new height</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err set_resolution(int width, int height)

# 5.1.25. set fps

1 def set_fps(self, fps: float) - > maix.err.Err

Set camera fps

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>fps: new fps</td></tr><tr><td>return</td><td>error code, err::ERR_NONE means success, others means failed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err set_fps(double fps)

# 5.1.26. exposure

1 def exposure(self, value: int = - 1) - > int

Set/Get camera exposure

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.</td></tr><tr><td>param</td><td>value: exposure time. unit: us
If value == -1, return exposure time.
If value != 0, set and return exposure time.</td></tr><tr><td>return</td><td>camera exposure time</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>int exposure(int value = -1)</td></tr></table>

# 5.1.27. gain

<table><tr><td>1 | def gain(self, value: int = -1) -&amp;gt; int</td></tr></table>

Set/Get camera gain

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.</td></tr><tr><td>param</td><td>value: camera gain.
If value == -1, returns camera gain.</td></tr></table>

2025/6/22 16:58 maix.camera - MaixPy

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>If value != 0, set and return camera gain.</td></tr><tr><td>return</td><td>camera gain</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/26b66b1e85fef06afd25f54e335e3ce09fedc46f8c9bda64fd0c8ba46feed52d.jpg)

# 5.1.28. luma

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/17e8decbde7ef0ad22b86382d176931d462784574f9e5b278af4dae0eda202b4.jpg)

Set/Get camera luma

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.</td></tr><tr><td>param</td><td>value: luma value, range is [0, 100]
If value == -1, returns luma value.
If value != 0, set and return luma value.</td></tr><tr><td>return</td><td>returns luma value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 int luma(int value = - 1)

# 5.1.29. constrast

1 def constrast(self, value: int = - 1) - > int

Set/Get camera constrast

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.</td></tr><tr><td>param</td><td>value: constrast value, range is [0, 100]
If value == -1, returns constrast value.
If value != 0, set and return constrast value.</td></tr><tr><td>return</td><td>returns constrast value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 int constrast(int value = - 1)

# 5.1.30. saturation

1 def saturation(self, value: int = - 1) - > int

Set/Get camera saturation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.</td></tr><tr><td>param</td><td>value: saturation value, range is [0, 100]
If value == -1, returns saturation value.
If value != 0, set and return saturation value.</td></tr><tr><td>return</td><td>returns saturation value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int saturation(int value = - 1)

# 5.1.31. awb_mode

1 def awb_mode(self, value: int = - 1) - > int

Set/Get white balance mode (deprecated interface)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.
This interface may be deprecated in the future, and there may be incompatibilities in the definition of the parameters of the new interface</td></tr><tr><td>param</td><td>value: value = 0, means set white balance to auto mode, value = 1, means set white balance to manual mode, default is auto mode.</td></tr><tr><td>return</td><td>returns awb mode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 int awb_mode(int value = - 1)

# 5.1.32. set_awb

Set/Get white balance mode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>with it.</td></tr><tr><td>param</td><td>value: value = 0, means set white balance to manual mode, value = 1, means set white balance to auto mode, default is auto mode.</td></tr><tr><td>return</td><td>returns awb mode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/ec33df4711a6342a12204bcac5ecc499c07f475b39830de030a89e49b8bf5bed.jpg)

# 5.1.33. exp_mode

![](https://cdn-mineru.openxlab.org.cn/extract/a1aa511e-9079-43ed-8300-eadaa6df483c/92d2cc3d05c7a37c996d5bacfff9c3ef15ab6968deba39b3cf0ec5f199b164e4.jpg)

Set/Get exposure mode (deprecated interface)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>attention</td><td>This method will affect the isp and thus the image, so please be careful with it.
This interface may be deprecated in the future, and there may be incompatibilities in the definition of the parameters of the new interface</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>value: value = 0, means set exposure to auto mode, value = 1, means set exposure to manual mode, default is auto mode.</td></tr><tr><td>return</td><td>returns exposure mode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int exp_mode(int value = - 1)

# 5.1.34. set_windowing

Set window size of camera

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: Support two input formats, [x,y,w,h] set the coordinates and size of the window; 
[w,h] set the size of the window, when the window is centred.</td></tr><tr><td>return</td><td>error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Errset_window(std::vector<int> roi)