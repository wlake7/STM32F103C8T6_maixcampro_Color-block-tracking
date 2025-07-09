# maix.image

maix.image module, image related definition and functions

You can use maix.image to access this module with MaixPyThis module is generated from MaixPy and MaixCDK

# 1. Module

No module

# 2. Enum

# 2.1. Format

Image formats

<table><tr><td>item</td><td>describe</td></tr><tr><td>attention</td><td>for MaixPy firmware developers, 
update this enum will also need to 
update the fmt_size and fmt_names 
too!!!</td></tr><tr><td>values</td><td>FMT_RGB888: RGBRGB...RGB, R at the 
lowest address 
FMT_BGR888: BGRBGR...BGR, B at the</td></tr></table>

<table><tr><td>item</td><td>describe</td></tr><tr><td></td><td>lowest address
FMT_RGBA8888: RGBARGBA...RGBA,
R at the lowest address
FMT_BGRA8888: BGRABGRA...BGRA,
B at the lowest address
FMT_RGB565:
FMT_BGR565:
FMT_YUV422SP:
YYYY...UVUVUV...UVUV
FMT_YUV422P: YYY...UUU...VVV
FMT_YVU420SP:
YYYY...UVUVUU...VUVU, NV21
FMT_YUV420SP:
YYYY...UVUVUU...UVUV, NV12
FMT_YVU420P: YYY...VVV...UUU
FMT_YUV420P: YYY...UUU...VVV
FMT_GRAYSCALE:
FMT_BGGR6: 6-bit Bayer format with a BGGR pattern.
FMT_GBRG6: 6-bit Bayer format with a GBRG pattern.
FMT_GRBG6: 6-bit Bayer format with a GBRG pattern.
FMT_RGGB6: 6-bit Bayer format with a RGGB pattern.
FMT_BGGR8: 8-bit Bayer format with a BGGR pattern.
FMT_GBRG8: 8-bit Bayer format with a GBRG pattern.
FMT_GRBG8: 8-bit Bayer format with a GBRG pattern.</td></tr></table>

<table><tr><td>item</td><td>describe</td></tr><tr><td></td><td>FMT_RGGB8: 8-bit Bayer format with a RGGB pattern.
FMT_BGGR10: 10-bit Bayer format with a BGGR pattern.
FMT_GBRG10: 10-bit Bayer format with a GBRG pattern.
FMT_GRBG10: 10-bit Bayer format with a GRBG pattern.
FMT_RGGB10: 10-bit Bayer format with a RGGB pattern.
FMT_BGGR12: 12-bit Bayer format with a BGGR pattern.
FMT_GBRG12: 12-bit Bayer format with a GBRG pattern.
FMT_GRBG12: 12-bit Bayer format with a GRBG pattern.
FMT_RGGB12: 12-bit Bayer format with a RGGB pattern.
FMT_UNCOMPRESSED_MAX:
FMT_COMPRESSED_MIN:
FMT JPEG:
FMT PNG:
FMT_COMPRESSED_MAX:
FMT_INVALID: format not valid</td></tr></table>

$\zeta + +$  definition code:

<table><tr><td>1</td><td>enum Format</td></tr><tr><td>2</td><td>{</td></tr><tr><td>3</td><td>FMT_RGB888 = 0, //</td></tr><tr><td>4</td><td>RGBRGB...RGB, R at the lowest address</td></tr><tr><td>5</td><td>FMT_BGR888,   //</td></tr><tr><td>6</td><td></td></tr></table>

8 RMT_RGBA8888, // 9 RGBARGBA...RGBA, R at the lowest 10 address 11 RMT_BGRA8888, // 12 BGRABGRA...RGBA, B at the lowest 13 address 14 FMT_RGB565, 15 FMT_BGR565, 16 FMT_YUV422SP, // 17 YYY...UVUVUV...UVUV 18 FMT_YUV422P, // 19 YYY...UUU...VVV 20 FMT_YVU420SP, // 21 YYY...VUVUUU...VUVU, NV21 22 FMT_YUV420SP, // 23 YYY...UVUVUV...UVUV, NV12 24 FMT_YVU420P, // 25 YYY...VVV...UUU 26 FMT_YUV420P, // 27 YYY...UUU...VVV 28 FMT_GRAYSCALE, 29 FMT_BGGR6, // 6- bit 30 Bayer format with a BGGR pattern. 31 FMT_GBRG6, // 6- bit 32 Bayer format with a GBRG pattern. 33 FMT_GRBG6, // 6- bit 34 Bayer format with a GRBG pattern. 35 FMT_RGGB6, // 6- bit 36 Bayer format with a RGGB pattern. 37 FMT_BGGR8, // 8- bit 38 Bayer format with a BGGR pattern. 39 FMT_GBRG8, // 8- bit 40 Bayer format with a GBRG pattern. 41 FMT_GRBG8, // 8- bit Bayer format with a GRBG pattern. FMT_RGGB8, // 8- bit Bayer format with a RGGB pattern. FMT_BGGR10, // 10- bit Bayer format with a BGGR pattern. FMT_GBRG10, // 10- bit Bayer format with a GBRG pattern. FMT_GRBG10, // 10- bit

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/238099bf5d1c8fbeb7ba29edb518902d57c1b7de7349ca98de4e8d28f44972be.jpg)

# 2.2. Fit

Object fit method

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>FIT_NONE: no object fit, keep original
FIT_FILL: width to new width, height to new height, may be stretch
FIT_CONTAIN: keep aspect ratio, fill blank area with black color
FIT_COVER: keep aspect ratio, crop image to fit new size
FIT_MAX:</td></tr></table>

$\zeta + +$  definition code:

1 enum Fit 2 { 3 FIT_NONE  $=$  - 1, // no object 4 fit, keep original 5 FIT_FILL  $= 0$  // width to 6 new width, height to new height, may 7 be stretch 8 FIT_CONTAIN, // keep aspect ratio, fill blank area with black color FIT_COVER, // keep aspect ratio, crop image to fit new size FIT_MAX }

# 2.3. ResizeMethod

Resize method

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>NEAREST:
BILINEAR:
BICUBIC:
AREA:
LANCZOS:
HAMMING:
RESIZE_METHOD_MAX:</td></tr></table>

$\zeta + +$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/0c9b3d2ce78e0dfbbd2ffe22b03d68c6c2011863d69a192b5b2fc65671bf60c0.jpg)

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/d3af6fd03a18cd8f7852e6c9e4335139018a0659d6ca68d6cdb55b5e3deccd78.jpg)

# 2.4. ApriltagFamilies

Family of apriltag

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>TAG16H5:
TAG25H7:
TAG25H9:
TAG36H10:
TAG36H11:
ARTOOLKIT:</td></tr></table>

$\mathtt{C + + }$  defination code:

<table><tr><td>1</td><td>enum ApriltagFamilies</td></tr><tr><td>2</td><td>{</td></tr><tr><td>3</td><td>TAG16H5 = 1,</td></tr><tr><td>4</td><td>TAG25H7 = 2,</td></tr><tr><td>5</td><td>TAG25H9 = 4,</td></tr><tr><td>6</td><td>TAG36H10 = 8,</td></tr><tr><td>7</td><td>TAG36H11 = 16,</td></tr><tr><td>8</td><td>ARTOOLKIT = 32</td></tr><tr><td>9</td><td>}</td></tr></table>

# 2.5. TemplateMatch

Template match method

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>SEARCH_EX: Exhaustive search
SEARCH_DS: Diamond search</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/046b947e160a8aafdc8f6b616bea98f158f11feac285954ecdaf6fc019b67ef1.jpg)

# 2.6. CornerDetector

CornerDetector class

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>CORNER_FAST:
CORNER_AGAST:</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/b60e4b5c0dc0dc1bad41db1a4496ae09886dd91192ad3ac59cb1c2249fdd82bb.jpg)

# 2.7. EdgeDetector

EdgeDetector class

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>EDGE_CANNY:
EDGE_SIMPLE:</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/b31353eef92c70b440329518cf4cc625ec773841213bb833c1bc56309a270402.jpg)

# 2.8. FlipDir

FlipDir

<table><tr><td>item</td><td>describe</td></tr><tr><td rowspan="3">values</td><td>X:</td></tr><tr><td>Y:</td></tr><tr><td>XY:</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/738822985a656fc173859c7ae57ed907f9a5f6fd44a5c24341ad5b78c63813c0.jpg)

# 2.9. QRCodeDecoderType

QRCode decode type class

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>QRCODE_DECODER_TYPE_ZBAR:
QRCODE_DECODER_TYPE_QUIRC:</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1</td><td>enum class QRCodeDecoderType {</td></tr><tr><td>2</td><td>QRCODE_DECODER_TYPE_ZBAR,</td></tr><tr><td>3</td><td>QRCODE_DECODER_TYPE_QUIRC</td></tr><tr><td>4</td><td>}</td></tr></table>

# 2.10. LineType

Line type class

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>LINE_NORMAL:
LINE_CROSS:
LINE_T:
LINE_L:</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1</td><td>enum class LineType {</td></tr><tr><td>2</td><td>LINE_NORMAL,</td></tr><tr><td>3</td><td>LINE_CROSS,</td></tr><tr><td>4</td><td>LINE_T,</td></tr><tr><td>5</td><td>LINE_L,</td></tr><tr><td>6</td><td>}</td></tr></table>

# 3. Variable

# 3.1. fmt_size

Image format size in bytes

<table><tr><td>item</td><td>description</td></tr><tr><td>attention</td><td>It&#x27;s a copy of this variable in MaixPy, so change it in C++ (e.g. update var in hello function) will not take effect the var in MaixPy.
So we add const for this var to avoid this mistake.</td></tr><tr><td rowspan="22">value</td><td>{</td></tr><tr><td>3,</td></tr><tr><td>3,</td></tr><tr><td>4,</td></tr><tr><td>4,</td></tr><tr><td>2,</td></tr><tr><td>2,</td></tr><tr><td>2,</td></tr><tr><td>1.5,</td></tr><tr><td>1.5,</td></tr><tr><td>1.5,</td></tr><tr><td>1.5,</td></tr><tr><td>1, // grayscale</td></tr><tr><td>0.75, // 6-bit Bayer format</td></tr><tr><td>0.75, // 6-bit Bayer format</td></tr><tr><td>0.75, // 6-bit Bayer format</td></tr><tr><td>0.75, // 6-bit Bayer format</td></tr><tr><td>1, // 8-bit Bayer format</td></tr><tr><td>1, // 8-bit Bayer format</td></tr><tr><td>1, // 8-bit Bayer format</td></tr><tr><td>1, // 8-bit Bayer format</td></tr><tr><td>1.25, // 10-bit Bayer format</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td rowspan="13"></td><td>1.25, // 10-bit Bayer format</td></tr><tr><td>1.25, // 10-bit Bayer format</td></tr><tr><td>1.25, // 10-bit Bayer format</td></tr><tr><td>1.5, // 12-bit Bayer format</td></tr><tr><td>1.5, // 12-bit Bayer format</td></tr><tr><td>1.5, // 12-bit Bayer format</td></tr><tr><td>0, // uncompereed_max</td></tr><tr><td>0, // compressed_min</td></tr><tr><td>1, // jpeg</td></tr><tr><td>1, // png</td></tr><tr><td>0, // compressed_max</td></tr><tr><td>0 // invalid</td></tr><tr><td>}</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

<table><tr><td>1</td><td>const std::vector&lt;float&gt; fmt_size = {</td></tr><tr><td>2</td><td>3,</td></tr><tr><td>3</td><td>3,</td></tr><tr><td>4</td><td>4,</td></tr><tr><td>5</td><td>4,</td></tr><tr><td>6</td><td>2,</td></tr><tr><td>7</td><td>2,</td></tr><tr><td>8</td><td>2,</td></tr><tr><td>9</td><td>2,</td></tr><tr><td>10</td><td>1.5,</td></tr><tr><td>11</td><td>1.5,</td></tr><tr><td>12</td><td>1.5,</td></tr><tr><td>13</td><td>1.5,</td></tr><tr><td>14</td><td>1, // grayscale</td></tr><tr><td>15</td><td>0.75,   // 6-bit Bayer format</td></tr><tr><td>16</td><td>0.75,   // 6-bit Bayer format</td></tr><tr><td>17</td><td>0.75,   // 6-bit Bayer format</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/3e72bcc17d6285ab4b5742178178f5da0dcaee14ef10c50e7cee997a6d729eb5.jpg)

# 3.2. fmt_names

Image format string

<table><tr><td>item</td><td>description</td></tr><tr><td rowspan="2">value</td><td>{</td></tr><tr><td>&quot;RGB888&quot;,
&quot;BGR888&quot;,
&quot;RGBA888&quot;,
&quot;BGRA8888&quot;,</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>&quot;RGB565&quot;,
&quot;BRG565&quot;,
&quot;YUV422SP&quot;,
&quot;YUV422P&quot;,
&quot;YUV420SP&quot;,
&quot;YUV420SP&quot;,
&quot;YUV420P&quot;,
&quot;YUV420P&quot;,
&quot;GRAYSCALE&quot;,
&quot;BGGR6&quot;,
&quot;GBRG6&quot;,
&quot;GRBG6&quot;,
&quot;RG6B6&quot;,
&quot;BGGR8&quot;,
&quot;GBRG8&quot;,
&quot;GRBG8&quot;,
&quot;RG6B8&quot;,
&quot;BGGR10&quot;,
&quot;GBRG10&quot;,
&quot;GRBG10&quot;,
&quot;RG6B10&quot;,
&quot;BGGR12&quot;,
&quot;GBRG12&quot;,
&quot;GRBG12&quot;,
&quot;RG6B12&quot;,
&quot;UNCOMPRESSED_MAX&quot;,
&quot;COMPRESSED_MIN&quot;,
&quot;JPEG&quot;,
&quot;PNG&quot;,
&quot;COMPRESSED_MAX&quot;,</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>&quot;INVALID&quot;</td></tr><tr><td></td><td>}</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1</td><td>const std::vector&lt;std::string&gt;</td></tr><tr><td>2</td><td>fmt_names = {</td></tr><tr><td>3</td><td>&quot;RGB888&quot;,</td></tr><tr><td>4</td><td>&quot;BGR888&quot;,</td></tr><tr><td>5</td><td>&quot;RGBA8888&quot;,</td></tr><tr><td>6</td><td>&quot;BGRA8888&quot;,</td></tr><tr><td>7</td><td>&quot;RGB565&quot;,</td></tr><tr><td>8</td><td>&quot;BGR565&quot;,</td></tr><tr><td>9</td><td>&quot;YUV422SP&quot;,</td></tr><tr><td>10</td><td>&quot;YUV422P&quot;,</td></tr><tr><td>11</td><td>&quot;YUV420SP&quot;,</td></tr><tr><td>12</td><td>&quot;YUV420SP&quot;,</td></tr><tr><td>13</td><td>&quot;YUV420P&quot;,</td></tr><tr><td>14</td><td>&quot;YUV420P&quot;,</td></tr><tr><td>15</td><td>&quot;GRAYSCALE&quot;,</td></tr><tr><td>16</td><td>&quot;BGGR6&quot;,</td></tr><tr><td>17</td><td>&quot;GBRG6&quot;,</td></tr><tr><td>18</td><td>&quot;GRBG6&quot;,</td></tr><tr><td>19</td><td>&quot;RG6B6&quot;,</td></tr><tr><td>20</td><td>&quot;BGGR8&quot;,</td></tr><tr><td>21</td><td>&quot;GBRG8&quot;,</td></tr><tr><td>22</td><td>&quot;GRBG8&quot;,</td></tr><tr><td>23</td><td>&quot;RG6B8&quot;,</td></tr><tr><td>24</td><td>&quot;BGGR10&quot;,</td></tr><tr><td>25</td><td>&quot;GBRG10&quot;,</td></tr><tr><td>26</td><td>&quot;GBRG10&quot;,</td></tr><tr><td>27</td><td>&quot;RG6B10&quot;,</td></tr><tr><td>28</td><td>&quot;BGGR12&quot;,</td></tr><tr><td>29</td><td>&quot;GBRG12&quot;,</td></tr><tr><td>30</td><td>&quot;GRBG12&quot;,</td></tr><tr><td>31</td><td>&quot;RG6B12&quot;,</td></tr><tr><td>32</td><td>&quot;UNCOMPRESSED_MAX&quot;,</td></tr><tr><td>33</td><td>&quot;COMPRESSED_MIN&quot;,</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/74d0dfeb0da445b3974079693a58dadca6df635d6a0b29d9b11ed0094cee1add.jpg)

# 3.3. COLOR_WHITE

Predefined color white

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(255, 255, 255)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR_WHITE = image::Color::from_rgb(255, 255, 255)

# 3.4. COLOR_BLACK

Predefined color black

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(0, 0, 0)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR_BLACK = image::Color::from_rgb(0, 0, 0)

# 3.5. COLOR RED

Predefined color red

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(255, 0, 0)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR RED = image::Color::from_rgb(255, 0, 0)

# 3.6. COLOR GREEN

Predefined color green

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(0, 255, 0)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR GREEN = image::Color::from_rgb(0, 255, 0)

# 3.7. COLOR BLUE

Predefined color blue

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(0, 0, 255)</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

const image::Color COLOR_BLUE = image::Color::from_rgb(0, 0, 255)

# 3.8. COLOR_YELLOW

Predefined color yellow

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(255, 255, 0)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

const image::Color COLOR_YELLOW = image::Color::from_rgb(255, 255, 0)

# 3.9. COLOR PURPLE

Predefined color purple

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(143, 0, 255)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR_PURPLE = image::Color::from_rgb(143, 0, 255)

# 3.10. COLOR_ORANGE

Predefined color orange

<table><tr><td>Item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(255, 127, 0)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR_ORANGE = image::Color::from_rgb(255, 127, 0)

# 3.11. COLOR_GRAY

Predefined color gray

<table><tr><td>item</td><td>description</td></tr><tr><td>value</td><td>image::Color::from_rgb(127, 127, 127)</td></tr><tr><td>readonly</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 const image::Color COLOR_GRAY = image::Color::from_rgb(127, 127, 127)

# 4. Function

# 4.1. resize_map_pos

1 def resize_map_pos(w_in: int, h_in: int, w_out: int, h_out: int, fit: Fit, x: int, y: int, w: int = - 1, h: int = - 1) - > list[int]

map point position or rectangle position from one image size to another image size(resize)

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>int: h_out target image height
fit: resize method, see maix.image.Fit
x: original point x, or rectagl e left-top point&#x27;s x
y: original point y, or rectagl e left-top point&#x27;s y
w: original rectagl e width, can be -1 if not use this arg, default -1.
h: original rectagl e height, can be -1 if not use this arg, default -1.</td></tr><tr><td>return</td><td>list type. [x, y] if map point, [x, y, w, h] if resize rectangle.</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> resize_map_pos(int w_in, int h_in, int w_out, int h_out, image::Fit fit, int x, int y, int w = - 1, int h = - 1)

# 4.2. resize_map_pos_reverse

1 def resize_map_pos_reverse(w_in: int, h_in: int, w_out: int, h_out: int, fit: Fit, x: int, y: int, w: int = - 1, h: int = - 1) - > list[int]

reverse resize_map_pos method, when we call image.resize method resiz image 'a' to image 'b', we want to known the original position on 'a' with a knew point on 'b'

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>int: h_out image height after resized
fit: resize method, see maix.image.Fit
x: point on resized image x, or rectagl
left-top point&#x27;s x
y: original point y, or rectagl left-top
point&#x27;s y
w: original rectagl width, can be -1 if
not use this arg, default -1.
h: original rectagl height, can be -1 if
not use this arg, default -1.</td></tr><tr><td>return</td><td>list type, [x, y] if map point, [x, y, w, h] if
resize rectangle.</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> resize_map_pos_reverse(int w_in, int h_in, int w_out, int h_out, image::Fit fit, int x, int y, int w = - 1, int h = - 1)

# 4.3. load

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/d9dd9d7bfd2149b0dec7f80b2d7d94137fbf4af621b56cb3cafc0e1d706f879b.jpg)

Load image from file, and convert to Image object

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>path: image file path
format: read as this format, if not match, will convert to this format, by default is RGB888</td></tr><tr><td>return</td><td>Image object, if load failed, will return
None(nullptr in C++), so you should care about it.</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Image *load(const char *path,
  image::Format format = image::Format::FMT_RGB888)</td></tr></table>

# 4.4. from_bytes

1 def from_bytes(width: int, height: int, format: Format, data: maix.Bytes(bytes), copy: bool = True) - > Image

Create image from bytes

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>width: image width
height: image height</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>format: image format
data: image data, if data is None, will malloc memory for image data
If the image is in jpeg format, data must be filled in.
copy: if true and data is not None, will copy data to new buffer, else will use data directly. default is true to avoid memory leak.
Use it carefully!!!</td></tr><tr><td>return</td><td>Image object</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *from_bytes(int width, int height, image::Format format, Bytes *data, bool copy = true)

# 4.5. load_font

1 def load_font(name: str, path: str, size: int = 16) - > maix.err.Err

Load font from file

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>name: font name, used to identify font path: font file path, support ttf, ttc, otf size: font size, font height, by default is 16</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>error code, err::ERR_NONE is ok, other is error</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err load_font(const std::string &name, const char *path, int size = 16)

# 4.6. set_default_font

Set default font, if not call this method, default is hershey_plain

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>name: font name, supported names can be get by fonts()</td></tr><tr><td>return</td><td>error code, err::ERR_NONE is ok, other is error</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err set_default_font(const std::string &name)

# 4.7. fonts

1 | def fonts() - > list[str]

Get all loaded fonts

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>all loaded fonts, string list type</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::string> *fonts()

# 4.8. string_size

1 | def string_size(string: str, scale: float = 1, thickness: int = 1, font: str = '') - > Size

Get text rendered width and height

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>string: text content
scale: font scale, by default(value is 1)
thickness: text thickness(line width), by default(value is 1)</td></tr><tr><td>return</td><td>text rendered width and height, [width, height]</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Size string_size(std::string string, float scale = 1, int thickness = 1, const std::string &font = '')

# 4.9. cv2image

1 def cv2image(array: numpy.ndarray[np.array.uint8], bgr: bool = True, copy: bool = True) - > Image

OpenCV Mat(numpy array object) to Image object

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>array: numpy array object, must be a 3-dim or 2-dim continuous array with shape hwc or hw
bgr: if set bgr, the return image will be marked as BGR888 or BGRA8888
format(only mark, not ensure return image is real BGR format), grayscale will ignore this arg.
copy: if true, will alloc new buffer and copy data, else will directly use array&#x27;s data buffer, default true.
Use this arg carefully, when set to false, then array MUST keep alive until we don&#x27;t use the return img of this func, or will cause program crash.</td></tr><tr><td>return</td><td>Image object</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Image *cv2image(py::array_t <uint8_t, py::array::c_style> array, bool bgr = true, bool copy = true)

# 4.10. image2cv

1 def image2cv(img: Image, ensure_bgr: bool = True, copy: bool = True) - > numpy.ndarray numpy.uint8]

Image object to OpenCV Mat(numpy array object)

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>img: Image object, maix.image.Image type.
ensure_bgr: auto convert to BGR888 or BGRA8888 if img format is not BGR or BGRA, if set to false, will not auto convert and directly use img&#x27;s data, default true.
If copy is false, ensure_bgr always be false.
copy: Whether alloc new image and copy data or not, if ensure_bgr and img is not bgr or bgra format, always copy,
if not copy, array object will directly use img&#x27;s data buffer, will faster but change array will affect img&#x27;s data, default true.</td></tr><tr><td>attention</td><td>take care of ensure_bgr and copy param.</td></tr><tr><td>return</td><td>numpy array object</td></tr></table>

$\mathtt{C + + }$  defination code:

1 py::array_t<uint8_t, py::array::c_style>

# 5. Class

# 5.1. Size

Image size type

$\mathtt{C + + }$  defination code:

1 class Size

# 5.1.1. init

1 def init_(self, width: int = 0, height: int = 0) - > None

Construct a new Size object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: image width
height: image height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 Size(int width = 0, int height = 0)

# 5.1.2. width

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/ad30ffa9547d196c9147c19a0b72fab3e92a8bc98122ed08d8af5a1f167eb9d0.jpg)

width of size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: set new width, if not set, only
return current width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int width(int width = - 1)

# 5.1.3. height

<table><tr><td>1 | def height(self, height: int = -1) -&amp;gt; int</td></tr></table>

height of size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>height: set new height, if not set, only return current height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int height(int height = - 1)

# 5.1.4. __getitem__

1 def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: 0 for width, 1 for height</td></tr><tr><td>return</td><td>int&amp;amp; width or height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int &operator[](int index)

# 5.1.5. __str__

1 def __str__(self) - > str

to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::string __str__(

# 5.2. Line

Line class

$\mathtt{C + + }$  definition code:

1 | class Line

# 5.2.1. init

1 | def init__(self, x1: int, y1: int, x2: int, y2: int, magnitude: int = 0, theta: int = 0, rho: int = 0) - > None

Line constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x1: coordinate x1 of the straight line
y1: coordinate y1 of the straight line
x2: coordinate x2 of the straight line
y2: coordinate y2 of the straight line
magnitude: magnitude of the straight line after Hough transformation
theta: angle of the straight line after Hough transformation</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>rho: p-value of the straight line after 
Hough transformation</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

Line(int x1, int y1, int x2, int y2, int magnitude = 0, int theta = 0, int rho = 0)

# 5.2.2. __getitem__

<table><tr><td>1 | def __getitem__(self, index: int) -&amp;gt; int</td></tr></table>

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] get x1 of line
[1] get y1 of line
[2] get x2 of line
[3] get y2 of line
[4] get length of line
[5] get magnitude of the straight line after Hough transformation
[6] get angle of the straight line after Hough transformation (0-179 degrees)
[7] get p-value of the straight line after Hough transformation</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int & getitem_(int index)

# 5.2.3. x1

1 def x1(self) - > int

get x1 of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x1 of the line, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int x1()

# 5.2.4. y1

1 def y1(self) - > int

get y1 of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y1 of the line, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y1

# 5.2.5. x2

get x2 of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x2 of the line, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x2

# 5.2.6. y2

<table><tr><td>1 | def y2(self) -&amp;gt; int</td></tr></table>

get y2 of line

<table><tr><td>2025/6/22 16:57</td><td>maix.image - MaixPy</td></tr><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y2 of the line, type is int</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int y2()</td></tr></table>

# 5.2.7. length

get length of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return length of the line, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int length()

# 5.2.8. magnitude

def magnitude(self) - > int

get magnitude of the straight line after Hough transformation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return magnitude, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int magnitude()

# 5.2.9. theta

get angle of the straight line after Hough transformation (0- 179 degrees)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return angle, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int theta()

# 5.2.10. rho

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/ea312d451f5f654b8f7c04d8405153deec3f2034612398d9b72d16f1007e60b0.jpg)

get p- value of the straight line after Hough transformation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return p-value, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int rho()

# 5.3. Rect

Rect class

$\mathtt{C + + }$  definition code:

class Rect

# 5.3.1. init

1 def init_(self, corners: list[list[int]], x: int, y: int, w: int, h: int, magnitude: int = 0) - > None

Rect constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>corners: corners of rect
x: coordinate x of the straight line
y: coordinate y of the straight line
w: coordinate w of the straight line
h: coordinate h of the straight line
magnitude: magnitude of the straight line after Hough transformation</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Rect(std::vector<std::vector<int>> &corners, int x, int y, int w, int h, int magnitude = 0)

# 5.3.2. __getitem__

1 | def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] get x of rect
[1] get y of rect
[2] get w of rect
[3] get h of rect</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>[4] get magnitude of the straight line after Hough transformation</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int &amp;amp;__getitem__(int index)</td></tr></table>

# 5.3.3. corners

<table><tr><td>1 | def corners(self) -&amp;gt; list[list[int]]</td></tr></table>

get corners of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the coordinate of the rect.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<std::vector<int>> corners()

# 5.3.4. rect

<table><tr><td>1 | def rect(self) -&amp;gt; list[int]</td></tr></table>

get rectangle of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the rectangle of the rect. format is {x, y, w, h}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> rect()

# 5.3.5.x

get x of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the rect, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x()

# 5.3.6.y

1 def y(self) - > int

get y of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the rect, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y()

# 5.3.7.w

get w of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return w of the rect, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int w()

# 5.3.8.h

1 def h(self) - > int

get h of rect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return h of the rect, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int h()

# 5.3.9. magnitude

get magnitude of the straight line after Hough transformation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return magnitude, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int magnitude()

# 5.4. Circle

circle class

$\mathtt{C + + }$  defination code:

1 class Circle

# 5.4.1. init

1 def init self,x: int,y: int,r: int,magnitude: int) - > None

Circle constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: coordinate x of the circle
y: coordinate y of the circle
r: coordinate r of the circle
magnitude: coordinate y2 of the straight line</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 Circle(int x, int y, int r, int magnitude)

# 5.4.2. getitem

1 def getitem self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] get x of circle
[1] get y of circle
[2] get r of circle
[3] get magnitude of the circle after Hough transformation</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int &__getitem__int index

# 5.4.3. x

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/f21ea2a17d90ddb3344268fa33be8ecccb9b7bfbca2a68b02d570cf8848ca421.jpg)

get x of circle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the circle, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int x()

# 5.4.4. y

1 | def y(self) - > int

get y of circle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the circle, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y()

# 5.4.5. r

1 | def r(self) - > int

get r of circle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return r of the circle, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int r()

# 5.4.6. magnitude

1 | def magnitude(self) - > int

get magnitude of the circle after Hough transformation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return magnitude, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int magnitude()

# 5.5. Blob

Blob class

$\mathtt{C + + }$  defination code:

class Blob

# 5.5.1. init

1 | def __init__(self, rect: list[int], corners: list[list[int]], mini_corners: list[list[int]], cx: float, cy: float, pixels: int, rotation: float, code:

int, count: int, perimeter: int, roundness: float, x_hist_bins: list[int], y_hist_bins: list[int]) - > None

# Blob constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>rect: blob rect, type is std::vector
corners: blob corners, type is
std::vector&lt;std::vector&amp;gt; 
minicorners: blob minicorners, type is
std::vector&lt;std::vector&amp;gt; 
cx: blob center x, type is float
cy: blob center y, type is float
pixels: blob pixels, type is int
rotation: blob rotation, type is float
code: blob code, type is int
count: blob count, type is int
perimeter: blob perimeter, type is int
roundness: blob roundness, type is float
x_hist_bins: blob x_hist_bins, type is
std::vector
y_hist_bins: blob y_hist_bins, type is
std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Blob(std::vector<int> & rect, std::vector<std::vector<int>> &corners,

maix.image - MaixPy

std::vector<std::vector<int>> &mini corners, float cx, float cy, int pixels, float rotation, int code, int count, int perimeter, float roundness, std::vector<int> &xHistbins, std::vector<int> &yHistbins)

# 5.5.2. _getitem

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] Returns the blob&#x27;s bounding box x coordinate
[1] Returns the blob&#x27;s bounding box y coordinate
[2] Returns the blob&#x27;s bounding box w coordinate
[3] Returns the blob&#x27;s bounding box h coordinate
[4] Returns the number of pixels that are part of this blob
[5] Returns the centroid x position of the blob
[6] Returns the centroid y position of the blob</td></tr><tr><td>return</td><td>int&amp;amp; width or height</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  definition code:

int &__getitem__(int index)

# 5.5.3. corners

1 def corners(self) - > list[list[int]]

get blob corners

<table><tr><td>item</td><td>description</td><td></td></tr><tr><td>type</td><td>func</td><td></td></tr><tr><td>return</td><td>Returns a list of 4 (x,y) tuples of the 4 corners of the object.
(x0, y0)        (x1, y1)</td><td></td></tr><tr><td>static</td><td>False</td><td></td></tr></table>

$\bar{\zeta} ++$  definition code:

std::vector<std::vector<int>> corners()

# 5.5.4. mini_corners

1 | def mini_corners(self) - > list[list[int]]

get blob mini corners

<table><tr><td>item</td><td>description</td><td></td></tr><tr><td>type</td><td>func</td><td></td></tr><tr><td>return</td><td>Returns a list of 
4 (x,y) tuples of 
the 4 corners 
than bound the 
min area 
rectangle of the 
blob. 
(x0, 
y0)          (x1, 
y1)</td><td></td></tr><tr><td>static</td><td>False</td><td></td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<std::vector<int>> mini_corners()

# 5.5.5. rect

1 | def rect(self) - > list[int]

get blob rect

<table><tr><td>item</td><td>description</td><td></td><td></td></tr><tr><td>type</td><td>func</td><td></td><td></td></tr><tr><td>return</td><td>Returns the center coordinates and width and height of the rectangle. format is (x, y, w, h) w (x, y)</td><td>h</td><td></td></tr><tr><td>static</td><td>False</td><td></td><td></td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/fe2f81b29e4185ca1b797cabccbc619fd4b09e5eb173d983ef39f93e46dddcf7.jpg)

# 5.5.6. x

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/1e754fcd0954d7c556b0caf7049f36bc071e3a9402356d774cdea8d00e194d17.jpg)

get blob x of the upper left coordinate

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the x coordinate of the upper left corner of the rectangle.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int x()</td></tr></table>

# 5.5.7.y

get blob y of the upper left coordinate

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the y coordinate of the upper left corner of the rectangle.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  definition code:

1 int y

# 5.5.8.w

<table><tr><td>1 | def w(self) -&amp;gt; int</td></tr></table>

get blob width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the blob&#x27;s bounding box w coordinate</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defnati on code:

1 int w

# 5.5.9.h

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/f1b18e02504d445f1b60862e6b97d896a535d0899af81052e1bc51432595a6d0.jpg)

get blob height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the blob&#x27;s bounding box h coordinate</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defnati on code:

1 int h

# 5.5.10.pixels

1 def pixels(self) - > int

get blob pixels

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the number of pixels that are part of this blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/7a843c2116699c88d423e917fef74d6553c85a396cb7bbe5c41333d1ad7d16bf.jpg)

# 5.5.11. cx

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/1358cf07c0d06fbe4a8d229fb969197a1b9ed2d17b596c440f9c24223dbba7ac.jpg)

get blob center x

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the centroid x position of the blob</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/6c0e13b11625955b1e78ff2d78f0eaf33e1729994a02d7a526c856ffbbd1037c.jpg)

# 5.5.12. cy

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/96523d652ceafa97e38b85318659bb3bfbbae684a6ba28e66b33b3657ba447cc.jpg)

get blob center y

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the centroid y position of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/b37c9c37aa64c8ffb22f9ea220756ac6be805bdca52720a0f7713a6b27b1a36e.jpg)

# 5.5.13.cxf

<table><tr><td>1 | def cxf(self) -&amp;gt; float</td></tr></table>

get blob center x

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the centroid x position of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/7c6bda65ea7885fc41be312d0a652646ce7acf2d8ed20250b1dba8e9512fabc6.jpg)

# 5.5.14. cyf

1 def cyf(self) - > float

get blob center y

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the centroid y position of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/c4c7f14648c57c7429a420efd2c4d3dc209e65f66cd13332935d9dba281a157e.jpg)

# 5.5.15. rotation

<table><tr><td>1 | def rotation(self) -&amp;gt; float</td></tr></table>

get blob rotation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the rotation of the blob in radians (float). If the blob is like a pencil or pen this value will be unique for 0-180 degrees.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 float rotation()

# 5.5.16. rotation_rad

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/d1b84de708c3997ee713f0be9f781ed6be7130b15570a4a95cd01920c135efcb.jpg)

get blob rotation_rad

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the rotation of the blob in radians</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 float rotation_rad()

# 5.5.17. rotation_deg

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/f63a0033ee2ab9ee6a9007589b55f62a071b20624947a4f30b4456aa8ea2ec24.jpg)

get blob rotation_deg

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the rotation of the blob in degrees.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int rotation_deg()</td></tr></table>

# 5.5.18. code

get blob code

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a 32-bit binary number with a bit set in it for each color threshold that&#x27;s part of this blob</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int code()</td></tr></table>

# 5.5.19. count

<table><tr><td>1 | def count(self) -&amp;gt; int</td></tr></table>

get blob count

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the number of blobs merged into this blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/32b02faab1da04a24a857bdbe5724ea0e7cac1bbc2362b9290d488124daceeb3.jpg)

# 5.5.20. perimeter

get blob merge_cnt

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the number of pixels on this blob&#x27;s perimeter.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ defination code:</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/1711ba423a67c798ec34ffb0d5a95b0ff7ad38c375d40dc73bce32122948c2b8.jpg)

# 5.5.21. roundness

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/edc08bb2305312433fb7e99017ff6570426fdee6ee44fe7d4a9ee9746d2339f5.jpg)

get blob roundness

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a value between 0 and 1
representing how round the object is</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float roundness()

# 5.5.22. elongation

get blob elongation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>returnReturns</td><td>a value between 0 and 1
representing how long (not round) the object is</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float elongation()

# 5.5.23.area

1 def area(self) - > int

get blob area

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the area of the bounding box around the blob</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int area()</td></tr></table>

# 5.5.24. density

<table><tr><td>1 | def density(self) -&amp;gt; float</td></tr></table>

get blob density

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the density ratio of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | float density()

# 5.5.25. extent

1 | def extent(self) - > float

Alias for blob.density()

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the density ratio of the blob</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | float extent()</td></tr></table>

# 5.5.26. compactness

<table><tr><td>1 | def compactness(self) -&amp;gt; float</td></tr></table>

get blob compactness

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the compactness ratio of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | float compactness()

# 5.5.27. solidity

1 def solidity(self) - > float

get blob solidity

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the solidity ratio of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | float solidity()

# 5.5.28. convexity

<table><tr><td>1 | def convexity(self) -&amp;gt; float</td></tr></table>

get blob convexity

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a value between 0 and 1
representing how convex the object is</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float convexity()

# 5.5.29. x_hist_bins

1 def x_hist_bins(self) - > list[int]

get blob x_hist_bins

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the x_hist_bins of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> x_hist_bins()

# 5.5.30. y hist bins

1 def y_hist_bins(self) - > list[int]

get blob y_hist_bins

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the y_hist_bins of the blob</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<int> y_hist_bins()

# 5.5.31.major_axis_line

1 def major_axis_line(self) - > list[int]

get blob major_axis_line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a line tuple (x1, y1, x2, y2) of the minor axis of the blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<int> major_axis_line()

# 5.5.32.minor_axis_line

1 def minor_axis_line(self) - > list[int]

get blob minor_axis_line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a line tuple (x1, y1, x2, y2) of the minor axis of the blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<int> minor_axis_line()

# 5.5.33. enclosing_circle

1 | def enclosing_circle(self) - > list[int]

get blob enclosing_circle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns a circle tuple (x, y, r) of the circle that encloses the min area rectangle of a blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<int> enclosing_circle()

# 5.5.34. enclosed_ellipse

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/1073a2bc6a49cdf7fbc7e045f90c6443ebc8d4a8a9d578809af52749a267d71a.jpg)

get blob enclosed_ellipse

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns an ellipse tuple (x, y, rx, ry, rotation) of the ellipse that fits inside of the min area rectangle of a blob.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<int> enclosed_ellipse()

# 5.6. QRCode

QRCode class

$\mathtt{C + + }$  defination code:

class QRCode

# 5.6.1. init

1 def init_(self, rect: list[int], corners: list[list[int]], payload: str, version: int, ecc_level: int, mask: int, data_type: int, eci: int) - > None

QRCode constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>rect: rect of corners, type is std::vector
corners: corners of QRCode
payload: payload of the QRCode
version: version of the QRCode
ecc_level: ecc_level of the QRCode
mask: mask of the QRCode
data_type: data_type of the QRCode
eci: eci of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | QRCode(std::vector<int> & rect, std::vector<std::vector<int>> &corners, std::string &payload, int version, int ecc_level, int mask, int data_type, int eci)

# 5.6.2. __getitem__

1 | def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] Returns the qrcode&#x27;s bounding box x coordinate</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>[1] Returns the qrcode&#x27; s bounding box
y coordinate
[2] Returns the qrcode&#x27; s bounding box
w coordinate
[3] Returns the qrcode&#x27; s bounding box
h coordinate
[4] Not support this index, try to use payload() method
[5] Returns the version of qrcode
[6] Returns the error correction level of qrcode
[7] Returns the mask of qrcode
[8] Returns the datatype of qrcode
[9] Returns the eci of qrcode</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int &__getitem__(int index)

# 5.6.3. corners

<table><tr><td>1 | def corners(self) -&amp;gt; list[list[int]]</td></tr></table>

get coordinate of QRCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>return the coordinate of the QRCode.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<std::vector<int>> corners()

# 5.6.4. rect

get rectangle of QRCode

<table><tr><td>Item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the rectangle of the QRCode.
format is {x, y, w, h}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<int> rect()

# 5.6.5. x

get x of QRCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the QRCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x

# 5.6.6. y

get y of QRCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the QRCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y

# 5.6.7.w

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/3e8984fa9e6de6f4ba6fd3dd55d988620e5b38926f76a3f3a13501c36c3a8316.jpg)

get w of QRCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return w of the QRCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int w

# 5.6.8.h

1 def h(self) - > int

get h of QRCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return h of the QRCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int h

# 5.6.9.payload

1 def payload(self) - > str

get QRCode payload

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return area of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::string payload()

# 5.6.10. version

get QRCode version

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return version of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int version()

# 5.6.11. ecc_level

get QRCode error correction level

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return error correction level of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 int ecc_level()

# 5.6.12. mask

1 def mask(self) - > int

get QRCode mask

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return mask of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 int mask()

# 5.6.13. data_type

1 def data_type(self) - > int

get QRCode dataType

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return mask of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int data_type()

# 5.6.14. eci

get QRCode eci

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return data of the QRCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int eci()

# 5.6.15. is numeric

<table><tr><td>1 | def is_numeric(self) -&amp;gt; bool</td></tr></table>

check QRCode is numeric

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return true if the result type of the QRCode is numeric</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/dbbbcad4244bd1c98bbeb4a1f5e22274a332a7f73ab6ef089034020bea2e9acc.jpg)

# 5.6.16. is_alphanumeric

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/637aab763ae45e674fd69863f2b01c885b7b4c7833eaecfed041a94fc85a5ff3.jpg)

check QRCode is alphanumeric

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return true if the result type of the QRCode is alphanumeric</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ defination code:</td></tr><tr><td colspan="2">1 | bool is_alphanumeric()</td></tr></table>

# 5.6.17. is_binary

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/78543f4ae501d1df121fb1523eaed15e98755e376da14ad78cd6a6c12bbbf301.jpg)

check QRCode is binary

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return true if the result type of the QRCode is binary</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 bool is_binary()

# 5.6.18. is_kanji

<table><tr><td>1 | def is_kanji(self) -&amp;gt; bool</td></tr></table>

check QRCode is kanji

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return true if the result type of the QRCode is kanji</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 bool is_kanji()

# 5.7. AprilTag

AprilTag class

$\mathtt{C + + }$  defination code:

1 class AprilTag

# 5.7.1. init

1 def init_(self, rect: list[int], corners: list[list[int]], id: int, family: int, centroid_x: float, centroid_y: float, rotation: float, decision_margin: float, hamming: int, goodness: float, x_translation: float, y_translation: float, z_translation: float, x_rotation: float, y_rotation: float, z_rotation: float) - > None

AprilTag constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>rect: Includes the top-left corner and the width and height of the rectangle.
format is {x, y, w, h}, type is std::vector
corners: Includes the four corners of the rectangle. format is {{x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}}, type is
std::vector&lt;std::vector&amp;gt;id: The id of the AprilTag
family: The family of the AprilTag</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>centroid_x: The x coordinate of the center of the AprilTag
centroid_y: The y coordinate of the center of the AprilTag
rotation: The rotation of the AprilTag
decision_margin: The decision_margin of the AprilTag
hamming: The hamming of the AprilTag
goodness: The goodness of the AprilTag
x_translation: The x_translation of the AprilTag
y_translation: The y_translation of the AprilTag
z_translation: The z_translation of the AprilTag
x_rotation: The x_rotation of the AprilTag
y_rotation: The y_rotation of the AprilTag
z_rotation: The z_rotation of the AprilTag</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 AprilTag(std::vector<int> &rect, std::vector<std::vector<int>> &corners, int id, int famliy, float centroid_x, float centroid_y, float rotation, float decision_margin, int hamming, float goodness, float x_translation, float y_translation, float z_translation, float x_rotation, float y_rotation, float

# 5.7.2. __getitem__

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] Returns the apriltag&#x27; s bounding box x coordinate
[1] Returns the apriltag&#x27; s bounding box y coordinate
[2] Returns the apriltag&#x27; s bounding box w coordinate
[3] Returns the apriltag&#x27; s bounding box h coordinate
[4] Returns the apriltag&#x27; s id
[5] Returns the apriltag&#x27; s family
[6] Not support
[7] Not support
[8] Not support
[9] Not support
[10] Returns the apriltag&#x27; s hamming
[11] Not support
[12] Not support
[13] Not support
[14] Not support
[15] Not support</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>[16] Not support
[17] Not support</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int &amp;amp;__getitem__(int index)</td></tr></table>

# 5.7.3. corners

<table><tr><td>1 | def corners(self) -&amp;gt; list[list[int]]</td></tr></table>

get coordinate of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the coordinate of the AprilTag.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<std::vector<int>> corners()

# 5.7.4. rect

<table><tr><td>1 | def rect(self) -&amp;gt; list[int]</td></tr></table>

get rectangle of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the rectangle of the AprilTag.
format is {x, y, w, h}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> rect()

# 5.7.5.x

1 def x(self) - > int

get x of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x()

# 5.7.6.y

1 def y(self) - > int

get y of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y()

# 5.7.7.w

get w of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return w of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int w()

# 5.7.8.h

1 def h(self) - > int

get h of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return h of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int h()

# 5.7.9. id

1 def id(self) - > int

get id of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return id of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int id()

# 5.7.10. family

1 def family(self) - > int

get family of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return family of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int family()

# 5.7.11.cx

1 def cx(self) - > int

get cx of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return cx of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int cx()

# 5.7.12.cxf

1 def cxf(self) - > float

get cxf of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return cxf of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float cxf

# 5.7.13. cy

1 def cy(self) - > int

get cy of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return cy of the AprilTag, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int cy()

# 5.7.14. cyf

1 def cyf(self) - > float

get cyf of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return cyf of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float cyf()

# 5.7.15. rotation

get rotation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return rotation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float rotation()

# 5.7.16. decision_margin

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/d79c63fa53671ba956de2d26659f92834fb07a362d2f041d9503c66ae8c23db4.jpg)

Get decision_margin of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the quality of the apriltag match (0.0 - 1.0) where 1.0 is the best.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

float decision_margin

# 5.7.17. hamming

get hamming of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the number of accepted bit errors for this tag. 
return 0, means 0 bit errors will be accepted. 
1 is TAG25H7, means up to 1 bit error may be accepted 
2 is TAG25H9, means up to 3 bit errors may be accepted</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>3 is TAG36H10, means up to 3 bit errors may be accepted
4 is TAG36H11, means up to 4 bit errors may be accepted
5 is ARTOOLKIT, means 0 bit errors will be accepted</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int hamming

# 5.7.18. goodness

get goodness of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return goodness of the AprilTag, type is float
Note: This value is always 0.0 for now.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float goodness

# 5.7.19. x_translation

1 def x_translation(self) - > float

get x_translation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x_translation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/5a470b01e39f79d0386b0d9eb8264470e1c8eaa8e029685ead027edd8022540e.jpg)

# 5.7.20. y_translation

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/28ab5cc43499e05c6140acaad712f35d83eb9ac8a0613dd715826ce8c00ef4a9.jpg)

get y_translation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y_translation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | float y_translation()

# 5.7.21.z_translation

1 | def z_translation(self) - > float

get z_translation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return z_translation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | float z_translation()</td></tr></table>

# 5.7.22.x_rotation

<table><tr><td>1 | def x_rotation(self) -&amp;gt; float</td></tr></table>

get x_rotation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x_rotation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float x_rotation()

# 5.7.23. y_rotation

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/8b8e67f21ecae3aefd63f0fbc8d1ce3591b70ea58c74c9a3dadd20b8ba873cc8.jpg)

get y_rotation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y_rotation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float y_rotation()

# 5.7.24. z_rotation

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/db03844d9b08e00ee66c13f8947955a7d9118f0ce44a884320319dfb6befb08e.jpg)

get z_rotation of AprilTag

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>return z_rotation of the AprilTag, type is float</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | float z_rotation()</td></tr></table>

# 5.8. DataMatrix

DataMatrix class

$\mathtt{C + + }$  definition code:

1 class DataMatrix

# 5.8.1. init

1 def init_(self, rect: list[int], corners: list[list[int]], payload: str, rotation: float, rows: int, columns: int, capacity: int, padding: int) - > None

DataMatrix constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>rect: Inlucodes the top-left corner and the width and height of the rectangle.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>format is {x, y, w, h}, type is std::vector
corners: Includes the four corners of the rectangle. format is {{x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}}, type is
std::vector&lt;std::vector&amp;gt; payload: The payload of the DataMatrix rotation: The rotation of the DataMatrix rows: The rows of the DataMatrix columns: The columns of the DataMatrix capacity: The capacity of the DataMatrix padding: The padding of the DataMatrix</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | DataMatrix<std::vector<int> &rect, std::vector<std::vector<int>> &corners, std::string &payload, float rotation, int rows, int columns, int capacity, int padding)

# 5.8.2. __getitem__

1 | def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>index: [0] get x of DataMatrix
[1] get y of DataMatrix
[2] get w of DataMatrix
[3] get h of DataMatrix
[4] Not support this index, try to use payload() method
[5] Not support this index, try to use rotation() method
[6] get rows of DataMatrix
[7] get columns of DataMatrix
[8] get capacity of DataMatrix
[9] get padding of DataMatrix</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/cf857da795812c7f845e20ce3d27277da7a92e02e880f360d6c6d68cb5aa9eb1.jpg)

# 5.8.3. corners

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/22b44191b66a93fcf9b74219e76285d911d9b653ad93d88dfe4eb7826585cbc4.jpg)

get coordinate of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the coordinate of the DataMatrix.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<std::vector<int>> corners()

# 5.8.4. rect

1 def rect(self) - > list[int]

get rectangle of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the rectangle of the DataMatrix.
format is {x, y, w, h}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<int> rect()

# 5.8.5. x

1 def x(self) - > int

get x of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x

# 5.8.6. y

get y of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y

# 5.8.7.w

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/13c5f65541ebd366122852e579f742463cda861d0ed42f94f11b30302f1509fd.jpg)

get w of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return w of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int w

# 5.8.8.h

get h of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return h of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int h

# 5.8.9.payload

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/40c6230a185061691f81028f99297804a2c93f8f79c7c64e548a3f754ba24387.jpg)

get payload of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return payload of the DataMatrix, type is std::string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defnati on code:

1 std::string payload()

# 5.8.10. rotation

get rotation of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return rotation of the DataMatrix, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defnati on code:

1 float rotation()

# 5.8.11. rows

<table><tr><td>1 | def rows(self) -&amp;gt; int</td></tr></table>

get rows of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return rows of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int rows()

# 5.8.12. columns

<table><tr><td>1 | def columns(self) -&amp;gt; int</td></tr></table>

get columns of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return columns of the DataMatrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int columns()

# 5.8.13. capacity

1 def capacity(self) - > int

get capacity of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns how many characters could fit in this data matrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int capacity()

# 5.8.14. padding

get padding of DataMatrix

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns how many unused characters are in this data matrix, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int padding()

# 5.9. BarCode

BarCode class

$\mathtt{C + + }$  definition code:

1 class BarCode

# 5.9.1. init

1 def init_(self, rect: list[int], corners: list[list[int]], payload: str, type: int, rotation: float, quality: int) - > None

BarCode constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>rect: Inlucdes the top-left corner and the width and height of the rectangle.
format is {x, y, w, h}, type is std::vector
corners: Includes the four corners of the rectangle. format is {{x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}}, type is
std::vector&lt;std::vector&amp;gt; 
payload: The payload of the BarCode
type: The type of the BarCode
rotation: The rotation of the BarCode
quality: The quality of the BarCode</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | BarCode(std::vector<int> &rect, std::vector<std::vector<int>> &corners, std::string &payload, int type, float rotation, int quality)

# 5.9.2. __getitem__

1 | def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: [0] get x of BarCode
[1] get y of BarCode
[2] get w of BarCode
[3] get h of BarCode
[4] Not support this index, try to use payload() method
[5] get type of BarCode
[6] Not support this index, try to use rotation() method
[7] get quality of BarCode</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int &__getitem__(int index)

# 5.9.3. corners

1 | def corners(self) - > list[list[int]]

get coordinate of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the coordinate of the BarCode.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<std::vector<int>> corners()

# 5.9.4. rect

1 | def rect(self) - > list[int]

get rectangle of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return the rectangle of the BarCode.
format is {x, y, w, h}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

# 5.9.5. x

get x of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x of the BarCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x()

# 5.9.6. y

get y of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y of the BarCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/bea4cb8f855a5ae89886997ccdcf138ce0c53487c7dbe7425db560a5e1fae277.jpg)

# 5.9.7.w

1 def w(self) - > int

get w of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return w of the BarCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  defination code:

1 int w

# 5.9.8.h

1 def h(self) - > int

get h of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return h of the BarCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/df894f28bb251466a3ef7fbaa450b1bde1e5171340885bce74d7eda76b791512.jpg)

# 5.9.9. payload

1 def payload(self) - > str

get payload of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return payload of the BarCode, type is std::string</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | std::string payload()</td></tr></table>

# 5.9.10. type

<table><tr><td>1 | def type(self) -&amp;gt; int</td></tr></table>

get type of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return type of the BarCode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int type()

# 5.9.11. rotation

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/8839d1ab16a2006d38feada0dcf1a5d71b0ee43f0311f37d4a6b559c8f4fc2ed.jpg)

get rotation of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return rotation of the BarCode, type is float. FIXME: always return 0.0</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float rotation()

# 5.9.12. quality

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/3b5d19e302518cac998e27d7b2bdeaa0f4efdea22a92a6dc76c986730aafed99.jpg)

get quality of BarCode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return quality of the BarCode, type is int</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int quality()

# 5.10. Statistics

Statistics class

$\mathtt{C + + }$  definition code:

class Statistics

# 5.10.1. init

1 def init_(self, format: Format, l_statistics: list[int], a_statistics: list[int], b_statistics: list[int]) - > None

Statistics constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>format: The statistics source image
format
l_statistics: The statistics of the L
channel.format is {mean, median, mode, std_dev, min, max, lq, uq}, type is</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>std::vector
a_statistics: The statistics of the A channel. format is {mean, median, mode, std_dev, min, max, lq, uq}, type is std::vector
b_statistics: The statistics of the B channel. format is {mean, median, mode, std_dev, min, max, lq, uq}, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

Statistics(image::Format format, std::vector<int>&l_statistics, std::vector<int>&a_statistics, std::vector<int>&b_statistics)

# 5.10.2. __getitem__

def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: array index</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int &__getitem__(int index)

# 5.10.3. format

1 def format(self) - > Format

get format of Statistics source image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return format of the Statistics source image, type is image::Format</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Format format()

# 5.10.4. I_mean

def l_mean(self) - > int

get L channel mean

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel mean, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_mean()

# 5.10.5. I_median

get L channel median

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel median, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_median()

# 5.10.6. I_mode

get L channel mode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel mode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_mode()

# 5.10.7. I_std_dev

1 def l_std_dev(self) - > int

get L channel std_dev

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel std_dev, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_std_dev()

# 5.10.8. I_min

1 def l_min(self) - > int

get L channel min

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel min, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int lmin

# 5.10.9. I_max

get L channel max

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel max, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int lmax

# 5.10.10. I_lq

<table><tr><td>1 | def l_lq(self) -&amp;gt; int</td></tr></table>

get L channel lq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel lq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_lq()

# 5.10.11. I_uq

get L channel uq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return L channel uq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_uq()

# 5.10.12. a_mean

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/36da1b0608f9473a922e5866014974f6b3c42b29392c6c9195d2ce0e3384688b.jpg)

get A channel mean

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel mean, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_mean()

# 5.10.13. a median

get A channel median

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel median, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_median()

# 5.10.14. a_mode

<table><tr><td>1 | def a_mode(self) -&amp;gt; int</td></tr></table>

get A channel mode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel mode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_mode()

# 5.10.15. a_std_dev

1 def a_std_dev(self) - > int

get A channel std_dev

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel std_dev, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_std_dev()

# 5.10.16. a_min

1 def a_min(self) - > int

get A channel min

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel min, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_min()

# 5.10.17. a_max

get A channel max

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel max, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_max()

# 5.10.18. a_lq

<table><tr><td>1 | def a_lq(self) -&amp;gt; int</td></tr></table>

get A channel lq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel lq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_lq()

# 5.10.19. a_uq

get A channel uq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return A channel uq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_uq()

# 5.10.20. b_mean

<table><tr><td>1 | def b_mean(self) -&amp;gt; int</td></tr></table>

get B channel mean

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel mean, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_mean()

# 5.10.21. b_median

get B channel median

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel median, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_median()

# 5.10.22. b_mode

<table><tr><td>1 | def b_mode(self) -&amp;gt; int</td></tr></table>

get B channel mode

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel mode, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_mode()

# 5.10.23.b_std_dev

1 def b_std_dev(self) - > int

get B channel std_dev

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel std_dev, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_std_dev()

# 5.10.24.b_min

1 def b_min(self) - > int

get B channel min

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel min, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_min()

# 5.10.25. b_max

get B channel max

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel max, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_max()

# 5.10.26. b_lq

<table><tr><td>1 | def b_lq(self) -&amp;gt; int</td></tr></table>

get B channel lq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel lq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_lq()

# 5.10.27. b_uq

get B channel uq

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return B channel uq, type is int</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_uq()

# 5.11. Displacement

Displacement class

$\mathtt{C + + }$  defination code:

1 class Displacement

# 5.11.1. init

1 | def __init__(self, x_translation: float, y_translation: float, rotation: float, scale: float, response: float) - > None

Displacement constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x_translation: The x_translation of the Displacement
y_translation: The y_translation of the Displacement
rotation: The rotation of the Displacement
scale: The scale of the Displacement
response: The response of the Displacement</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Displacement(float x_translation, float y_translation, float rotation, float scale, float response)

# 5.11.2. getitem

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/0b601fc61caad9ce423bcb7680ad1ef624955d114c18409b1bd304eff9231f85.jpg)

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>index: array index</td></tr><tr><td>return</td><td>int&amp;amp;</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int &__getitem__(int index)

# 5.11.3.x_translation

def x_translation(self) - > float

get x_translation of Displacement

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return x_translation of the Displacement, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

float x_translation

# 5.11.4. y_translation

1 def y_translation(self) - > float

get y_translation of Displacement

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return y_translation of the Displacement, type is float</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | float y_translation()</td></tr></table>

# 5.11.5. rotation

<table><tr><td>1 | def rotation(self) -&amp;gt; float</td></tr></table>

get rotation of Displacement

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return rotation of the Displacement, type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  defnatiOn code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/fd6d9fee3c4ac056c696c391387ebb029cee7c7a37cecd7ed12944a16e469e20.jpg)

# 5.11.6. scale

1 def scale(self) - > float

get scale of Displacement

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return scale of the Displacement, type is float</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | float scale()</td></tr></table>

# 5.11.7. response

<table><tr><td>1 | def response(self) -&amp;gt; float</td></tr></table>

get response of Displacement

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return response of the Displacement, 
type is float</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 float response()

# 5.12. Percentile

Percentile class

$\zeta + +$  definition code:

1 class Percentile

# 5.12.1. init

1 def init__self, l_value: int, a_value: int = 0, b_value: int = 0) - > None

Percentile constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>I_value: for grayscale image, it is grayscale percentile value (between 0 and 255).
for rgb888 image, it is I channel percentile value of lab (between 0 and 100).
a_value: for rgb888 image, it is a channel percentile value of lab format (between -128 and 127).</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>b_value: for rgb888 image, it is b
channel percentile value of lab
format(between -128 and 127).</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | Percentile(int l_value, int a_value = 
  0, int b_value = 0)</td></tr></table>

# 5.12.2. __getitem__

<table><tr><td>1 | def __getitem__(self, index: int) -&amp;gt; int</td></tr></table>

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int &__getitem__(int index)

# 5.12.3. value

def value(self) - > int

Return the grayscale percentile value (between 0 and 255).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns grayscale percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int value()

# 5.12.4. I_value

Return the I channel percentile value of lab format (between 0 and 100).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns I channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_value()

# 5.12.5. a_value

1 | def a_value(self) - > int

Return the a channel percentile value of lab format (between - 128 and 127).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns a channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int a_value()

# 5.12.6. b_value

1 | def b_value(self) - > int

Return the b channel percentile value of lab format (between - 128 and 127).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns b channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int b_value()

# 5.13. Threshold

Threshold class

$\mathtt{C + + }$  defination code:

1 class Threshold

# 5.13.1. init

1 def init_(self, l_value: int, a_value: int = 0, b_value: int = 0) - > None

Threshold constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>I_value: for grayscale image, it is grayscale threshold value (between 0 and 255).
for rgb888 image, it is I channel threshold value of lab (between 0 and 100).
a_value: for rgb888 image, it is a channel threshold value of lab format(between -128 and 127).
b_value: for rgb888 image, it is b channel threshold value of lab format(between -128 and 127).</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

Threshold(int l_value, int a_value = 0, int b_value = 0)

# 5.13.2. __getitem__

def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int &__getitem__(int index)

# 5.13.3. value

def value(self) - > int

Return the grayscale threshold value (between 0 and 255).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns grayscale threshold value</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int value()

# 5.13.4. I_value

1 def l_value(self) - > int

Return the I channel threshold value of lab format (between 0 and 100).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns I channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int l_value()

# 5.13.5. a_value

1 def a_value(self) - > int

Return the a channel threshold value of lab format (between - 128 and 127).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns a channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int a_value()

# 5.13.6. b_value

1 def b_value(self) - > int

Return the b channel threshold value of lab format (between - 128 and 127).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns b channel percentile value</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int b_value()

# 5.14. Histogram

Histogram class

$\zeta + +$  definition code:

1 class Histogram

# 5.14.1. init

1 | def init_(self, i_bin: list[float], a_bin: list[float], b_bin: list[float], format: Format = ...) - > None

Histogram constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>I_value: for grayscale image, it is grayscale threshold value list (the range of element values in the list is 0 and 255).
for rgb888 image, it is I channel threshold value list of lab (the range of element values in the list is 0 and 100).
a_value: for rgb888 image, it is a channel threshold value list of lab format (the range of element values in the list is -128 and 127).
b_value: for rgb888 image, it is b channel threshold value list of lab format (the range of element values in the list is -128 and 127).
format: format of the source image</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | Histogram(std::vector<float> l_bin, std::vector<float> a_bin, std::vector<float> b_bin, image::Format format = image::Format::FMT_RGB888)

# 5.14.2. __getitem__

1 | def __getitem__(self, index: int) - > int

Subscript operator

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | int &__getitem__(int index)

# 5.14.3. bins

1 | def bins(self) - > list[float]

Returns a list of floats for the grayscale histogram.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> bins()

# 5.14.4. I_bins

1 def l_bins(self) - > list[float]

Returns a list of floats for the RGB565 histogram LAB L channel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> l_bins()

# 5.14.5. a_bins

1 def a_bins(self) - > list[float]

Returns a list of floats for the RGB565 histogram LAB A channel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> a_bins()

# 5.14.6. b_bins

1 def b_bins(self) - > list[float]

Returns a list of floats for the RGB565 histogram LAB B channel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> b_bins()

# 5.14.7. get_percentile

1 def get_percentile(self, percentile: float) - > Percentile

Computes the CDF of the histogram channels and returns a image::Percentile object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>percentile: the values of the histogram at the passed in percentile (0.0 - 1.0) (float).
So, if you pass in 0.1 this method will tell you (going from left-to-right in the histogram)
what bin when summed into an accumulator caused the accumulator to cross 0.1. This is useful to determine min (with 0.1) and max (with 0.9) of a color distribution without outlier effects
ruining your results for adaptive color tracking.</td></tr><tr><td>return</td><td>image::Percentile object</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Percentile
get_percentile(float percentile)</td></tr></table>

# 5.14.8. get_threshold

<table><tr><td>1 | def get_threshold(self) -&amp;gt; Threshold</td></tr></table>

Uses Otsu's Method to compute the optimal threshold values that split the histogram into two

halves for each channel of the histogram and returns a image::Threshold object.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>image::Threshold object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Threshold get_threshold()

# 5.14.9. get_statistics

1 | def get_statistics(self) - > Statistics

Computes the mean, median, mode, standard deviation, min, max, lower quartile, and upper quartile of each color channel in the histogram and returns a image::Statistics object.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>image::Statistics object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Statistics get_statistics()

# 5.15. LBPPKeyPoint

LBPPKeyPoint class

$\mathtt{C + + }$  defination code:

1 class LBPPKeyPoint

# 5.15.1. init

1 def init_(self, data: list[int]) - > None

LBPPKeyPoint constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>data: The data of the LBPPKeyPoint</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | LBPPKeyPoint(std::valarray<int8_t>&data)

# 5.16. KeyPoint

KeyPoint class

$\mathtt{C + + }$  defination code:

1 class KeyPoint

# 5.16.1. init

1 | def __init__(self, x: int, y: int, score: int, octave: int, angle: int, matched: int, desc: list[int]) - > None

KeyPoint constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: The x of the KeyPoint
y: The y of the KeyPoint
score: The score of the KeyPoint
octave: The octave of the KeyPoint
angle: The angle of the KeyPoint
matched: The matched of the KeyPoint
desc: The desc of the KeyPoint</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | KeyPoint(uint16_t x, uint16_t y, uint16_t score, uint16_t octave, uint16_t angle, uint16_t matched, std::vector<uint8_t> &desc)

# 5.17. KPTMatch

KPTMatch class

$\mathtt{C + + }$  definition code:

1 class KPTMatch

# 5.17.1. init

1 | def __init__(self, cx: int, cy: int, x: int, y: int, w: int, h: int, score: int, theta: int, match: int) - > None

KPTMatch constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>cx: The cx of the KPTMatch
cy: The cy of the KPTMatch
x: The x of the KPTMatch
y: The y of the KPTMatch
w: The w of the KPTMatch
h: The h of the KPTMatch
score: The score of the KPTMatch
theta: The theta of the KPTMatch
match: The match of the KPTMatch</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | KPTMatch(int cx, int cy, int x, int y, int w, int h, int score, int theta, int match)

# 5.18. ORBKeyPoint

ORBKeyPoint class

$\mathtt{C + + }$  definition code:

1 class ORBKeyPoint

# 5.18.1. init

1 def init_(self, data: list[KeyPoint], threshold: int, normalized: bool) - > None

ORBKeyPoint constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>data: The data of the ORBKeyPoint
threshold: The threshold of the ORBKeyPoint
normalized: The normalized of the ORBKeyPoint</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>ORBKeyPoint(std::vector&lt;image::KeyPoint &amp;amp;data, int threshold, bool normalized)</td></tr></table>


</image>

# 5.18.2. get_data

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/cbdcd72b1aef3c271a402ccc32fa06d8fd67055b5bd502788a4420079319b9f8.jpg)

get data of ORBKeyPoint

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return data of the ORBKeyPoint, type is std::vector</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<image::KeyPoint> get_data()

# 5.19. HaarCascade

HaarCascade class

$\mathtt{C + + }$  definition code:

1 | class HaarCascade

# 5.19.1. init

1 | def __init__(self) - > None

HaarCascade constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>data: The data of the HaarCascade
threshold: The threshold of the
HaarCascade
normalized: The normalized of the
HaarCascade</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

HaarCascade()

# 5.20. LineGroup

LineGroup class

$\mathtt{C + + }$  defination code:

class LineGroup

# 5.20.1. init

def __init__(self, id: int, type: LineType, lines: list[Line]) - > None

LineGroup constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>id: The id of line
type: The line list type, @see
image::LineType
lines: The line list</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | LineGroup(int id, image::LineType type, std::vector<image::Line> lines)

# 5.20.2. id

1 | def id(self) - > int

Get the line id of group, first id is 0.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>return id</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | int id()

# 5.20.3. type

1 | def type(self) - > LineType

Get the line type of group

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns line type. @see LineType</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::LineType type()

# 5.20.4. lines

1 | def lines(self) - > list[Line]

Get a list of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>returns a list composed of Line objects</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<image::Line> lines()

# 5.21. Color

Color class

$\zeta + +$  defination code:

1 class Color

# 5.21.1. init

1 def init_(self, ch1: int, ch2: int = 0, ch3: int = 0, alpha: float = 0, format: Format = ...) - > None

Color constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>alpha: alpha channel, value range: 0 ~ 1</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

Color(uint8_t ch1, uint8_t ch2 = 0, uint8_t ch3 = 0, float alpha = 0, image::Format format = image::FMT_GRAYSCALE)

# 5.21.2. r

Color red channel

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 uint8_t r

# 5.21.3. g

Color green channel

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

<table><tr><td>1 | uint8_t g</td></tr></table>

# 5.21.4. b

Color blue channel

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/406d360bab43c53666b3a2e217a773065f3cbef4018ed3f551dbc1ff2a21e606.jpg)

# 5.21.5. alpha

Color alpha channel, value from 0.0 to 1.0, float value

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

# 5.21.6. gray

Color gray channel

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

uint8_t gray

# 5.21.7. format

Color format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format format

# 5.21.8.hex

Get color's hex value

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

uint32_t hex()

# 5.21.9. from_rgb

def from_rgb(r: int, g: int, b: int) - > Color

Create Color object from RGB channels

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | static image::Color from_rgb(uint8_tr, uint8_t g, uint8_t b)

# 5.21.10. from_bgr

1 | def from_bgr(b: int, g: int, r: int) - > Color

Create Color object from BGR channels

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | static image::Color from_bgr(uint8_tb, uint8_t g, uint8_t r)

# 5.21.11. from_gray

1 | def from_gray(gray: int) - > Color

Create Color object from gray channel

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | static image::Color from_gray(uint8_t gray)

# 5.21.12. from_rgba

1 | def from_rgba(r: int, g: int, b: int, alpha: float) - > Color

Create Color object from RGBA channels

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>alpha: alpha channel, float value, value range: 0 ~ 1</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | static image::Color from_rgba(uint8_tr, uint8_t g, uint8_t b, float alpha)

# 5.21.13. from_bgra

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/243b8147e3bbeb5b6907b466462bc3563a99583158cabeb84d278e7cfb3cbfed.jpg)

Create Color object from BGRA channels

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>alpha: alpha channel, float value, value range: 0 ~ 1</td></tr><tr><td>static</td><td>True</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | static image::Color from_bgra(uint8_t b, uint8_t g, uint8_t r, float alpha)

# 5.21.14. from_hex

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/5201f71ae93f858b81a396427d11402751c15a58fc6ccc18e1f9d499b765e993.jpg)

Create Color object from hex value

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>hex: hex value, e.g. 0x0000FF00, lower address if first channel format: color format, @see image::Format</td></tr><tr><td>static</td><td>True</td></tr></table>

$\zeta + +$  definition code:

1 | static image::Color from_hex(uint32_t hex, image::Format &format)

# 5.21.15. to_format

1 | def to_format(self, format: Format) - > None

Convert Color format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>format: format want to convert to, @see image::Format, only support RGB888, BGR888, RGBA888, BGRA888, GRAYSCALE.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | void to_format(const image::Format &format)

# 5.21.16. to_format2

1 | def to_format2(self, format: Format) - > Color

Convert color format and return a new Color object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>format: format want to convert to, @see image::Format, only support RGB888, BGR888, RGBA888, BGRA888, GRAYSCALE.</td></tr><tr><td>return</td><td>new Color object, you need to delete it manually in C++.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Color *to_format2(const image::Format &format)

# 5.22. Image

Image class

$\mathtt{C + + }$  defination code:

class Image

# 5.22.1. init

1 def init self, width: int, height: int, format: Format = ...)- > None

Image constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>width: image width, should &amp;gt; 0
height: image height, should &amp;gt; 0
format: image format @see
image::Format</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | Image(int width, int height, image::Format format = image::Format::FMT_RGB888)

# 5.22.2. format

1 | def format(self) - > Format

Get image's format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>see</td><td>image.Format</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Format format()

# 5.22.3. size

1 | def size(self) - > Size

Get image's size, [width, height]

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size size()

# 5.22.4. data_size

def data_size(self) - > int

Get image's data size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int data_size()

# 5.22.5. width

def width(self) - > int

Get image's width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int width()

# 5.22.6.height

Get image's height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int height()

# 5.22.7. str

1 def str (self) - > str

To string method

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string str

# 5.22.8. to_str

To string method

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string to_str

# 5.22.9. get_pixel

def get_pixel(self, x: int, y: int,rgbtuple: bool = False) - > list[int]

Get pixel of image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: pixel&#x27;s coordinate x. x must less than image&#x27;s width
y: pixel&#x27;s coordinate y. y must less than image&#x27;s height
rgbtuple: switch return value method.
rgbtuple decides whether to split the return or not. default is false.</td></tr><tr><td>return</td><td>pixel value,
According to image format and rgbtuple, return different value:
format is FMT_RGB888, rgbtuple is true, return [R, G, B]; rgbtuple is false, return [RGB]
foramt is FMT_BGR888, rgbtuple is true, return [B, G, R]; rgbtuple is false, return [BGR]
format is FMT_GRAYSCALE, return [GRAY];</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> get_pixel(int x, int y, bool rgbtuple = false)

# 5.22.10. set_pixel

1 | def set_pixel(self, x: int, y: int, pixel: list[int]) - > maix.err.Err

Set pixel of image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: pixel&#x27;s coordinate x. x must less than image&#x27;s width
y: pixel&#x27;s coordinate y. y must less than image&#x27;s height
pixel: pixel value, according to image format and size of pixel, has different operation:
format is FMT_RGB888, pixel size must be 1 or 3, if size is 1, will split pixel[0] to [R, G, B]; if size is 3, will use pixel directly format is FMT_BGR888, pixel size must be 1 or 3, if size is 1, will split pixel[0] to [B, G, R]; if size is 3, will use pixel directly format is FMT_GRAYSCALE, pixel size must be 1, will use pixel directly</td></tr><tr><td>return</td><td>error code, Err::ERR_NONE is ok, other is error</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err set_pixel(int x, int y, std::vector<int> pixel)

# 5.22.11. to_tensor

1 | def to_tensor(self, chw: bool = False, copy: bool = True) - > maix.tensor.Tensor

Convert Image object to tensor::Tensor object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>chw: if true, the shape of tensor is [C, H, W], else [H, W, C]
copy: if true, will alloc memory for tensor data, else will use the memory of Image object</td></tr><tr><td>return</td><td>tensor::Tensor object pointer, an allocated tensor object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | tensor::Tensor *to_tensor(bool chw = false, bool copy = true)

# 5.22.12. to_bytes

Get image's data and convert to array bytes

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>copy: if true, will alloc memory and copy data to new buffer, 
else will use the memory of Image object, delete bytes object will not affect Image object, 
but delete Image object will make bytes object invalid, it may cause program crash !!! 
So use this param carefully.</td></tr><tr><td>return</td><td>image&#x27;s data bytes, need be delete by caller in C++.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | Bytes *to_bytes(bool copy = true)</td></tr></table>

# 5.22.13. to_format

<table><tr><td>1 | def to_format(self, format: Format) -&amp;gt; Image</td></tr></table>

Convert image to specific format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>format: format want to convert to, @see image::Format, only support RGB888,</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>BGR888, RGBA888, BGRA8888, GRAYSCALE, JPEG.</td></tr><tr><td>return</td><td>new image object. Need be delete by caller in C++.</td></tr><tr><td>throw</td><td>err.Exception, if two images&#x27; format not support, or already the format, will raise exception</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *to_format(const image::Format &format)

# 5.22.14. to_jpeg

<table><tr><td>1 | def to_jpeg(self, quality: int = 95) -&amp;gt; Image</td></tr></table>

Convert image to jpeg

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>quality: the quality of jpg, default is 95.
For MaixCAM supported range is (50, 100], if &amp;lt;= 50 will be fixed to 51.</td></tr><tr><td>return</td><td>new image object. Need be delete by caller in C++.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>throw</td><td>err.Exception, if two images&#x27; format not support, or already the format, will raise exception</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *to_jpeg(int quality = 95)

# 5.22.15. draw_image

<table><tr><td>1 | def draw_image(self, x: int, y: int, img: Image) -&amp;gt; Image</td></tr></table>

Draw image on this image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: left top corner of image point&#x27;s 
coordinate x
y: left top corner of image point&#x27;s 
coordinate y
img: image object to draw, the caller&#x27;s 
channel must &amp;lt;= the args&#x27; channel, 
e.g. caller is RGB888, args is RGBA888, 
will throw exception, but caller is 
RGBA888, args is RGB888 or RGBA888 
is ok</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *draw_image(int x, int y, image::Image &img)

# 5.22.16. draw_rect

1 def draw_rect(self, x: int, y: int, w: int, h: int, color: Color, thickness: int = 1) - > Image

Fill rectangle color to image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: left top corner of rectangle point&#x27;s 
coordinate x
y: left top corner of rectangle point&#x27;s 
coordinate y
w: rectangle width
h: rectangle height
color: rectangle color
thickness: rectangle thickness(line 
width), by default(value is 1), -1 means 
fill rectangle</td></tr><tr><td>return</td><td>this image object self</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *draw_rect(int x, int y, int w, int h, const image::Color &color, int thickness = 1)

# 5.22.17. draw_line

1 def draw_line(self, x1: int, y1: int, x2: int, y2: int, color: Color, thickness: int = 1) - > Image

Draw line on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x1: start point&#x27;s coordinate x
y1: start point&#x27;s coordinate y
x2: end point&#x27;s coordinate x
y2: end point&#x27;s coordinate y
color: line color @see image::Color
thickness: line thickness(line width), by default(value is 1)</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Image *draw_line(int x1, int y1, int x2, int y2, const image::Color &color, int thickness = 1)

# 5.22.18. draw_circle

1 def draw_circle(self, x: int, y: int, radius: int, color: Color, thickness: int = 1) - > Image

Draw circle on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: circle center point&#x27;s coordinate x
y: circle center point&#x27;s coordinate y
radius: circle radius
color: circle color @see image::Color
thickness: circle thickness(line width),
default -1 means fill circle</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *draw_circle(int x, int y, int radius, const image::Color &color, int thickness = 1)

# 5.22.19. draw_ellipse

1 def draw_ellipse(self, x: int, y: int, a: int, b: int, angle: float, start_angle: float, end_angle: float, color: Color, thickness: int = 1) - > Image

Draw ellipse on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: ellipse center point&#x27;s coordinate x
y: ellipse center point&#x27;s coordinate y
a: ellipse major axis length
b: ellipse minor axis length
angle: ellipse rotation angle
start_angle: ellipse start angle
end_angle: ellipse end angle
color: ellipse color @see image::Color
thickness: ellipse thickness(line width),
by default(value is 1), -1 means fill
ellipse</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathbb{C} + +$  definition code:

1 image::Image *draw_ellipse(int x, int y, int a, int b, float angle, float start_angle, float end_angle, const image::Color &amp;color, int thickness = 1)

# 5.22.20. draw_string

1 | def draw_string(self, x: int, y: int, textstring: str, color: Color = ..., scale: float = 1, thickness: int = - 1, wrap: bool = True, wrap_space: int = 4, font: str = '') - > Image

Draw text on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: text left top point&#x27;s coordinate x
y: text left top point&#x27;s coordinate y
string: text content
color: text color @see image::Color,
default is white
scale: font scale, by default(value is 1)
thickness: text thickness(line width), if
negative, the glyph is filled, by
default(value is -1)
wrap: if true, will auto wrap text to next
line if text width &amp;gt; image width, by
default(value is true)</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Image *draw_string(int x, int y, const std::string &textstring, const image::Color &color = image::COLOR_WHITE, float scale = 1,

# 5.22.21. draw_cross

1 def draw_cross(self, x: int, y: int, color: Color, size: int = 5, thickness: int = 1) - > Image

Draw cross on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: cross center point&#x27;s coordinate x
y: cross center point&#x27;s coordinate y
color: cross color @see image::Color
size: how long the lines of the cross
extend, by default(value is 5). So the line
length is 2 * size + thickness
thickness: cross thickness(line width), by
default(value is 1)</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Image *draw_cross(int x, int y, const image::Color &color, int size = 5, int thickness = 1)

# 5.22.22. draw_arrow

1 def draw_arrow(self, x0: int, y0: int, x1: int, y1: int, color: Color, thickness: int = 1) - > Image

Draw arrow on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x0: start coordinate of the arrow x0
y0: start coordinate of the arrow y0
x1: end coordinate of the arrow x1
y1: end coordinate of the arrow y1
color: cross color @see image::Color
thickness: cross thickness(line width), by default(value is 1)</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *draw_arrow(int x0, int y0, int x1, int y1, const image::Color &color, int thickness = 1)

# 5.22.23. draw_edges

1 def draw_edges(self, corners: list[list[int]], color: Color, size: int = 0, thickness: int = 1, fill: bool = False) - > Image

Draw edges on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>corners: edges, [[x0, y0], [x1, y1], [x2, y2],
[x3, y3]]
color: edges color @see image::Color
size: the circle of radius size. TODO:
support in the feature
thickness: edges thickness(line width),
by default(value is 1)
fill: if true, will fill edges, by
default(value is false)</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *draw_edges(std::vector<std::vector<int> corners, const image::Color &color, int size = 0, int thickness = 1, bool fill = false)

# 5.22.24. draw keypoints

1 def draw keypoints(self, keypoints: list[int], color: Color, size: int = 4, thickness: int = - 1, line_thickness: int = 0) - > Image

Draw keypoints on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>keypoints: keypoints, [x1, y1, x2, y2...] or 
[x, y, rotation_andle_in_degrees, x2, y2, 
rotation_andle_in_degrees2](TODO:
rotation_andle_in_degrees support in the 
feature)
color: keypoints color @see image::Color
size: size of keypoints(radius)
thickness: keypoints thickness(line 
width), by default(value is -1 means fill 
circle)
line_thickness: line thickness, default 0 
means not draw lines, &amp;gt; 0 will draw lines 
connect points.</td></tr><tr><td>return</td><td>this image object self</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *draw_keypoints(const std::vector<int> & keypoints, const image::Color & color, int size = 4, int thickness = - 1, int line_thickness = 0)

# 5.22.25. resize

1 def resize(self, width: int, height: int, object_fit: Fit = ..., method: ResizeMethod = ...) - > Image

Resize image, will create a new resized image object

<table><tr><td>item</td><td>description</td><td></td></tr><tr><td>type</td><td>func</td><td></td></tr><tr><td>param</td><td>width: new width,
if value is -1, will use height to calculate aspect ratio
height: new height, if value is -1, will use width to calculate aspect ratio
object_fit: fill, contain, cover, by default is fill
method: resize method, by default is NEAREST</td><td></td></tr><tr><td>return</td><td>Always return a new resized image object even size not change, So in C++ you should take care of the return value to avoid memory leak.
And it&#x27;s better to judge whether the</td><td></td></tr></table>

<table><tr><td>item</td><td>description</td><td></td></tr><tr><td></td><td>size has changed before calling this function to make the program more efficient.
e.g.
if img-&amp;gt;width() != width</td><td></td></tr><tr><td>static</td><td>False</td><td></td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *resize(int width, int height, image::Fit object_fit = image::Fit::FIT_FILL, image::ResizeMethod method = image::ResizeMethod::NEAREST)

# 5.22.26. affine

1 def affine(self, src_points: list[int], dst_points: list[int], width: int = - 1, height: int = - 1, method: ResizeMethod = ...) - > Image

Affine transform image, will create a new transformed image object, need 3 points.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>src_points: three source points, [x1, y1, x2, y2, x3, y3]
dst_points: three destination points, [x1, y1, x2, y2, x3, y3]
width: new width, if value is -1, will use height to calculate aspect ratio
height: new height, if value is -1, will use width to calculate aspect ratio
method: resize method, by default is bilinear</td></tr><tr><td>return</td><td>new transformed image object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Image *affine(std::vector<int> src_points, std::vector<int> dst_points, int width = - 1, int height = - 1, image::ResizeMethod method = image::ResizeMethod::BILINEAR)

# 5.22.27. perspective

1 def perspective(self, src_points: list[int], dst_points: list[int], width: int = - 1, height: int = - 1, method: ResizeMethod = ...) - > Image

Perspective transform image, will create a new transformed image object, need 4 points.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>src_points: three source points, [x1, y1, x2, y2, x3, y3, x4, y4]
dst_points: three destination points, [x1, y1, x2, y2, x3, y3, x4, y4]
width: new width, if value is -1, will use height to calculate aspect ratio
height: new height, if value is -1, will use width to calculate aspect ratio
method: resize method, by default is bilinear</td></tr><tr><td>return</td><td>new transformed image object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image* perspective(std::vector<int> src_points, std::vector<int> dst_points, int width = - 1, int height = - 1, image::ResizeMethod method = image::ResizeMethod::BILINEAR)

# 5.22.28. copy

1 def copy(self) - > Image

Copy image, will create a new copied image object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>new copied image object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Image *copy()

# 5.22.29. crop

1 def crop(self, x: int, y: int, w: int, h: int) - > Image

Crop image, will create a new cropped image object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: left top corner of crop rectangle
point&#x27;s coordinate x
y: left top corner of crop rectangle
point&#x27;s coordinate y
w: crop rectangle width
h: crop rectangle height</td></tr><tr><td>return</td><td>new cropped image object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *crop(int x, int y, int w, int h)

# 5.22.30. rotate

1 | def rotate(self, angle: float, width: int = - 1, height: int = - 1, method: ResizeMethod = ...) - > Image

Rotate image, will create a new rotated image object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>angle: anti-clock wise rotate angle, if
angle is 90 or 270, and width or height is
-1, will swap width and height, or will
throw exception
width: new width, if value is -1, will use
height to calculate aspect ratio
height: new height, if value is -1, will use
width to calculate aspect ratio
method: resize method, by default is
bilinear</td></tr><tr><td>return</td><td>new rotated image object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *rotate(float angle, int width = - 1, int height = - 1, image::ResizeMethod method =

# 5.22.31. flip

1 | def flip(self, dir: FlipDir) - > Image

Vertical flip image, and return a new image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>dir: flip dir, see image.FlipDir, e.g.
image.FlipDir.X is vertical flip.</td></tr><tr><td>return</td><td>new flipped image.</td></tr><tr><td>throw</td><td>When arg error, will throw out err.Err
exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *flip(const image::FlipDir dir)

# 5.22.32. mean_pool

1 | def mean_pool(self, x_div: int, y_div: int, copy: bool = False) - > Image

Finds the mean of x_div * y_div squares in the image and returns the modified image composed of the mean of each square.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x_div: The width of the squares.
y_div: The height of the squares.
copy: Select whether to return a new image or modify the original image.
default is false.
If true, returns a new image composed of the mean of each square; If false, returns the modified image composed of the mean of each square.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *mean_pool(int x_div, int y_div, bool copy = false)

# 5.22.33. midpoint_pool

def midpoint_pool(self, x_div: int, y_div: int, bias: float = 0.5, copy: bool = False) - > Image

Finds the midpoint of x_div * y_div squares in the image and returns the modified image composed of the mean of each square.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x_div: The width of the squares.
y_div: The height of the squares.
bias: The bias of the midpoint. default is 0.5.
midpoint value is equal to (max * bias + min * (1 - bias))
copy: Select whether to return a new image or modify the original image.
default is false.
If true, returns a new image composed of the midpoint of each square; If false, returns the modified image composed of the midpoint of each square.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Image *midpoint_pool(int x_div, int y_div, double bias = 0.5, bool copy = false)</td></tr></table>

# 5.22.34. compress

1 def compress(self, quality: int = 95) - > Image

JPEG compresses the image in place, the same as to_jpeg function, it's recommend to use to_jpeg instead.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>quality: The quality of the compressed image. default is 95.</td></tr><tr><td>return</td><td>Returns the compressed JPEG image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  defination code:

image::Image *compress(int quality = 95)

# 5.22.35. clear

<table><tr><td>1 | def clear(self, mask: Image = None) -&amp;gt; Image</td></tr></table>

Sets all pixels in the image to zero.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>Only pixels set in the mask are modified.
default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *clear(image::Image *mask = nullptr)

# 5.22.36. mask_rectangle

1 | def mask_rectangle(self, x: int = - 1, y: int = - 1, w: int = - 1, h: int = - 1) - > Image

Zeros a rectangular part of the image. If no arguments are supplied this method zeros the center of the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: The x coordinate of the top left corner of the rectangle.
y: The y coordinate of the top left corner of the rectangle.
w: The width of the rectangle.
h: The height of the rectangle.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Image *mask_rectangle(int x = - 1, int y = - 1, int w = - 1, int h = - 1)

# 5.22.37. mask_circle

1 | def mask_circle(self, x: int = - 1, y: int = - 1, radius: int = - 1) - > Image

Zeros a circular part of the image. If no arguments are supplied this method zeros the center of the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: The x coordinate of the center of the circle.
y: The y coordinate of the center of the circle.
radius: The radius of the circle.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *mask_circle(int x = - 1, int y = - 1, int radius = - 1)

# 5.22.38. mask_ellipse

1 def mask_ellipse(self, x: int = - 1, y: int = - 1, radius_x: int = - 1, radius_y: int = - 1, rotation_angle_in_degrees: float = 0) - > Image

Zeros a ellipse part of the image. If no arguments are supplied this method zeros the center of the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: The x coordinate of the center of the ellipse.
y: The y coordinate of the center of the ellipse.
radius_x: The radius of the ellipse in the x direction.
radius_y: The radius of the ellipse in the y direction.
rotation_angle_in_degrees: The rotation angle of the ellipse in degrees.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *mask_ellipse(int x = - 1, int y = - 1, int radius_x = - 1, int radius_y = - 1, float rotation_angle_in_degrees = 0)

# 5.22.39. binary

1 def binary(self, thresholds: list[list[int]] = [], invert: bool = False, zero: bool = False, mask: Image = None, to_bitmap: bool = False, copy: bool = False) - > Image

Sets all pixels in the image to black or white depending on if the pixel is inside of a threshold in the threshold list thresholds or not.

https://wiki.sipeed.com/maixpy/api/maix/image.html

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>For GRAYSCALE format, Lmin and Lmax range is [0, 255]. For RGB888 format, Lmin and Lmax range is [0, 100].</td></tr><tr><td>param</td><td>thresholds: You can define multiple thresholds.
For GRAYSCALE format, you can use {{Lmin, Lmax}, ...} to define one or more thresholds.
For RGB888 format, you can use {{Lmin, Lmax, Amin, Amax, Bmin, Bmax}, ...} to define one or more thresholds.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>Where the upper case L,A,B represent the L,A,B channels of the LAB image format, and min, max represent the minimum and maximum values of the corresponding channels.
invert: If true, the thresholds will be inverted before the operation. default is false.
zero: If zero is true, the image will be set the pixels within the threshold to 0, other pixels remain unchanged. If zero is false, the image will be set to black or white. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.
to_bitmap: If true, the image will be converted to a bitmap image before thresholding. default is false. TODO: support in the feature
copy: Select whether to return a new image or modify the original image. default is false.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *binary(std::vector<std::vector<int>> thresholds = std::vector<std::vector<int>>(), bool invert = false, bool zero = false, image::Image *mask = nullptr, bool to_bitmap = false, bool copy = false)

# 5.22.40. invert

Inverts the image in place.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the image after the operation is completed</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *invert()

# 5.22.41. b_and

1 def b_and(self, other: Image, mask: Image = None) - > Image

Performs a bitwise and operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Image *b_and(image::Image *other, image::Image *mask = nullptr)</td></tr></table>

# 5.22.42. b_nand

1 def b_nand(self, other: Image, mask: Image = None) - > Image

Performs a bitwise nand operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Image *b_nand(image::Image *other, image::Image *mask = nullptr)

# 5.22.43. b_or

1 def b_or(self, other: Image, mask: Image = None) - > Image

Performs a bitwise or operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO:
support path:
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Image *b_or(image::Image *other, image::Image *mask = nullptr)</td></tr></table>

# 5.22.44. b_nor

1 def b_nor(self, other: Image, mask: Image = None) - > Image

Performs a bitwise nor operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *b_nor(image::Image *other, image::Image *mask = nullptr)

# 5.22.45. b_xor

1 def b_xor(self, other: Image, mask: Image = None) - > Image

Performs a bitwise xor operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td>1</td><td>image::Image *b_xor(image::Image *other, image::Image *mask = nullptr)</td></tr></table>

# 5.22.46. b_xnor

1 def b_xnor(self, other: Image, mask: Image = None) - > Image

Performs a bitwise xor operation between the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *b_xnor(image::Image *other, image::Image *mask = nullptr)

# 5.22.47. awb

1 def awb(self, max: bool = False) - > Image

Performs an auto white balance operation on the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>max: if True uses the white-patch algorithm instead. default is false.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  defination code:

image::Image \*awb(bool max  $=$  false)

# 5.22.48. ccm

1 def ccm(self, matrix: list[float]) - > Image

Multiples the passed (3x3) or (4x3) floating- point color- correction- matrix with the image.\nnote: Grayscale format is not support.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>matrix: The color correction matrix to use. 3x3 or 4x3 matrix.
Weights may either be positive or negative, and the sum of each column in</td></tr></table>

<table><tr><td>item</td><td>description</td><td></td><td></td></tr><tr><td></td><td>the 3x3 matrix should generally be 1.
example:
{
  1, 0, 0,
  0, 1, 0,
  0, 0, 1,
}
Where the last row of the 4x3 matrix is an offset per color channel. If you add an offset you may wish to make the weights sum to less than 1 to account for the offset.
example:
{
  1, 0, 0,
  0, 1, 0,
  0, 0, 1,
  0, 0, 0,
}</td><td></td><td>Returns the image after the operation is completed.</td></tr><tr><td>return</td><td rowspan="2">False</td><td></td><td></td></tr><tr><td>static</td><td></td><td></td></tr></table>

$\zeta + +$  definition code:

1 | image::Image *ccm(std::vector<float>&matrix)

# 5.22.49. gamma

1 def gamma(self, gamma: float = 1.0, contrast: float = 1.0, brightness: float = 0.0) - > Image

Quickly changes the image gamma, contrast, and brightness. Create a array whose size is usually 255,\nand use the parameters gamma, contrast, and brightness to calculate the value of the array, and then map the\nimage pixel value through the value of the array.\nThe calculation method for array is: array[array_idx] = (powf((array_idx / 255.0), (1 / gamma)) * contrast + brightness) * scale,\n powf is a function used to calculate floating point power.\n array is the array used for mapping.\n array_idx is the index of the array, the maximum value is determined according to the image format, usually 255.\n scale is a constant, the value is determined by the image format, usually 255. \nMapping method:\nAssume that a pixel value in the image is 128, then map the pixel value to the value of array[128]\nUsers can adjust the value of the array through the gamma, contrast, and brightness parameters.

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>gamma: The contrast gamma greater than 1.0 makes the image darker in a non-linear manner while less than 1.0 makes the image brighter. default is 1.0. contrast: The contrast value greater than 1.0 makes the image brighter in a linear</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>manner while less than 1.0 makes the image darker. default is 1.0.
brightness: The brightness value greater than 0.0 makes the image brighter in a constant manner while less than 0.0
makes the image darker. default is 0.0.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *gamma(double gamma = 1.0, double contrast = 1.0, double brightness = 0.0)

# 5.22.50. gamma_corr

def gamma_corr(self, gamma: float, contrast: float = 1.0, brightness: float = 0.0) - > Image

Alias for Image.gamma.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>gamma: The contrast gamma greater than 1.0 makes the image darker in a non-linear manner while less than 1.0 makes the image brighter. default is 1.0.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>contrast: The contrast value greater than 1.0 makes the image brighter in a linear manner while less than 1.0 makes the image darker. default is 1.0.
brightness: The brightness value greater than 0.0 makes the image brighter in a constant manner while less than 0.0 makes the image darker. default is 0.0.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *gamma_corr(double gamma, double contrast = 1.0, double brightness = 0.0)

# 5.22.51. negate

<table><tr><td>1 | def negate(self) -&amp;gt; Image</td></tr></table>

Flips (numerically inverts) all pixels values in an image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

image::Image *negate()

# 5.22.52. replace

1 def replace(self, other: Image = None,  hmirror: bool = False, vflip: bool = False, transpose: bool = False, mask: Image = None) - > Image

Replaces all pixels in the image with the corresponding pixels in the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
hmirror: If true, the image will be horizontally mirrored before the operation. default is false.
vflip: If true, the image will be vertically flipped before the operation. default is false.
transpose: If true, the image can be used to rotate 90 degrees or 270 degrees.
hmirror = false, vflip = false, transpose = false, the image will not be rotated.
hmirror = false, vflip = true, transpose =</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>true, the image will be rotated 90 degrees.
hmirror = true, vflip = true, transpose = false, the image will be rotated 180 degrees.
hmirror = true, vflip = false, transpose = true, the image will be rotated 270 degrees.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *replace(image::Image *other = nullptr, bool hmirror = false, bool vflip = false, bool transpose = false, image::Image *mask = nullptr)

# 5.22.53. set

def set(self, other: Image, hmirror: bool = False, vflip: bool = False,

Alias for Image::replace.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
hmirror: If true, the image will be horizontally mirrored before the operation. default is false.
vflip: If true, the image will be vertically flipped before the operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on.
Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *set(image::Image *other, bool hmirror = false, bool vflip = false, bool transpose =

# 5.22.54. add

1 | def add(self, other: Image, mask: Image = None) - > Image

Adds the other image to the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *add(image::Image *other, image::Image *mask = nullptr)

# 5.22.55. sub

1 def sub(self, other: Image, reverse: bool = False, mask: Image = None) - > Image

Subtracts the other image from the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
reverse: If true, the image will be reversed before the operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 image::Image *sub(image::Image *other, bool reverse = false,

# 5.22.56. mul

1 def mul(self, other: Image, invert: bool = False, mask: Image = None) - > Image

Multipliesthe image by the other image.\nNote: This method is meant for image blending and cannot multiply the pixels in the image by a scalar like 2.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
invert: If true, the image will be change the multiplication operation from ab to 1/((1/a)(1/b)).
In particular, this lightens the image instead of darkening it (e.g. multiply versus burn operations). default is false. mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Image *mul(image::Image *other, bool invert = false, image::Image *mask = nullptr)

# 5.22.57. div

1 def div(self, other: Image, invert: bool = False, mod: bool = False, mask: Image = None) - > Image

Divides the image by the other image.\nThis method is meant for image blending and cannot divide the pixels in the image by a scalar like 2.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on. TODO: support path?
invert: If true, the image will be change the division direction from a/b to b/a. default is false.
mod: If true, the image will be change</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>the division operation to the modulus operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *div(image::Image *other, bool invert = false, bool mod = false, image::Image *mask = nullptr)

# 5.22.58. min

def min(self, other: Image, mask: Image = None) - > Image

Calculate the minimum of each pixel in the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *min(image::Image *other, image::Image *mask = nullptr)

# 5.22.59. max

def max(self, other: Image, mask: Image = None) - > Image

Caculate the maximum of each pixel in the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *max(image::Image *other, image::Image *mask = nullptr)

# 5.22.60. difference

def difference(self, other: Image, mask: Image = None) - > Image

Calculate the absolute value of the difference between each pixel in the image and the other image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *difference(image::Image *other, image::Image *mask = nullptr)

# 5.22.61. blend

def blend(self, other: Image, alpha: int = 128, mask: Image = None) - > Image

Blends the image with the other image.\nres = alpha * this_img / 256 + (256 - alpha) * other_img / 256

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>other: The other image should be an image and should be the same size as the image being operated on.
alpha: The alpha value of the blend, the value range is [0, 256], default is 128.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on.
Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *blend(image::Image *other, int alpha = 128, image::Image *mask = nullptr)

# 5.22.62. histeq

1 def histeq(self, adaptive: bool = False, clip_limit: int = - 1, mask: Image = None) - > Image

Runs the histogram equalization algorithm on the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>adaptive: If true, an adaptive histogram equalization method will be run on the image instead which as generally better results than non-adaptive histogram equalization but a longer run time. default is false.
clip_limit: Provides a way to limit the contrast of the adaptive histogram equalization. Use a small value for this, like 10, to produce good histogram equalized contrast limited images. default is -1.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Image *histeq(bool adaptive = false, int clip_limit = - 1, image::Image *mask = nullptr)

# 5.22.63. mean

1 def mean(self, size: int, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Standard mean blurring filter using a box filter.\nThe parameters offset and invert are valid when threshold is True.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel&#x27;s brightness in relation to the brightness of the kernel of pixels around them. 
default is false. 
offset: The larger the offset value, the lower brightness pixels on the original image will be set to white. default is 0. 
invert: If true, the image will be inverted before the operation. default is false. 
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>size as the image being operated on.
Only pixels set in the mask are modified.
default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *mean(int size, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.64. median

1 def median(self, size: int, percentile: float = 0.5, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Runs the median filter on the image. The median filter is the best filter for smoothing surfaces while preserving edges but it is very slow.

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
percentile: This parameter controls the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>percentile of the value used in the 
kernel. You can set this to 0 for a min 
filter, 0.25 for a lower quartile filter, 0.75 
for an upper quartile filter, and 1.0 for a 
max filter. default is 0.5.
threshold: If true, which will enable 
adaptive thresholding of the image 
which sets pixels to white or black based 
on a pixel&#x27;s brightness in relation to the 
brightness of the kernel of pixels around 
them.
default is false.
offset: The larger the offset value, the 
lower brightness pixels on the original 
image will be set to white. default is 0.
invert: If true, the image will be inverted 
before the operation. default is false.
mask: Mask is another image to use as a 
pixel level mask for the operation. The 
mask should be an image with just black 
or white pixels and should be the same 
size as the image being operated on. 
Only pixels set in the mask are modified. 
default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is 
completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | image::Image *median(int size, double percentile = 0.5, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.65. mode

1 def mode(self, size: int, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Runs the mode filter on the image by replacing each pixel with the mode of their neighbors.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel&#x27; s brightness in relation to the brightness of the kernel of pixels around them. 
default is false. 
offset: The larger the offset value, the lower brightness pixels on the original image will be set to white. default is 0. 
invert: If true, the image will be inverted before the operation. default is false.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *mode(int size, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.66. midpoint

1 def midpoint(self, size: int, bias: float = 0.5, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Runs the midpoint filter on the image. This filter finds the midpoint (max * bias + min * (1 - bias)) of each pixel neighborhood in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
bias: The bias of the midpoint. default is 0.5. 
threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel&#x27;s brightness in relation to the brightness of the kernel of pixels around them. 
default is false. 
offset: The larger the offset value, the lower brightness pixels on the original image will be set to white. default is 0. 
invert: If true, the image will be inverted before the operation. default is false. 
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. 
Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | image::Image *midpoint(int size, double bias = 0.5, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.67. morph

1 def morph(self, size: int, kernel: list[int], mul: float = - 1, add: float = 0.0, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Convolves the image by a filter kernel. This allows you to do general purpose convolutions on an image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
kernel: The kernel used for convolution. 
The kernel should be a list of lists of numbers. The kernel should be the same size as the actual kernel size. 
mul: This parameter is used to multiply the convolved pixel results. default is auto. 
add: This parameter is the value to be added to each convolution pixel result. default is 0.0. 
threshold: If true, which will enable</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>adaptive thresholding of the image
which sets pixels to white or black based
on a pixel&#x27;s brightness in relation to the
brightness of the kernel of pixels around
them.
default is false.
offset: The larger the offset value, the
lower brightness pixels on the original
image will be set to white. default is 0.
invert: If true, the image will be inverted
before the operation. default is false.
mask: Mask is another image to use as a
pixel level mask for the operation. The
mask should be an image with just black
or white pixels and should be the same
size as the image being operated on.
Only pixels set in the mask are modified.
default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is
completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | image::Image *morph(int size, std::vector<int> kernel, float mul = - 1, float add = 0.0, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.68. gaussian

1 def gaussian(self, size: int, unsharp: bool = False, mul: float = - 1, add: float = 0.0, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Convolves the image by a smoothing gaussian kernel.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
unsharp: If true, this method will perform an unsharp mask operation instead of gaussian filtering operation, this improves the clarity of image edges. default is false.
mul: This parameter is used to multiply the convolved pixel results. default is auto.
add: This parameter is the value to be added to each convolution pixel result. default is 0.0.
threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel&#x27;s brightness in relation to the brightness of the kernel of pixels around them.
default is false.
offset: The larger the offset value, the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>lower brightness pixels on the original image will be set to white. default is 0.
invert: If true, the image will be inverted before the operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *gaussian(int size, bool unsharp = false, float mul = - 1, float add = 0.0, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.69. laplacian

1 def laplacian(self, size: int, sharpen: bool = False, mul: float = - 1, add: float = 0.0, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Convolves the image by a edge detecting laplacian kernel.

type func param size: Kernel size. The actual kernel size is  $((\text{size} *2) + 1) * ((\text{size} *2) + 1)$ . Use 1(3x3 kernel), 2(5x5 kernel). sharpen: If True, this method will sharpen the image instead of an unthresholded edge detection image. Then increase the kernel size to improve image clarity. default is false. mul: This parameter is used to multiply the convolved pixel results. default is auto. add: This parameter is the value to be added to each convolution pixel result. default is 0.0. threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel's brightness in relation to the brightness of the kernel of pixels around them. default is false. offset: The larger the offset value, the lower brightness pixels on the original image will be set to white. default is 0. invert: If true, the image will be inverted before the operation. default is false. mask: Mask is another image to use as a

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *laplacian(int size, bool sharpen = false, float mul = - 1, float add = 0.0, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.70. bilateral

1 def bilateral(self, size: int, color_sigma: float = 0.1, space_sigma: float = 1, threshold: bool = False, offset: int = 0, invert: bool = False, mask: Image = None) - > Image

Convolves the image by a bilateral filter.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel).
color_sigma: Controls how closely colors are matched using the bilateral filter. default is 0.1.
space_sigma: Controls how closely pixels space-wise are blurred with each other. default is 1.
threshold: If true, which will enable adaptive thresholding of the image which sets pixels to white or black based on a pixel&#x27; s brightness in relation to the brightness of the kernel of pixels around them.
default is false.
offset: The larger the offset value, the lower brightness pixels on the original image will be set to white. default is 0.
invert: If true, the image will be inverted before the operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *bilateral(int size, double color_sigma = 0.1, double space_sigma = 1, bool threshold = false, int offset = 0, bool invert = false, image::Image *mask = nullptr)

# 5.22.71. linpolar

1 def linpolar(self, reverse: bool = False) - > Image

Re- project' s and image from cartesian coordinates to linear polar coordinates.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>reverse: If true, the image will be reverse polar transformed. default is false.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *linpolar(bool reverse = false)

# 5.22.72. logpolar

1 | def logpolar(self, reverse: bool = False) - > Image

Re- project' s and image from cartesian coordinates to log polar coordinates.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>reverse: If true, the image will be reverse polar transformed. default is false.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *logpolar(bool reverse = false)

# 5.22.73. lens_corr

1 def lens_corr(self, strength: float = 1.8, zoom: float = 1.0, x_corr: float = 0.0, y_corr: float = 0.0) - > Image

Performs a lens correction operation on the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>strength: The strength of the lens
correction. default is 1.8.
zoom: The zoom of the lens correction.
default is 1.0.
x_corr: The x correction of the lens
correction. default is 0.0.
y_corr: The y correction of the lens
correction. default is 0.0.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Image *lens_corr(double strength = 1.8, double zoom = 1.0, double x_corr = 0.0, double y_corr = 0.0)

# 5.22.74. rotation_corr

1 def rotation_corr(self, x_rotation: float = 0.0, y_rotation: float = 0.0, z_rotation: float = 0.0, x_translation: float = 0.0, y_translation: float = 0.0, zoom: float = 1.0, fov: float = 60.0, corners: list[float] = []) - > Image

Performs a rotation correction operation on the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x_rotation: The x rotation of the rotation correction. default is 0.0.
y_rotation: The y rotation of the rotation correction. default is 0.0.
z_rotation: The z rotation of the rotation correction. default is 0.0.
x_translation: The x translation of the rotation correction. default is 0.0.
y_translation: The y translation of the rotation correction. default is 0.0.
zoom: The zoom of the rotation correction. default is 1.0.
fov: The fov of the rotation correction. default is 60.0.
corners: The corners of the rotation correction. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *rotation_corr(double x_rotation = 0.0, double y_rotation = 0.0, double z_rotation = 0.0, double x_translation = 0.0, double y_translation = 0.0, double zoom =

maix.image - MaixPy

1.0, double fov = 60.0, std::vector<float> corners = std::vector<float>()

# 5.22.75. get_histogram

1 | def get_histogram(self, thresholds: list[list[int]] = [], invert: bool = False, roi: list[int] = [], bins: int = - 1, l_bins: int = 100, a_bins: int = 256, b_bins: int = 256, difference: Image = None) - > Histogram

Computes the normalized histogram on all color channels and returns a image::Histogram object.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>For GRAYSCALE format, Lmin and Lmax range is [0, 255]. For RGB888 format, Lmin and Lmax range is [0, 100].</td></tr><tr><td>param</td><td>thresholds: You can define multiple thresholds.
For GRAYSCALE format, you can use {{Lmin, Lmax}, ...} to define one or more thresholds.
For RGB888 format, you can use {{Lmin, Lmax, Amin, Amax, Bmin, Bmax}, ...} to define one or more thresholds.
Where the upper case L,A,B represent the L,A,B channels of the LAB image format, and min, max represent the minimum and maximum values of the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>corresponding channels.
invert: If true, the thresholds will be inverted before the operation. default is false.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.
bins: The number of bins to use for the histogram.
In GRAYSCALE format, setting range is [2, 256], default is 100.
In RGB888 format, setting range is [2, 100], default is 100.
I_bins: The number of bins to use for the I channel of the histogram. Only valid in RGB888 format.
If an invalid value is set, bins will be used instead. The setting range is [2, 100], default is 100.
a_bins: The number of bins to use for the a channel of the histogram.
Only valid in RGB888 format. The setting range is [2, 256], default is 256.
b_bins: The number of bins to use for the b channel of the histogram.
Only valid in RGB888 format. The setting range is [2, 256], default is 256.
difference: difference may be set to an image object to cause this method to</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>operate on the difference image between the current image and the difference image object. default is None.</td></tr><tr><td>return</td><td>Returns image::Histogram object</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Histogram get_histogram(std::vector<std::vector>i thresholds  $=$  std::vector<std::vector<int>>(), bool invert  $=$  false, std::vector<int> roi  $=$  std::vector<int>(), int bins  $=$  - 1, int l_bins  $=$  100, int a_bins  $=$  256, int b_bins  $=$  256, image::Image \*difference  $=$  nullptr)

# 5.22.76. get_statistics

1 def get_statistics(self, thresholds: list[list[int]] = [], invert: bool = False, roi: list[int] = [], bins: int = - 1, l_bins: int = - 1, a_bins: int = - 1, b_bins: int = - 1, difference: Image = None) - > Statistics

Gets the statistics of the image. TODO: support in the feature

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>For GRAYSCALE format, Lmin and Lmax range is [0, 255]. For RGB888 format, Lmin and Lmax range is [0, 100].</td></tr><tr><td>param</td><td>thresholds: You can define multiple thresholds.
For GRAYSCALE format, you can use {{Lmin, Lmax}, ...} to define one or more thresholds.
For RGB888 format, you can use {{Lmin, Lmax, Amin, Amax, Bmin, Bmax}, ...} to define one or more thresholds.
Where the upper case L,A,B represent the L,A,B channels of the LAB image format, and min, max represent the minimum and maximum values of the corresponding channels.
invert: If true, the image will be inverted before the operation. default is false.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
bins: The number of bins to use for the statistics. default is -1.
I_bins: The number of bins to use for the I channel of the statistics. default is -1.
a_bins: The number of bins to use for the a channel of the statistics. default is</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>-1.
b_bins: The number of bins to use for the b channel of the statistics. default is -1.
difference: The difference image to use for the statistics. default is None.</td></tr><tr><td>return</td><td>Returns the statistics of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Statistics get_statistics(std::vector<std::vector< thresholds = std::vector<std::vector<int>>(), bool invert = false, std::vector<int> roi = std::vector<int>(), int bins = - 1, int l_bins = - 1, int a_bins = - 1, int b_bins = - 1, image::Image *difference = nullptr)

# 5.22.77. get_regression

1 def get_regression(self, thresholds: list[list[int]] = [], invert: bool = False, roi: list[int] = [], x_stride: int = 2, y_stride: int = 1, area_threshold: int = 10, pixels_threshold: int = 10, robust: bool = False) - > list[Line]

Gets the regression of the image.

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>For GRAYSCALE format, Lmin and Lmax range is [0, 255]. For RGB888 format, Lmin and Lmax range is [0, 100].</td></tr><tr><td>param</td><td>thresholds: You can define multiple thresholds.
For GRAYSCALE format, you can use {{Lmin, Lmax}, ...} to define one or more thresholds.
For RGB888 format, you can use {{Lmin, Lmax, Amin, Amax, Bmin, Bmax}, ...} to define one or more thresholds.
Where the upper case L,A,B represent the L,A,B channels of the LAB image format, and min, max represent the minimum and maximum values of the corresponding channels.
invert: If true, the image will be inverted before the operation. default is false.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.
x_stride: The x stride to use for the regression. default is 2.
y_stride: The y stride to use for the regression. default is 1.
area_threshold: The area threshold to use for the regression. default is 10.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>pixels_threshold: The pixels threshold to use for the regression. default is 10.
robust: If true, the regression will be robust. default is false.</td></tr><tr><td>return</td><td>Returns the regression of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<image::Line> get_regression(std::vector<std::vector<thresholds = std::vector<std::vector<int>>(), bool invert = false, std::vector<int> roi = std::vector<int>(), int x_stride = 2, int y_stride = 1, int area_threshold = 10, int pixels_threshold = 10, bool robust = false)

# 5.22.78. save

1 | def save(self, path: str, quality: int = 95) - > maix.err.Err

Save image to file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>path: file path
quality: image quality, by default(value is</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>95), support jpeg and png format</td></tr><tr><td>return</td><td>error code, err::ERR_NONE is ok, other is error</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | err::Err save(const char *path, int quality = 95)

# 5.22.79. flood_fill

1 def flood_fill(self, x: int, y: int, seed_threshold: float = 0.05, floating_threshold: float = 0.05, color: Color = ..., invert: bool = False, clear_background: bool = False, mask: Image = None) - > Image

Flood fills a region of the image starting from location x, y.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: The x coordinate of the seed point.
y: The y coordinate of the seed point.
seed_threshold: The seed_threshold
value controls how different any pixel in the fill area may be from the original starting pixel. default is 0.05.
floating_threshold: The</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>floating_threshold value controls how different any pixel in the fill area may be from any neighbor pixels. default is 0.05. color: The color to fill the region with. default is white.
invert: If true, the image will be inverted before the operation. default is false.
clear_background: If true, the background will be cleared before the operation. default is false.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on.
Only pixels set in the mask are modified. default is None. FIXME: the mask image works abnormally</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | image::Image *flood_fill(int x, int y, float seed_threshold = 0.05, float floating_threshold = 0.05, image::Color color = image::COLOR_WHITE, bool invert = false, bool clear_background = false, image::Image *mask = nullptr)

# 5.22.80.erode

1 | def erode(self, size: int, threshold: int = - 1, mask: Image = None) - > Image

Erodes the image in place.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: The number of pixels in the kernel that are not 0. If it is less than or equal to the threshold, set the center pixel to black. default is (kernel_size - 1). mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Image *erode(int size, int threshold = - 1, image::Image *mask =

# 5.22.81. dilate

1 def dilate(self, size: int, threshold: int = 0, mask: Image = None) - > Image

Dilates the image in place.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: The number of pixels in the kernel that are not 0. If it is greater than or equal to the threshold, set the center pixel to white. default is 0.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/d89ad3e6490e1ff2564a515f57fb0570cab707429b8c334f9e0680d9134ce0d1.jpg)

# 5.22.82. open

1 def open(self, size: int, threshold: int = 0, mask: Image = None) - > Image

Performs erosion and dilation on an image in order.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: As the threshold for erosion and dilation, the actual threshold for erosion is (kernel_size - 1 - threshold), the actual threshold for dilation is threshold. default is 0.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Image *open(int size, int threshold = 0, image::Image *mask = nullptr)

# 5.22.83. close

1 def close(self, size: int, threshold: int = 0, mask: Image = None) - > Image

Performs dilation and erosion on an image in order.

<table><tr><td>Item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: As the threshold for erosion and dilation, the actual threshold for erosion is (kernel_size - 1 - threshold), the actual threshold for dialation is threshold. default is 0.
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>Only pixels set in the mask are modified.
default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *close(int size, int threshold = 0, image::Image *mask = nullptr)

# 5.22.84. top_hat

1 def top_hat(self, size: int, threshold: int = 0, mask: Image = None) - > Image

Returns the image difference of the image and Image.open()' ed image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: As the threshold for open method. default is 0. 
mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *top_hat(int size, int threshold = 0, image::Image *mask = nullptr)

# 5.22.85. black_hat

1 def black_hat(self, size: int, threshold: int = 0, mask: Image = None) - > Image

Returns the image difference of the image and Image.close()' ed image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>size: Kernel size. The actual kernel size is ((size * 2) + 1) * ((size * 2) + 1). Use 1(3x3 kernel), 2(5x5 kernel). 
threshold: As the threshold for close method. default is 0.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>mask: Mask is another image to use as a pixel level mask for the operation. The mask should be an image with just black or white pixels and should be the same size as the image being operated on. Only pixels set in the mask are modified. default is None.</td></tr><tr><td>return</td><td>Returns the image after the operation is completed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image *black_hat(int size, int threshold = 0, image::Image *mask = nullptr)

# 5.22.86. find_blobs

1 def find_blobs(self, thresholds: list[list[int]] = [], invert: bool = False, roi: list[int] = [], x stride: int = 2, y stride: int = 1, area threshold: int = 10, pixels threshold: int = 10, merge: bool = False, margin: int = 0, xHist bins max: int = 0, yHist bins max: int = 0) - > list[Blob]

Finds all blobs in the image and returns a list of image.Blob class which describe each Blob.\nPlease see the image.Blob object more more information.

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>type</td><td>func</td></tr><tr><td>note</td><td>For GRAYSCALE format, Lmin and Lmax range is [0, 255]. For RGB888 format, Lmin and Lmax range is [0, 100].</td></tr><tr><td>param</td><td>thresholds: You can define multiple thresholds.
For GRAYSCALE format, you can use {{Lmin, Lmax}, ...} to define one or more thresholds.
For RGB888 format, you can use {{Lmin, Lmax, Amin, Amax, Bmin, Bmax}, ...} to define one or more thresholds.
Where the upper case L,A,B represent the L,A,B channels of the LAB image format, and min, max represent the minimum and maximum values of the corresponding channels.
invert: if true, will invert thresholds before find blobs, default is false
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
x_stride: x stride is the number of x pixels to skip when doing the hough transform. default is 2
y_stride: y stride is the number of y pixels to skip when doing the hough transform. default is 1</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>area_threshold: area threshold, if the blob area is smaller than area_threshold, the blob is not returned, default is 10 pixels_threshold: pixels threshold, if the blob pixels is smaller than area_threshold, the blob is not returned, default is 10.
when x_stride and y_stride is equal to 1, pixels_threshold is equivalent to area_threshold
merge: if True merges all not filtered out blobs whos bounding rectangles intersect each other. default is false
margin: margin can be used to increase or decrease the size of the bounding rectangles for blobs during the intersection test.
For example, with a margin of 1 blobs whos bounding rectangles are 1 pixel away from each other will be merged. default is 0
x_hist_bins_max: if set to non-zero populates a histogram buffer in each blob object with an x_histogram projection of all columns in the object. This value then sets the number of bins for that projection.
y_hist_bins_max: if set to non-zero populates a histogram buffer in each blob object with an y_histogram projection of all rows in the object. This</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>value then sets the number of bins for that projection.</td></tr><tr><td>return</td><td>Return the blob when found blobs, format is (blob1, blob2, ...), you can use blob class methods to do more operations.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 std::vector<image::Blob> find_blobs(std::vector<std::vector<int> thresholds = std::vector<std::vector<int>>(), bool invert = false, std::vector<int> roi = std::vector<int>(), int x_stride = 2, int y_stride = 1, int area_threshold = 10, int pixels_threshold = 10, bool merge = false, int margin = 0, int xHist_bins_max = 0, int yHist_bins_max = 0)

# 5.22.87. find_lines

1 def find_lines(self, roi: list[int] = [], x_stride: int = 2, y_stride: int = 1, threshold: float = 1000, theta_margin: float = 25, rho_margin: float = 25) - > list[Line]

Find lines in image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.
x治疗方法: x stride is the number of x pixels to skip when doing the hough transform. default is 2
y治疗方法: y stride is the number of y pixels to skip when doing the hough transform. default is 1
threshold: threshold threshold controls what lines are detected from the hough transform. Only lines with a magnitude greater than or equal to threshold are returned.
The right value of threshold for your application is image dependent. default is 1000.
theta_margin: theta_margin controls the merging of detected lines. default is 25.
rho_margin: rho_margin controls the merging of detected lines. default is 25.</td></tr><tr><td>return</td><td>Return the line when found lines, format is (line1, line2, ...,), you can use line class methods to do more operations</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<image::Line> find_lines(std::vector<int> roi = std::vector<int>(), int x_stride = 2, int y_stride = 1, double threshold = 1000, double theta_margin = 25, double rho_margin = 25)

# 5.22.88. find_line_segments

1 | def find_line_segments(self, roi: list[int] = [], merge_distance: int = 0, max_theta_difference: int = 15) - > list[Line]

Finds all line segments in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. merge_distance: The maximum distance between two lines to merge them. default is 0. max_theta_difference: The maximum difference between two lines to merge them. default is 15.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>Return the line when found lines, format is (line1, line2, ...), you can use line class methods to do more operations</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<image::Line> find_line_segments(std::vector<int> roi = std::vector<int>(), int merge_distance = 0, int max_theta_difference = 15)

# 5.22.89. search_line_path

1 | def search_line_path(self, threshold: int = 30, merge_degree: int = 10, min_len_of_new_path: int = 10) - > list[LineGroup]

Search the path of line

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>threshold: Threshold for finding a line, the larger the value the more accurate the line is found
merge_degree: Minimum angle difference required when merging multiple lines
min_len_of_new_path: The minimum</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>length of a new path, if the crossing length exceeds this value, it is considered a new path.</td></tr><tr><td>return</td><td>Return the line when found lines, format is (groupline1, groupline2, ...), you can use LineGroup class methods to do more operations</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<image::LineGroup> search_line_path(int threshold = 30, int merge_degree = 10, int min_len_of_new_path = 10)

# 5.22.90. find_circles

1 | def find_circles(self, roi: list[int] = [], x_stride: int = 2, y_stride: int = 1, threshold: int = 2000, x_margin: int = 10, y_margin: int = 10, r_margin: int = 10, r_min: int = 2, r_max: int = - 1, r_step: int = 2) - > list[Circle]

Find circles in image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.
x旅游局: x旅游局 is the number of x pixels to skip when doing the hough transform. default is 2
y旅游局: y旅游局 is the number of y pixels to skip when doing the hough transform. default is 1
threshold: threshold controls what circles are detected from the hough transform. Only circles with a magnitude greater than or equal to threshold are returned.
The right value of threshold for your application is image dependent.
x旅游局: x旅游局 controls the merging of detected circles. Circles which are x旅游局, y旅游局, and r_margin pixels apart are merged. default is 10
y旅游局: y旅游局 controls the merging of detected circles. Circles which are x旅游局, y旅游局, and r_margin pixels apart are merged. default is 10
r_margin: r_margin controls the merging of detected circles. Circles which are x旅游局, y旅游局, and r_margin pixels apart are merged. default is 10
r_min: r_min controls the minimum circle</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>radius detected. Increase this to speed up the algorithm. default is 2
r_max: r_max controls the maximum circle radius detected. Decrease this to speed up the algorithm. default is min(roi.w / 2, roi.h / 2)
r_step: r_step controls how to step the radius detection by. default is 2.</td></tr><tr><td>return</td><td>Return the circle when found circles, format is (circle1, circle2, ...), you can use circle class methods to do more operations</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<image::Circle> find_circles(std::vector<int> roi = std::vector<int>(), int x_stride = 2, int y_stride = 1, int threshold = 2000, int x_margin = 10, int y_margin = 10, int r_margin = 10, int r_min = 2, int r_max = - 1, int r_step = 2)

# 5.22.91. find_rects

1 | def find_rects(self, roi: list[int] = [], threshold: int = 10000) - > list[Rect]

Finds all rects in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. threshold: The threshold to use for the rects. default is 10000.</td></tr><tr><td>return</td><td>Returns the rects of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::vector<int> roi = std::vector<int>(), int threshold = 10000)

# 5.22.92. find_qrcodes

1 | def find_qrcodes(self, roi: list[int] = [], decoder_type: QRCodeDecoderType = ...) - > list[QRCode]

Finds all qrcodes in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
decoder_type: Select the QR code decoding method. Choosing 
QRCODE_DECODER_TYPE_QUIRC allows for retrieving QR code version, ECC level, mask, data type, and other details, though it may decode slower at lower resolutions. Opting for 
QRCODE_DECODER_TYPE_ZBAR enables faster decoding at lower resolutions but may slow down at higher resolutions, providing only the QR code content and position information. default is 
QRCODE_DECODER_TYPE_ZBAR.</td></tr><tr><td>return</td><td>Returns the qrcodes of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | std::vector<image::QRCode> find_qrcodes(std::vector<int> roi = std::vector<int>(); image::QRCodeDecoderType decoder_type = image::QRCodeDecoderType::QRCODE_DECODE

# 5.22.93. find_apriltags

1 def find_apriltags(self, roi: list[int] = [], families: ApriltagFamilies = ..., fx: float = - 1, fy: float = - 1, cx: int = - 1, cy: int = - 1) - > list[AprilTag]

Finds all apriltags in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. families: The families to use for the apriltags. default is TAG36H11.
fx: The camera X focal length in pixels, default is -1.
fy: The camera Y focal length in pixels, default is -1.
cx: The camera X center in pixels, default is image.width / 2.
cy: The camera Y center in pixels, default is image.height / 2.</td></tr><tr><td>return</td><td>Returns the apriltags of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<image::AprilTag> find_apriltags(std::vector<int> roi = std::vector<int>(   ),

maix.image - MaixPy

image::ApriltagFamilies families = image::ApriltagFamilies::TAG36H11, float fx = - 1, float fy = - 1, int cx = - 1, int cy = - 1)

# 5.22.94. find_datamatrices

1 def find_datamatrices(self, roi: list[int] = [], effort: int = 200) - > list[DataMatrix]

Finds all datamatrices in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. effort: Controls how much time to spend trying to find data matrix matches. default is 200.</td></tr><tr><td>return</td><td>Returns the datamatrices of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<image::DataMatrix> find_datamatrices(std::vector<int> roi = std::vector<int>(), int effort = 200)

# 5.22.95. find barcodes

1 | def find_barcodes(self, roi: list[int] = []) - > list[BarCode]

Finds all barcodes in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.</td></tr><tr><td>return</td><td>Returns the barcodes of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<image::BarCode> find_barcodes(std::vector<int> roi = std::vector<int>()

# 5.22.96. find_displacement

1 | def find_displacement(self, template_image: Image, roi: list[int] = [], template_roi: list[int] = [], logpolar: bool = False) - > Displacement

Finds the displacement between the image and the template. TODO: support in the feature\nnote: this

method must be used on power- of- 2 image sizes

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>template_image: The template image.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
template_roi: The region-of-interest rectangle (x, y, w, h) to work in. If not specified, it is equal to the image rectangle.
logpolar: If true, it will instead find rotation and scale changes between the two images. default is false.</td></tr><tr><td>return</td><td>Returns the displacement of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | image::Displacement find_displacement(image::Image &template_image, std::vector<int> roi = std::vector<int>(), std::vector<int> template_roi = std::vector<int>(), bool logpolar = false)

# 5.22.97. find_template

1 def find_template(self, template_image: Image, threshold: float, roi: list[int] = [], step: int = 2, search: TemplateMatch = ...) - > list[int]

Finds the template in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>template_image: The template image.
threshold: Threshold is floating point number (0.0-1.0) where a higher threshold prevents false positives while lowering the detection rate while a lower threshold does the opposite.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
Only valid in SEARCH_EX mode.
step: The step size to use for the template. default is 2. Only valid in SEARCH_EX mode
search: The search method to use for the template. default is SEARCH_EX.</td></tr><tr><td>return</td><td>Returns a bounding box tuple (x, y, w, h) for the matching location otherwise None.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<int> find_template(image::Image &template_image, float threshold, std::vector<int> roi = std::vector<int>(), int step = 2, image::TemplateMatch search = image::TemplateMatch::SEARCH_EX)

# 5.22.98.find features

1 | def find_features(self, cascade: int, threshold: float = 0.5, scale: float = 1.5, roi: list[int] = []) - > list[int]

Finds the features in the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>cascade: The cascade to use for the features, default is CASCADE_FRONTALFACE_ALT.
threshold: The threshold to use for the features, default is 0.5.
scale: The scale to use for the features. default is 1.5.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.</td></tr><tr><td>return</td><td>Returns the features of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<int> find_features(int cascade, float threshold = 0.5, float scale = 1.5, std::vector<int> roi = std::vector<int>()

# 5.22.99. find_lbp

1 | def find_lbp(self, roi: list[int] = []) - > LBPPKeyPoint

Finds the lbp in the image. TODO: support in the feature.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image.</td></tr><tr><td>return</td><td>Returns the lbp of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::LBPKKeyPoint find_lbp(std::vector<int> roi = std::vector<int>())

# 5.22.100. find keypoints

1 def find keypoints(self, roi: list[int] = [], threshold: int = 20, normalized: bool = False, scale_factor: float = 1.5, max keypoints: int = 100, corner_detector: CornerDetector = ...) - > ORBKeyPoint

Finds the keypoints in the image. TODO: support in the feature.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. threshold: The threshold to use for the keypoints. default is 20. normalized: If true, the image will be normalized before the operation. default is false. scale_factor: The scale factor to use for the keypoints. default is 1.5. max_keypoints: The maximum number of keypoints to use for the keypoints. default is 100. corner_detector: The corner detector to use for the keypoints. default is CORNER_AGAST.</td></tr><tr><td>return</td><td>Returns the keypoints of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | image::ORBKeyPoint find keypoints(std::vector<int> roi = std::vector<int>(), int threshold = 20, bool normalized = false, float scale_factor = 1.5, int max_keypoints = 100, image::CornerDetector corner_detector = image::CornerDetector::CORNER_AGAST)

# 5.22.101. find_edges

1 | def find_edges(self, edge_type: EdgeDetector, roi: list[int] = [], threshold: list[int] = [100, 200]) - > Image

Finds the edges in the image.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>edge_type: The edge type to use for the edges. default is EDGE_CANNY.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
threshold: The threshold to use for the edges. default is 20.</td></tr><tr><td>return</td><td>Returns the edges of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | image::Image* find_edges(image::EdgeDetector edge_type, std::vector<int> roi = std::vector<int>(), std::vector<int> threshold = std::vector<int>{{100, 200}}))

![](https://cdn-mineru.openxlab.org.cn/extract/5155c5bd-6bbe-4a3b-a044-e1e88ef4e34d/3cb5f0b0bb539260bb5c8d299eda4d7f4d5acd0b69d89d34108c4f9f1818b693.jpg)

Finds the hog in the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi. default is None, means whole image. size: The size to use for the hog. default is 8.</td></tr><tr><td>return</td><td>Returns the hog of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image* find_hog(std::vector<int> roi = std::vector<int>(), int size = 8)

# 5.22.103. match_lbp_descriptor

1 def match_lbp_descriptor(self, desc1: LBPKeyPoint, desc2: LBPKeyPoint) - > int

Matches the lbp descriptor of the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>desc1: The descriptor to use for the match.
desc2: The descriptor to use for the match.</td></tr><tr><td>return</td><td>Returns the match of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int match_lbp_descriptor(image::LBPPKeyPoint &desc1, image::LBPPKeyPoint &desc2)

# 5.22.104. match orb descriptor

1 def match_orb_descriptor(self, desc1: ORBKeyPoint, desc2: ORBKeyPoint, threshold: int = 95, filter_outliers: bool = False) - > KPTMatch

Matches the orb descriptor of the image. TODO: support in the feature

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>desc1: The descriptor to use for the match.
desc2: The descriptor to use for the</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>match.
threshold: The threshold to use for the match.default is 95.
filter_outliers: If true, the image will be filter_outliers before the operation. default is false.</td></tr><tr><td>return</td><td>Returns the match of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::KPTMatch matchorb_descriptor(image::ORBKeyPoint &desc1, image::ORBKeyPoint &desc2, int threshold  $= 95$  ,bool filter_outliers  $=$  false)

# 5.22.105. resize_map_pos

1 def resize_map_pos(self, w_out: int, h_out: int, fit: Fit, x: int, y: int, w: int = - 1, h: int = - 1) - > list[int]

map point position or rectangle position from this image size to another image size(resize)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>int: h_out target image height
fit: resize method, see maix.image.Fit</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>x: original point x, or rectagle left-top
point&#x27;s x
y: original point y, or rectagle left-top
point&#x27;s y
w: original rectagle width, can be -1 if not use this arg, default -1.
h: original rectagle height, can be -1 if not use this arg, default -1.</td></tr><tr><td>return</td><td>list type, [x, y] if map point, [x, y, w, h] if resize rectangle.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<int> resize_map_pos(int w_out, int h_out, image::Fit fit, int x, int y, int w = - 1, int h = - 1)

# 5.23. QRCodeDetector

QRCodeDetector class

$\mathtt{C + + }$  defination code:

1 class QRCodeDetector

# 5.23.1. init

1 def init_(self) - > None

QRCodeDetector constructor.\nUse npu to accelerate the speed of QR code scanning, note that this object will occupy npu resources

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | QRCodeDetector()

# 5.23.2. detect

1 | def detect(self, img: Image, roi: list[int] = [], decoder_type: QRCodeDecoderType = ...) - > list[QRCode]

Finds all qrcodes in the image.

https://wiki.sipeed.com/maixpy/api/maix/image.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: The image to find qrcodes.
roi: The region of interest, input in the format of (x, y, w, h), x and y are the coordinates of the upper left corner, w and h are the width and height of roi.
default is None, means whole image.
decoder_type: Select the QR code decoding method. Choosing
QRCODE_DECODER_TYPE_QUIRC allows</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>for retrieving QR code version, ECC level, mask, data type, and other details, though it may decode slower at lower resolutions. Opting for QR CODE DECODER_TYPE_ZBAR enables faster decoding at lower resolutions but may slow down at higher resolutions, providing only the QR code content and position information. default is QR CODE DECODER_TYPE_ZBAR.</td></tr><tr><td>return</td><td>Returns the qrcodes of the image</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<image::QRCode> detect(image::Image *img, std::vector<int> roi = std::vector<int>(   ), image::QRCodeDecoderType decoder_type = image::QRCodeDecoderType::QRCODE_DECODE