# maix.nn

maix.nn module

You can use maix.nn to access this module with MaixPyThis module is generated from MaixPy and MaixCDK

# 1. Module

<table><tr><td>module</td><td>brief</td></tr><tr><td>F</td><td>maix.nn.F module</td></tr></table>

# 2. Enum

# 2.1. SpeechDevice

speech device

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>DEVICE_NONE:
DEVICE_PCM:
DEVICE_MIC:
DEVICE WAV:</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/5966942272038c1deb6e34990fc0301769b76d6ff4aec95e0c3ff7119c61521c.jpg)

# 2.2. SpeechDecoder

speech decoder type

<table><tr><td>item</td><td>describe</td></tr><tr><td>values</td><td>DECODER_RAW:
DECODER_DIG:
DECODER_LVCSR:
DECODER_KWS:
DECODER_ALL:</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/f977848fc524034f08db2b18edeb86a7abdfe3189676dd916983ba0606606e06.jpg)

# 3. Variable

# 4. Function

# 5. Class

# 5.1. NanoTrack

NanoTrack class

$\mathtt{C + + }$  defination code:

1 class NanoTrack

# 5.1.1. init

1 def init_(self, model: str = '') - > None

Constructor of NanoTrack class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 NanoTrack(const string &model = "")

# 5.1.2. load

1 def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err load(const string &model)

# 5.1.3. init

1 | def init(self, img: maix.image.Image, x: int, y: int, w: int, h: int) - > None

Init tracker, give tacker first target image and target position.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, target should be in this image.
x: the target position left top coordinate
x.
y: the target position left top coordinate
y.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>w: the target width.
h: the target height.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void init(image::Image &img, int x, int y, int w, int h)

# 5.1.4. track

1 | def track(self, img: maix.image.Image, threshold: float = 0.9) - > ...

Track object according to last object position and the init function learned target feature.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image to detect object and track, can be any resolution, before detect it will crop a area according to last time target&#x27;s position. 
threshold: If score &amp;lt; threshold, will see this new detection is invalid, but remain return this new detection, default 0.9.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>object, position and score, and detect area in points&#x27;s first 4 element(x, y, w, h, center_x, center_y, input_size, target_size)</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | nn::Object track(image::Image &img, float threshold = 0.9)

# 5.1.5. input_size

<table><tr><td>1 | def input_size(self) -&amp;gt; maix.image.Size</td></tr></table>

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Size input_size()

# 5.1.6. input_width

1 | def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_width()

# 5.1.7.input_height

1 def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.1.8.input_format

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/222c09201cfbd14fa4cb917dd5f13134085f23446736485f94839533fb2955c7.jpg)

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Format input_format()

# 5.1.9. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<float> mean

# 5.1.10. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> scale

# 5.2. Speech

Speech

$\mathtt{C + + }$  defination code:

1 | class Speech

# 5.2.1. init

1 | def __init__(self, model: str = '') - > None

Construct a new Speech object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | Speech(const string &model = "")

# 5.2.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | err::Err load(const string &model)

# 5.2.3. init

1 | def init(self, dev_type: SpeechDevice, device_name: str = '') - > maix.err.Err

Init the ASR library and select the type and name of the audio device.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>dev_type: device type want to detect, can choose between WAV, PCM, or MIC.
device_name: device name want to detect, can choose a WAV file, a PCM file, or a MIC device name.</td></tr><tr><td>throw</td><td>1. If am model is not loaded, will throw err::ERR_NOT Impl.
2. If device is not supported, will throw err::ERR_NOT Impl.</td></tr><tr><td>return</td><td>err::Err type, if init success, return err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err init(nn::SpeechDevice dev_type, const string &device_name = "")

# 5.2.4. devive

1 def devive(self, dev_type: SpeechDevice, device_name: str) - > maix.err.Err

Reset the device, usually used for PCM/WAV recognition, \nsuch as identifying the next WAV file.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>dev_type: device type want to detect, can choose between WAV, PCM, or MIC.
device_name: device name want to detect, can choose a WAV file, a PCM file, or a MIC device name.</td></tr><tr><td>throw</td><td>If device is not supported, will throw err::ERR_NOT_IMPL.</td></tr><tr><td>return</td><td>err::Err type, if init success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err devive(nn::SpeechDevice dev_type, const string &device_name)

# 5.2.5. dec_deinit

def dec_deinit(self, decoder: SpeechDecoder) - > None

Deinit the decoder.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>decoder: decoder type want to deinit
can choose between DECODER_RAW,
DECODER_DIG, DECODER_LVCSR,
DECODER_KWS or DECODER_ALL.</td></tr><tr><td>throw</td><td>If device is not supported, will throw
err::ERR_NOT_IMPL.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void dec_deinit(nn::SpeechDecoder decoder)

# 5.2.6.raw

1 def raw(self, callback: typing.Callable[[list[tuple[int, float]], int], None]) - > maix.err.Err

Init raw decoder, it will output the prediction results of the original AM.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>callback: raw decoder user callback.</td></tr><tr><td>return</td><td>err::Err type, if init success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err raw(std::function<void(std::vector<std: float>>, int)> callback)

# 5.2.7. digit

1 def digit(self, blank: int, callback: typing.Callable[[str, int], None]) - > maix.err.Err

Init digit decoder, it will output the Chinese digit recognition results within the last 4 seconds.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>blank: If it exceeds this value, insert a &#x27;_&#x27; in the output result to indicate idle mute. callback: digit decoder user callback.</td></tr><tr><td>return</td><td>err::Err type, if init success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err digit(int blank, std::function<void(char*, int)> callback)

# 5.2.8. kws

1 def kws(self, kw_tbl: list[str], kw_gate: list[float], callback: typing.Callable[[list[float], int], None], auto_similar: bool = True) - > maix.err.Err

Init kws decoder, it will output a probability list of all registered keywords in the latest frame,\nusers can set their own thresholds for wake- up.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>kw_tbl: Keyword list, filled in with spaces separated by pinyin, for example: xiao3 ai4 tong2 xue2 
kw_gate: kw_gate, keyword probability gate table, the number should be the same as kw_tbl 
auto_similar: Whether to perform automatic homophone processing, setting it to true will automatically calculate the probability by using pinyin with different tones as homophones callback: digit decoder user callback.</td></tr><tr><td>return</td><td>err::Err type, if init success, return 
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err kws(std::vector<string> kw_tbl, std::vector<float> kw_gate,

maix.nn - MaixPy

std::function<void(std::vector<float>, int)> callback, bool auto_similar = true)

# 5.2.9. Ivcsr

1 def lvcsr(self, sfst_name: str, sym_name: str, phones_txt: str, words_txt: str, callback: typing.Caliable[[tuple[str, str], int], None], beam: float = 8, bg_prob: float = 10, scale: float = 0.5, mmap: bool = False) - > maix.err.Err

Init lvcsr decoder, it will output continuous speech recognition results (less than 1024 Chinese characters).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>sfst_name: Sfst file path.
sym_name: Sym file path (output symbol table).
phones_txt: Path to phones.bin (pinyin table).
words_txt: Path to words.bin (dictionary table).
callback: lvcsr decoder user callback.
beam: The beam size for WFSF search is set to 8 by default, and it is recommended to be between 3 and 9.
The larger the size, the larger the search space, and the more accurate but slower the search.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>bg_prob: The absolute value of the natural logarithm of the default probability value for background pinyin outside of BEAM-CNT is set to 10 by default.
scale: acoustics_cost = log(pny_prob)scale.
mmap*: use mmap to load the WFST decoding image,
If set to true, the beam should be less than 5.</td></tr><tr><td>return</td><td>err::Err type, if init success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/7ce7ec4c0245b12b2d7a3757878cb2548bcc2be84d6d8dd0d3bf08063ca57360.jpg)

# 5.2.10. run

1 def run(self, frame: int) - > int

Run speech recognition, user can run 1 frame at a time and do other processing after running, \nor it can run continuously within a thread and be stopped by an external thread.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>frame: The number of frames per run.</td></tr><tr><td>return</td><td>int type, return actual number of frames in the run.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int run(int frame)</td></tr></table>

# 5.2.11. clear

<table><tr><td>1 | def clear(self) -&amp;gt; None</td></tr></table>

Reset internal cache operation

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\bar{\zeta} ++$  definition code:

void clear()

# 5.2.12. frame_time

1 | def frame_time(self) - > int

Get the time of one frame.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>int type, return the time of one frame.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int frame_time()

# 5.2.13. similar

1 | def similar(self, pny: str, similar_pnys: list[str]) - > maix.err.Err

Manually register mute words, and each pinyin can register up to 10 homophones, please note that using this interface to register homophones will overwrite, the homophone table automatically generated in the "automatic homophone processing" feature.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>dev_type: device type want to detect, can choose between WAV, PCM, or MIC.
device_name: device name want to detect, can choose a WAV file, a PCM file, or a MIC device name.</td></tr><tr><td>return</td><td>err::Err type, if init success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err similar(const string &pny, std::vector<std::string> similar_pnys)

# 5.2.14. skip_frames

1 def skip_frames(self, num: int) - > None

Run some frames and drop, this can be used to avoid\nincorrect recognition results when switching decoders.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>num: number of frames to run and drop</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void skip_frames(int num)

# 5.2.15. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.2.16. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.2.17. dev_type

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/4b63b2784885e2072926e26e31e2199b10fd36da991cf7585fefe0f6b8fc7ed4.jpg)

get device type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>nn::SpeechDevice type, see SpeechDevice of this module</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

nn::SpeechDevice dev_type

# 5.3. FaceLandmarksObject

FaceLandmarksObject class

$\mathtt{C + + }$  defination code:

class FaceLandmarksObject

# 5.3.1. init

1 def init self - > None

Valid or not(score > conf_th when detect).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | FaceLandmarksObject()

# 5.3.2. valid

Valid or not(score > conf_th when detect).

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1 | bool valid</td></tr></table>

# 5.3.3. score

whether face in image score, value from 0 to 1.0.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/01edee547d6c84c5f4681e562618efbcc4e7d0ab639587527d642632210fbb05.jpg)

# 5.3.4. points

landmarks points, format: x0, y0, ..., xn- 1, yn- 1.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<int> points

# 5.3.5. points_z

landmarks points, format: z0, z1, ..., zn- 1.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<int> points_z

# 5.4. FaceLandmarks

FaceLandmarks class

$\mathtt{C + + }$  definition code:

1 class FaceLandmarks

# 5.4.1. init

1 def init_(self, model: str = '') - > None

Constructor of FaceLandmarks class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 FaceLandmarks(const string &model = "")

# 5.4.2. load

1 def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err load(const string &model)

# 5.4.3. detect

1 def detect(self, img: maix.image.Image, conf_th: float = 0.5, landmarks_abs: bool = True, landmarks_rel: bool = False) - > FaceLandmarksObject

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size n model input&#x27;s, will auto resize with fit meth conf_th. Hand detect confidence threshold, landmarks_rel: outputs the relative coordin points with respect to the top-left vertex of In obj.points, the last 21x2 values are arran x0y0x1y1...x20y20.
Value from 0 to obj.w.</td></tr><tr><td>throw</td><td>If image format not match model input forr throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it aft Object&#x27;s points value format: box_topleft_x, box_topleft_y, box_topright_x, box_topright box_bottomright_x, box_bottomright_y, box_bottomleft_x, box_bottomleft_y, x0, y0, z1, x1, y1, z2, ..., x20, y20, z20.
If landmarks_rel is True, will be box_topleft_box_topleft_y...,x20,y20,z20,x0_rel,y0_rel...,x Z is depth, the larger the value, the farther the palm, and the positive value means clos camera.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::FaceLandmarksObject *detect(image::Image &img, float conf_th = 0.5, bool landmarks_abs = true, bool landmarks_rel = false)

# 5.4.4. crop_image

1 def crop_image(self, img: maix.image.Image, x: int, y: int, w: int, h: int, points: list[int], new_width: int = - 1, new_height: int = - 1, scale: float = 1.2) - > maix.image.Image

Crop image from source image by 2 points(2 eyes)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x,y,w,h: face rectangle, x,y is left-top point.
img: source image
points: 2 points, eye left x, eye left y, 
eye_right x, eye_right y
scale: crop size scale relative to rectangle&#x27;s max side length (w or h), final value is scale *max (w, h), default 1.2.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 maix::image::Image *crop_image(maix::image::Image &img, int x, int y, int w, int h, std::vector<int> points, int new_width = - 1, int new_height = - 1, float scale = 1.2)

# 5.4.5. input_size

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/ffc86339911185061707f575030983898f3914de0c0c806304c1af22e2af0902.jpg)

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size input_size(bool detect = true)

# 5.4.6. input_width

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/d19c9e87a7e07207d133b19682b1a4a6a8f9d75fdc3f42c69fc360841af902b4.jpg)

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size of width</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int input_width(bool detect = true)

# 5.4.7. input_height

1 def input_height(self, detect: bool = True) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int input_height(bool detect = true)

# 5.4.8. input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Format input_format()

# 5.4.9. draw_face

1 | def draw_face(self, img: maix.image.Image, points: list[int], num: int, points_z: list[int] = [], r_min: int = 2, r_max: int = 4) - > None

Draw hand and landmarks on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
leftright: 0 means left, 1 means right
points: points result from detect
method: x0, y0, x1, y1, ..., xn-1, yn-1.
points_z: points result from detect
method: z0, z1, ..., zn-1.
r_min: min radius of points.
r_max: min radius of points.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void draw_face(image::Image &img, const std::vector<int> &points, int num, const std::vector<int> &points_z=std::vector<int>(), int r_min = 2, int r_max = 4)

# 5.4.10. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.4.11. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.4.12. landmarks_num

landmarks number.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | int landmarks_num

# 5.5. SelfLearnClassifier

SelfLearnClassifier

$\mathtt{C + + }$  definition code:

1 | class SelfLearnClassifier

# 5.5.1. _init_

1 | def __init__(self, model: str = '', dual_buff: bool = True) - > None

Construct a new SelfLearnClassifier object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: MUD model path, if empty, will not load model, you can call load_model() later.
if not empty, will load model and will raise err:Exception if load failed.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | SelfLearnClassifier(const std::string &amp;amp;model = &quot;&quot;, bool dual_buff = true)</td></tr></table>

# 5.5.2. load_model

1 | def load_model(self, model: str) - > maix.err.Err

Load model from file, model format is .mud,\nMUD file should contain [extra] section, have key- values:\n- model_type: classifier_no_top\n- input_type: rgb or bgr\n- mean: 123.675, 116.28, 103.53\n- scale: 0.017124753831663668, 0.01750700280112045, 0.017429193899782137

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: MUD model path</td></tr><tr><td>return</td><td>error code, if load failed, return error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err load_model(const string &model)

# 5.5.3. classify

1 | def classify(self, img: maix.image.Image, fit: maix.image.Fit = ...) - > list[tuple[int, float]]

Classify image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image, format should match model input_type, or will raise err.Exception fit: image resize fit mode, default Fit.FIT_COVER, see image.Fit.</td></tr><tr><td>throw</td><td>If error occurred, will raise err::Exception, you can find reason in log, mostly caused by args error or hardware error.</td></tr><tr><td>return</td><td>result, a list of (idx, distance), smaller distance means more similar. In C++, you need to delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::pair<int, float>> *classify(image::Image & img, image::Fit fit = image::FIT_COVER)

# 5.5.4. add_class

1 | def add_class(self, img: maix.image.Image, fit: maix.image.Fit = ...) - > None

Add a class to recognize

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>img: Add a image as a new class
fit: image resize fit mode, default
Fit.FIT_COVER, see image.Fit.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void add_class(image::Image &img, image::Fit fit = image::FIT_COVER)

# 5.5.5. class_num

1 | def class_num(self) - > int

Get class number

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | int class_num()

# 5.5.6. rm_class

1 | def rm_class(self, idx: int) - > maix.err.Err

# Remove a class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>idx: index, value from 0 to class_num();</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err rm_class(int idx)

# 5.5.7. add_sample

1 def add_sample(self, img: maix.image.Image, fit: maix.image.Fit = ...) - > None

Add sample, you should call learn method after add some samples to learn classes.\nSample image can be any of classes we already added.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Add a image as a new sample.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 void add_sample(image::Image &img, image::Fit fit = image::FIT_COVER)

# 5.5.8. rm_sample

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/c91a635ec41fdf2768a8599952d6280888a4f618077a632178ed7003916e8882.jpg)

Remove a sample

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>idx: index, value from 0 to sample_num();</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

err::Err rm_sample(int idx)

# 5.5.9. sample_num

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/6f64ad062f87bb4050af8225afdc7e913e7c4e59b9f16217a4706fe59d72833b.jpg)

Get sample number

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

int sample_num()

# 5.5.10. learn

1 | def learn(self) - > int

Start auto learn class features from classes image and samples. In You should call this method after you add some samples.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>learn epoch(times), 0 means learn nothing.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | int learn()</td></tr></table>

# 5.5.11. clear

<table><tr><td>1 | def clear(self) -&amp;gt; None</td></tr></table>

Clear all class and samples

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

void clear()

# 5.5.12. input_size

1 | def input_size(self) - > maix.image.Size

Get model input size, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size input_size()

# 5.5.13. input_width

1 | def input_width(self) - > int

Get model input width, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int input_width()

# 5.5.14. input_height

1 | def input_height(self) - > int

Get model input height, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int input_height()

# 5.5.15. input_format

1 | def input_format(self) - > maix.image.Format

Get input image format, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Format input_format()

# 5.5.16. input_shape

1 | def input_shape(self) - > list[int]

Get input shape, if have multiple input, only return first input shape

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input shape, list type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> input_shape()

# 5.5.17. save

1 | def save(self, path: str, labels: list[str] = []) - > maix.err.Err

Save features and labels to a binary file.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>path: file path to save, e.g.
/root/my_classes.bin
labels: class labels, can be None, or length must equal to class num, or will return err::Err</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>maix.errErr if labels exists but length not equal to class num, or save file failed, or class num is 0.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

err::Err save(const std::string &path, const std::vector<std::string> &labels = std::vector<std::string>())

# 5.5.18.load

1 def load(self, path: str) - > list[str]

Load features info from binary file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>path: feature info binary file path, e.g. /root/my_classes.bin</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<std::string> load(const std::string &path)

# 5.5.19.labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<string> labels

# 5.5.20.label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::string label_path

# 5.5.21. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<float> mean

# 5.5.22. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<float> scale

# 5.6. YOLOv8

YOLOv8 class

$\mathtt{C + + }$  definition code:

class YOLOv8

# 5.6.1. init

1 | def __init__(self, model: str = '', dual_buff: bool = True) - > None

Constructor of YOLOv8 class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | YOLOv8(const string &model = "", bool dual_buff = true)

# 5.6.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err load(const string &model)

# 5.6.3. detect

1 def detect(self, img: maix.image.Image, conf_th: float = 0.5, iou_th: float = 0.45, fit: maix.image.Fit = ..., keypoint_th: float = 0.5, sort: int = 0) - > ...

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
conf_th: Confidence threshold, default 0.5.
iou_th: IoU threshold, default 0.45.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>fit: Resize method, default
image缩小 FIT_CONTAIN.
keypoint_th: keypoint threshold, default
0.5, only for yolov8-pose model.
sort: sort result according to object size,
default 0 means not sort, 1 means bigger
in front, -1 means smaller in front.</td></tr><tr><td>throw</td><td>If image format not match model input
format, will throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it
after use.
If model is yolov8-pose, object&#x27;s points
have value, and if points&#x27; value &amp;lt; 0
means that point is invalid(conf &amp;lt; keypoint_th).</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::Objects *detect(image::Image &amp;img, float conf_th = 0.5, float iou_th = 0.45, maix::image::Fit fit = maix::image::FIT_CONTAIN, float keypoint_th = 0.5, int sort = 0)

# 5.6.4. input_size

<table><tr><td>1 | def input_size(self) -&amp;gt; maix.image.Size</td></tr></table>

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size input_size()

# 5.6.5. input_width

def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int input_width()

# 5.6.6. input_height

def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.6.7.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format input_format()

# 5.6.8.draw_pose

1 def draw_pose(self, img: maix.image.Image, points: list[int], radius: int = 4, color:

maix.image.Color = ..., colors: list[maix.image.Color] = [], body: bool = True, close: bool = False) - > None

Draw pose keypoints on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
points: keypoints, int list type, [x, y, x, y ...]
radius: radius of points.
color: color of points.
colors: assign colors for points, list type,
element is image.Color object.
body: true, if points&#x27; length is 172 and
body is true, will draw lines as human
body, if set to false won&#x27;t draw lines,
default true.
close*: connect all points to close a
polygon, default false.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

void draw_pose(image::Image &img, std::vector<int> points, int radius = 4, image::Color color = image::COLOR_RED, const std::vector(image::Color> &colors = std::vector(image::Color>(), bool body = true, bool close = false)

# 5.6.9. draw_seg_mask

1 def draw_seg_mask(self, img: maix.image.Image, x: int, y: int, seg_mask: maix.image.Image, threshold: int = 127) - > None

Draw segmentation on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
seg_mask: segmentation mask image by
detect method, a grayscale image
threshold: only mask&#x27;s value &amp;gt; threshold
will be draw on image, value from 0 to
255.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

void draw_seg_mask(image::Image &img, int x, int y, image::Image &seg_mask, int threshold = 127)

# 5.6.10. labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<string> labels

# 5.6.11.label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string label_path

# 5.6.12. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.6.13. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.7. YOLO11

YOLO11 class

$\mathtt{C + + }$  definition code:

1 | class YOLO11

# 5.7.1. init

1 | def __init__(self, model: str = '', dual_buff: bool = True) - > None

# Constructor of YOLO11 class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | YOLO11(const string &model = "", bool dual_buff = true)

# 5.7.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err load(const string &model)

# 5.7.3. detect

1 | def detect(self, img: maix.image.Image, conf_th: float = 0.5, iou_th: float = 0.45, fit: maix.image.Fit = ..., keypoint_th: float = 0.5, sort: int = 0) - > ...

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
conf_th: Confidence threshold, default 0.5.
iou_th: IoU threshold, default 0.45.
fit: Resize method, default image.Fit.FIT_CONTAIN.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>keypoint_th: keypoint threshold, default 0.5, only for yolo11-pose model.
sort: sort result according to object size, default 0 means not sort, 1 means bigger in front, -1 means smaller in front.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it after use.
If model is yolo11-pose, object&#x27;s points have value, and if points&#x27; value &amp;lt; 0 means that point is invalid(conf &amp;lt; keypoint_th).</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::Objects *detect(image::Image &img, float conf_th = 0.5, float iou_th = 0.45, maix::image::Fit fit = maix::image::FIT_CONTAIN, float keypoint_th = 0.5, int sort = 0)

# 5.7.4. input_size

1 | def input_size(self) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Size input_size()

# 5.7.5. input_width

1 | def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int input_width()

# 5.7.6. input_height

1 | def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.7.7.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format input_format()

# 5.7.8.draw_pose

1 def draw_pose(self, img: maix.image.Image, points: list[int], radius: int = 4, color:

maix.image.Color = ..., colors: list[maix.image.Color] = [], body: bool = True, close: bool = False) - > None

Draw pose keypoints on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
points: keypoints, int list type, [x, y, x, y ...]
radius: radius of points.
color: color of points.
colors: assign colors for points, list type,
element is image.Color object.
body: true, if points&#x27; length is 172 and
body is true, will draw lines as human
body, if set to false won&#x27;t draw lines,
default true.
close*: connect all points to close a
polygon, default false.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void draw_pose(image::Image &img, std::vector<int> points, int radius = 4, image::Color color = image::COLOR_RED, const std::vectorimage::Color> &colors = std::vectorimage::Color>(), bool body = true, bool close = false)

# 5.7.9. draw_seg_mask

1 def draw_seg_mask(self, img: maix.image.Image, x: int, y: int, seg_mask: maix.image.Image, threshold: int = 127) - > None

Draw segmentation on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
seg_mask: segmentation mask image by
detect method, a grayscale image
threshold: only mask&#x27;s value &amp;gt; threshold
will be draw on image, value from 0 to
255.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

void draw_seg_mask(image::Image &img, int x, int y, image::Image &seg_mask, int threshold = 127)

# 5.7.10. labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<string> labels

# 5.7.11.label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::string label_path

# 5.7.12. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.7.13. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.8. YOLOv5

YOLOv5 class

$\mathtt{C + + }$  definition code:

1 | class YOLOv5

# 5.8.1. init

1 | def __init__(self, model: str = '', dual_buff: bool = True) - > None

# Constructor of YOLOv5 class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | YOLOv5(const string &model = "", bool dual_buff = true)

# 5.8.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err load(const string &model)

# 5.8.3. detect

1 | def detect(self, img: maix.image.Image, conf_th: float = 0.5, iou_th: float = 0.45, fit: maix.image.Fit - - - , sort: int = 0) - - > list[...]

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
conf_th: Confidence threshold, default 0.5.
iou_th: IoU threshold, default 0.45.
fit: Resize method, default image.Fit.FIT_CONTAIN.
sort: sort result according to object size,</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>default 0 means not sort, 1 means bigger in front, -1 means smaller in front.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<nn::Object> \*detect(image::Image &img,float conf_th  $= \Theta \cdot 5$  float iou_th  $= 0.45$  maix::image::Fit fit  $=$  maix::image::FIT_CONTAIN, int sort  $=$  0)

# 5.8.4. input_size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Size input_size()

# 5.8.5. input_width

1 | def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int input_width()

# 5.8.6. input_height

1 | def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.8.7.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | image::Format input_format()</td></tr></table>

# 5.8.8.labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<string> labels

# 5.8.9. label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::string label_path

# 5.8.10. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.8.11. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.8.12. anchors

Get anchors

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> anchors

# 5.9. HandLandmarks

HandLandmarks class

$\mathtt{C + + }$  definition code:

1 | class HandLandmarks

# 5.9.1. init

1 | def init_(self, model: str = '') - > None

Constructor of HandLandmarks class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | HandLandmarks(const string &model = "")

# 5.9.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err load(const string &model)

# 5.9.3. detect

1 def detect(self, img: maix.image.Image, conf_th: float = 0.7, iou_th: float = 0.45, conf_th2: float = 0.8, landmarks_rel: bool = False) - > ...

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size n model input&#x27;s, will auto resize with fit meth conf_th: Hand detect confidence threshold, iou_th: IoU threshold, default 0.45. conf_th2: Hand detect confidence second t threshold, default 0.8. landmarks_rel: outputs the relative coordin points with respect to the top-left vertex of In obj.points, the last 21x2 values are arran x0y0x1y1...x20y20. Value from 0 to obj.w.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>throw</td><td>If image format not match model input for
throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it after
Object&#x27;s points value format: box_topleft_x,
box_topleft_y, box_topright_x, box_topright
box_bottomright_x, box_bottomright_y,
box_bottomleft_x, box_bottomleft_y,
x0, y0, z1, x1, y1, z2, ..., x20, y20, z20.
If landmarks_rel is True, will be box_topleft_
box_topleft_y..., x20, y20, z20, x0_rel, y0_rel, ..., x
Z is depth, the larger the value, the farther
the palm, and the positive value means clos
camera.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::Objects *detect(image::Image &img, float conf_th = 0.7, float iou_th = 0.45, float conf_th2 = 0.8, bool landmarks_rel = false)

# 5.9.4. input_size

1 | def input_size(self, detect: bool = True) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Size input_size(bool detect = true)

# 5.9.5. input_width

<table><tr><td>1</td><td>def input_width(self, detect: bool = True) -&amp;gt; int</td></tr></table>

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int input_width(bool detect = true)

# 5.9.6. input_height

1 | def input_height(self, detect: bool = True) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect: detect or landmarks model, default true.</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ defination code:</td></tr><tr><td colspan="2">1 | int input_height(bool detect = true)</td></tr></table>

# 5.9.7. input_format

1 | def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | image::Format input_format()

# 5.9.8. draw_hand

1 | def draw_hand(self, img: maix.image.Image, leftright: int, points: list[int], r_min: int = 4, r_max: int = 10, box: bool = True, box_thickness: int = 1, box_color_l: maix.image.Color = ..., box_color_r: maix.image.Color = ...) - > None

Draw hand and landmarks on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
leftright: 0 means left, 1 means right
points: points result from detect
method: box_topleft_x, box_topleft_y,
box_topright_x, box_topright_y,
box_bottomright_x, box_bottomright_y,
box_bottomleft_x, box_bottomleft_y,
x0, y0, z1, x1, y1, z2, ..., x20, y20, z20
r_min: min radius of points.
r_max: min radius of points.
box: draw box or not, default true.
box_color: color of box.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void draw_hand(image::Image &img, int leftright, const std::vector<int> &points, int r_min = 4, int r_max = 10, bool box = true, int box_thickness = 1, image::Color box_color_l = image::COLOR_RED, image::Color box_color_r = image::COLOR_GREEN)

# 5.9.9. labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::string> labels

# 5.9.10. label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::string label_path

# 5.9.11. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.9.12. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.10. OCR_Box

Object for OCR detect box

$\mathtt{C + + }$  definition code:

1 | class OCR_Box

# 5.10.1. init

1 | def init_(self, x1: int = 0, y1: int = 0, x2: int = 0, y2: int = 0, x3: int = 0, y3: int = 0, x4: int = 0, y4: int = 0) - > None

OCR_Box constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | OCR_Box (int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int x3 = 0, int

# 5.10.2.x1

left top point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x1

# 5.10.3.y1

left top point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y1

# 5.10.4.x2

right top point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x2

# 5.10.5.y2

right top point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int y2

# 5.10.6.x3

right bottom point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int x3

# 5.10.7.y3

right bottom point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int y3

# 5.10.8.x4

left bottom point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int x4

# 5.10.9. y4

left bottom point of box

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int y4

# 5.10.10. to list

1 def to_list(self) - > list[int]

convert box point to a list type.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>list type, element is int type, value [x1, y1, x2, y2, x3, y3, x4, y4].</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<int> to_list()

# 5.11. OCR_Object

Object for OCR detect result

$\mathtt{C + + }$  definition code:

1 | class OCR_Object

# 5.11.1. init

1 | def __init__(self, box: OCR_Box, idx_list: list[int], char_list: list[str], score: float = 0, char_pos: list[int] = []) - > None

Constructor of Object for OCR detect result

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>score: score</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | OCR_Object(const nn::OCR_Box &box, const std::vector<int> &idx_list, const std::vector<std::string> &char_list, float score = 0, const

# 5.11.2. box

OCR_Object box, 4 points box, first point at the left- top, clock- wise.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

# 5.11.3. score

Object score

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | float score

# 5.11.4.idx_list

chars' idx list, element is int type.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> idx_list

# 5.11.5.char_pos

Chars' position relative to left

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> char_pos

# 5.11.6.char_str

1 | def char_str(self) - > str

Get OCR_Object's characters, return a string type.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>All characters in string type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 const std::string &char_str()

# 5.11.7.char_list

1 def char_list(self) - > list[str]

Get OCR_Object's characters, return a list type.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>All characters in list type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 const std::vector<std::string>&char_list()

# 5.11.8.update_chars

1 | def update_chars(self, char_list: list[str]) - > None

# Set OCR_Object's characters

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>char_list: All characters in list type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void update_chars(const std::vector<std::string> &char_list)

# 5.11.9. __str__

1 | def __str__(self) - > str

# OCR_Object info to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>OCR_Object info string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::string to_str()

# 5.12. OCR Objects

OCR_Objects Class for detect result

$\mathtt{C + + }$  defination code:

1 class OCR Objects

# 5.12.1. init

1 def init self - > None

Constructor of OCR Objects class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

OCR Objects()

# 5.12.2. add

1 def add(self, box: OCR_Box, idx_list: list[int], char_list: list[str], score: float = 0, char_pos: list[int] = []) - > OCR_Object

Add object to objects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>throw</td><td>Throw exception if no memory</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 nn::OCR_Object &add(const nn::OCR_Box &box, const std::vector<int>&idx_list, const std::vector<std::string>&char_list,float score  $= 0$  const std::vector<int>&char_pos  $=$  std::vector<int>（)

# 5.12.3.remove

1 def remove(self,idx:int)- > maix.err.Err

Remove object form objects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err remove(int idx)

# 5.12.4.at

1 | def at(self, idx: int) - > OCR_Object

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::OCR_Object &at(int idx)

# 5.12.5. __getitem__

1 | def __getitem__(self, idx: int) - > OCR_Object

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::OCR_Object &operator[](int idx)

# 5.12.6. __len__

1 | def __len__(self) - > int

Get size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | size_t size()

# 5.12.7. __iter__

1 | def __iter__(self) - > typing.Iterator

Begin

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<OCR_Object>::iterator begin()

# 5.13. FaceObject

Face object

$\mathtt{C + + }$  defination code:

1 class FaceObject

# 5.13.1. init

1 def init_(self, x: int = 0, y: int = 0, w: int = 0, h: int = 0, class_id: int = 0, score: float = 0, points: list[int] = [], feature: list[float] = [], face: maix.image.Image = ...)- > None

Constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 FaceObject(int  $x = 0$  ,int  $y = 0$  ,int  $w = 0$  ,int  $h = 0$  ,int class_id  $= 0$  float score  $= 0$  ,std::vector<int> points  $=$  std::vector<int>(), std::vector<float> feature  $=$  std::vector<float>(),image::Image face  $=$  image::Image)

# 5.13.2. str

1 def str_(self) - > str

FaceObject info to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>FaceObject info string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::string to_str()

# 5.13.3.x

FaceObject left top coordinate x

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int x

# 5.13.4.y

FaceObject left top coordinate y

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int y

# 5.13.5.w

FaceObject width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

<table><tr><td>1 | int w</td></tr></table>

# 5.13.6.h

FaceObject height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/3da7613121180123d359e72b53b211a4a86249348a4b7dfdbe091f65d3a5b1b9.jpg)

# 5.13.7.class id

FaceObject class id

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

# 5.13.8.score

FaceObject score

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

# 5.13.9. points

keypoints

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> points

# 5.13.10. feature

feature, float list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> feature

# 5.13.11. face

face image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

image::Image face

# 5.14. FaceObjects

Objects Class for detect result

$\mathtt{C + + }$  definition code:

class FaceObjects

# 5.14.1. init

def init__self- > None

Constructor of FaceObjects class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

FaceObjects()

# 5.14.2. add

1 def add(self, x: int  $= 0$  y: int  $= 0$  w: int  $= 0$  h: int  $= 0$  class_id: int  $=$  0, score: float  $= 0$  points: list[int]  $=$  [], feature: list[float]  $=$  [], face: maix.image.Image  $\equiv$  ..- > Faceobject

Add object to FaceObjects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>throw</td><td>Throw exception if no memory</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 nn::FaceObject &add(int  $x = 0$  int y  $= 0$  int  $w = 0$  int  $h = 0$  int class_id  $= 0$  float score  $= 0$  std::vector<int> points  $=$  std::vector<int>(), std::vector<float> feature  $=$  std::vector<float>(), image::Image face  $=$  image::Image)

# 5.14.3. remove

1 def remove(self, idx: int) - > maix.err.Err

Remove object form FaceObjects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err remove(int idx)

# 5.14.4. at

1 def at(self, idx: int) - > FaceObject

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

nn::FaceObject &at(int idx)

# 5.14.5. getitem

1 def __getitem__(self, idx: int) - > FaceObject

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

nn::FaceObject &operator[](int idx)

# 5.14.6. len

1 def __len__(self) - > int

Get size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

size_t size()

# 5.14.7. iter

1 def __iter__(self) - > typing.Iterator

Begin

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<FaceObject*>::iterator begin()

# 5.15. FaceRecognizer

FaceRecognizer class

$\mathtt{C + + }$  definition code:

1 | class FaceRecognizer

# 5.15.1. init

1 | def init_(self, detect_model: str = '', feature_model: str = '', dual_buff: bool = True) - > None

Constructor of FaceRecognizer class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect_model: face detect model path, default empty, you can load model later by load function.
feature_model: feature extract model
dual_buff: direction [in], prepare dual</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>input output buffer to accelerate
forward, that is, when NPU is forwarding
we not wait and prepare the next input
buff.
If you want to ensure every time forward
output the input&#x27;s result, set this arg to
false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load
failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | FaceRecognizer(const string &detect_model = "", const string &feature_model = "", bool dual_buff = true)

# 5.15.2. load

1 | def load(self, detect_model: str, feature_model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>detect_model: face detect model path, default empty, you can load model later</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>by load function.
feature_model: feature extract model</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | err::Err load(const string &detect_model, const string &feature_model)

# 5.15.3. recognize

1 | def recognize(self, img: maix.image.Image, conf_th: float = 0.5, iou_th: float = 0.45, compare_th: float = 0.8, get_feature: bool = False, get_face: bool = False, fit: maix.image.Fit = ...) - > FaceObjects

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
conf_th: Detect confidence threshold, default 0.5.
iou_th: Detect IoU threshold, default 0.45.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>compare_th: Compare two face score
threshold, default 0.8, if two faces&#x27; score &amp;lt; this value, will see this face as unknown.
get_feature: return feature or not, if true
will copy features to result, if false will not copy feature to result to save time and memory.
get_face: return face image or not, if true result object&#x27;s face attribute will valid, or face attribute is empty. Get face image will alloc memory and copy image, so will lead to slower speed.
fit: Resize method, default image.Fit.FIT_CONTAIN.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>return</td><td>FaceObjects object. In C++, you should delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::FaceObjects *recognize(image::Image & img, float conf_th = 0.5, float iou_th = 0.45, float compare_th = 0.8, bool get_feature = false, bool get_face = false, maix::image::Fit fit = maix::image::FIT_CONTAIN)

# 5.15.4. add_face

1 | def add_face(self, face: FaceObject, label: str) - > maix.err.Err

Add face to lib

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>face: face object, find by recognize label: face label(name)</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err add_face(nn::FaceObject *face, const std::string &label)

# 5.15.5. remove_face

1 | def remove_face(self, idx: int = - 1, label: str = '') - > maix.err.Err

remove face from lib

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>idx: index of face in lib, default -1 means use label, value [0, face_num), idx and label must have one, idx have high priotiry.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>label: which face to remove, default to empty string mean use idx, idx and label must have one, idx have high priotiry.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | err::Err remove_face(int idx = - 1, const std::string &label = "")

# 5.15.6. save_faces

1 | def save_faces(self, path: str) - > maix.err.Err

Save faces info to a file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>path: where to save, string type.</td></tr><tr><td>return</td><td>err.Err type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | err::Err save_faces(const std::string &path)

# 5.15.7. load_faces

1 def load_faces(self, path: str) - > maix.err.Err

Load faces info from a file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>path: from where to load, string type.</td></tr><tr><td>return</td><td>err::Err type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err load_faces(const std::string &path)

# 5.15.8.input_size

def input_size(self) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Size input_size()

# 5.15.9. input_width

1 | def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int input_width()

# 5.15.10. input_height

1 | def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.15.11.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | image::Format input_format()</td></tr></table>

# 5.15.12.mean_detector

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<float> mean_detector

# 5.15.13. scaleDetector

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> scale_detector

# 5.15.14. mean_feature

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> mean_feature

# 5.15.15. scale_feature

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> scale_feature

# 5.15.16. labels

labels, list type, first is "unknown"

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<std::string> labels

# 5.15.17. features

features

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::vector<float>> features

# 5.16. Retinaface

Retinaface class

$\mathtt{C + + }$  definition code:

1 | class Retinaface

# 5.16.1. init

1 | def init_(self, model: str = '', dual_buff: bool = True) - > None

Constructor of Retinaface class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

Retinaface(const string &model = "", bool dual_buff = true)

# 5.16.2. load

1 def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err load(const string &model)

# 5.16.3. detect

1 | def detect(self, img: maix.image.Image, conf_th: float = 0.4, iou_th: float = 0.45, fit: maix.image.Fit = ...) - > list[...]

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
conf_th: Confidence threshold, default 0.4.
iou_th: IoU threshold, default 0.45.
fit: Resize method, default image.Fit.FIT_CONTAIN.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<nn::Object> *detect(image::Image &img, float

maix.nn - MaixPy

conf_th = 0.4, float iou_th = 0.45, maix::image::Fit fit = maix::image::FIT_CONTAIN)

# 5.16.4. input_size

1 | def input_size(self) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | image::Size input_size()

# 5.16.5. input_width

1 | def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int input_width()

# 5.16.6. input_height

1 def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int input_height()

# 5.16.7. input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::format input_format()

# 5.16.8. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> mean

# 5.16.9. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<float> scale

# 5.17. PP_OCR

PP_OCR class

$\mathtt{C + + }$  defination code:

1 | class PP_OCR

# 5.17.1. init

1 | def init_(self, model: str = '') - > None

Constructor of PP_OCR class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | PP_OCR(const string &model = "")

# 5.17.2. load

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/8d9368862e5edf6c588e1c2f450957e10f8dcbafbfc6133a700b901a8d581430.jpg)

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

err::Err load(const string &model)

# 5.17.3. detect

1 def detect(self, img: maix.image.Image, thresh: float = 0.3, box_thresh: float = 0.6, fit: maix.image.Fit = ..., char_box: bool = False) - > OCR Objects

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.
thresh: Confidence threshold where pixels have character, default 0.3.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>box_threshold: Box threshold, the box prob higher than this value will be valid, default 0.6.
fit: Resize method, default image.Fit.FIT_CONTAIN.
char_box: Calculate every character&#x27;s box, default false, if true then you can get character&#x27;s box by nn.OCR_Object&#x27;s char boxes attribute.</td></tr><tr><td>throw</td><td>If image format not match model input format or no memory, will throw err::Exception.</td></tr><tr><td>return</td><td>nn.OCR Objects type. In C++, you should delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | nn::OCR_Objects *detect(image::Image &img, float thresh = 0.3, float box_threshold = 0.6, maix::image::Fit fit = maix::image::FIT_CONTAIN, bool char_box = false)

# 5.17.4. recognize

1 | def recognize(self, img: maix.image.Image, box_points: list[int] = []) - > OCR_Object

Only recognize, not detect

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image to recognize chractors, can be a stard cropped chractors image, if crop image not standard, you can use box_points to assign where the chractors&#x27; 4 corner is.
box_points: list type, length must be 8 or 0, default empty means not transfer image to standard image.
4 points postiion, format: [x1, y1, x2, y2, x3, y3, x4, y4], point 1 at the left-top, point 2 right-top...
char_box: Calculate every chractor&#x27;s box, default false, if true then you can get chractor&#x27;s box by nn.OCR_Object&#x27;s char Boxes attribute.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | nn::OCR_Object  *recognize(image::Image & img, const std::vector<int> & box_points = std::vector<int>()

# 5.17.5. draw_seg_mask

1 | def draw_seg_mask(self, img: maix.image.Image, x: int, y: int, seg_mask: maix.image.Image, threshold:

Draw segmentation on image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image object, maix.image.Image
type.
seg_mask: segmentation mask image by
detect method, a grayscale image
threshold: only mask&#x27;s value &amp;gt; threshold
will be draw on image, value from 0 to
255.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  defination code:

1 | void draw_seg_mask(image::Image &img, int x, int y, image::Image &seg_mask, int threshold = 127)

# 5.17.6. input_size

1 | def input_size(self) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size input_size()

# 5.17.7.input_width

1 def input_width(self) - > int

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int input_width()

# 5.17.8.input height

def input_height(self) - > int

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int input_height()

# 5.17.9.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format input_format()

# 5.17.10.mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> mean

# 5.17.11. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<float> scale

# 5.17.12. rec_mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<float> rec_mean

# 5.17.13.rec_scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<float> rec_scale

# 5.17.14.labels

labels (characters)

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<std::string> labels

# 5.17.15. det

model have detect model

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool det

# 5.17.16. rec

model have recognize model

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 bool rec

# 5.18. FaceDetector

FaceDetector class

$\mathtt{C + + }$  definition code:

# 5.18.1. init

1 | def init__(self, model: str = '', dual_buff: bool = True) - > None

Constructor of FaceDetector class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: model path, default empty, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to false please.
Default true to ensure speed.</td></tr><tr><td>throw</td><td>If model arg is not empty and load failed, will throw err::Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | FaceDetector(const string &model = "", bool dual_buff = true)

# 5.18.2.load

1 def load(self, model: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: Model path want to load</td></tr><tr><td>return</td><td>err::Err</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err load(const string &model)

# 5.18.3. detect

1 def detect(self, img: maix.image.Image, conf_th: float = 0.5, iou_th: float = 0.45, fit: maix.image.Fit = ...) - > list[...]

Detect objects from image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: Image want to detect, if image&#x27;s size not match model input&#x27;s, will auto resize with fit method.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>conf_th: Confidence threshold, default 0.5.
iou_th: IoU threshold, default 0.45.
fit: Resize method, default image.Fit.FIT_CONTAIN.</td></tr><tr><td>throw</td><td>If image format not match model input format, will throw err::Exception.</td></tr><tr><td>return</td><td>Object list. In C++, you should delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<nn::Object> *detect(image::Image & img, float conf_th = 0.5, float iou_th = 0.45, maix::image::Fit fit = maix::image::FIT_CONTAIN)

# 5.18.4. input_size

1 | def input_size(self) - > maix.image.Size

Get model input size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | image::Size input_size()

# 5.18.5. input_width

Get model input width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | int input_width()

# 5.18.6. input_height

Get model input height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 int input_height()

# 5.18.7.input_format

1 def input_format(self) - > maix.image.Format

Get input image format

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

image::Format input_format()

# 5.18.8. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<float> mean

# 5.18.9. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.19. Object

Object for detect result

$\mathtt{C + + }$  definition code:

1 | class Object

# 5.19.1. init

1 | def init_(self, x: int = 0, y: int = 0, w: int = 0, h: int = 0, class_id: int = 0, score: float = 0, points: list[int] = [], angle: float = - 9999) - > None

Constructor of Object for detect result

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: left top x
y: left top y
w: width
h: height
class_id: class id
score: score</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 Object(int  $x = 0$  int  $y = 0$  int  $w =$  0,int  $h = 0$  int class id  $= 0$  float score  $= 6$  ,std::vector<int> points  $=$  std::vector<int>(), float angle  $=$  - 9999)

# 5.19.2. __str__

1 def __str__(self) - > str

Object info to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Object info string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::string to_str()

# 5.19.3. get_obb_points

1 | def get_obb_points(self) - > list[int]

Get OBB(oriented bounding box) points, auto calculated according to x,y,w,h,angle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\zeta + +$  definition code:

1 | std::vector<int> get_obb_points()

# 5.19.4. x

Object left top coordinate x

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\zeta + +$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/cff80a98024998fc13a32113eabb2719a18e00ee3b526831390275b269e74f02.jpg)

# 5.19.5. y

Object left top coordinate y

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/1de8c3c8e86ae49c5cc3d3636991f8a6952052c1d1814761b8a5937178e73883.jpg)

# 5.19.6.w

Object width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/0748911d099adaaa62e9e3250d8c28dbfc9b35b5f97e7cb42ae3d796b3758a12.jpg)

# 5.19.7.h

Object height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int h

# 5.19.8.class_id

Object class id

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int class_id

# 5.19.9.score

Object score

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

float score

# 5.19.10. points

keypoints

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

std::vector<int> points

# 5.19.11. angle

Rotate angle, - 9999 means not set, value is a percentage, need to multiply 180 to get the real angle or multiply PI to get the radian.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float angle

# 5.19.12. seg_mask

segmentation mask, uint8 list type, shape is h * w but flattened to one dimension, value fron 0 to 255.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>attention</td><td>For efficiency, it&#x27;s a pointer in C++, use this carefully!</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Image *seg_mask

# 5.20. ObjectFloat

Object for detect result

$\mathtt{C + + }$  defination code:

1 class ObjectFloat

# 5.20.1. init

1 def init_(self, x: float = 0, y: float = 0, w: float = 0, h: float = 0, class_id: float = 0, score: float = 0, points: list[float] = [], angle: float = - 1) - > None

Constructor of Object for detect result

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>x: left top x
y: left top y
w: width
h: height
class_id: class id
score: score</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 ObjectFloat(float x = 0, float y = 0, float w = 0, float h = 0, float class_id = 0, float score = 0, std::vector<float> points = std::vector<float>(), float angle = - 1)

# 5.20.2. str

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/c51260cd88fa1fb71687c7f135f8ad6119904684a867d665cc16c65e355a9c4a.jpg)

Object info to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>Object info string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::string to_str()

# 5.20.3.x

Object left top coordinate x

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 float x

# 5.20.4.y

Object left top coordinate y

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 float y

# 5.20.5.w

Object width

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 float w

# 5.20.6.h

Object height

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 float h

# 5.20.7.class_id

Object class id

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 float class_id

# 5.20.8.score

Object score

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/d7637911887c7d4a1b8866f1ee3389ce3e40050b1c4d9432b586a380ea9ba3e3.jpg)

# 5.20.9. points

keypoints

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

# 5.20.10. angle

Rotate angle

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | float angle

# 5.21. Objects

Objects Class for detect result

$\mathtt{C + + }$  definition code:

1 class Objects

# 5.21.1. init

1 def init (self) - > None

Constructor of Objects class

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 Objects()

# 5.21.2. add

1 def add(self, x: int = 0, y: int = 0, w: int = 0, h: int = 0, class_id: int = 0, score: float = 0, points: list[int] = [], angle: float = - 1) - > Object

Add object to objects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>throw</td><td>Throw exception if no memory</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 nn::Object &add(int  $x = 0$  ,int  $y = 0$  int  $w = 0$  ,int  $h = 0$  ,int class_id  $=$  0,float score  $= 0$  ,std::vector<int> points  $=$  std::vector<int>(),float angle  $= - 1$

# 5.21.3.remove

1 def remove(self,idx: int) - > maix.err.Err

Remove object form objects

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 err::Err remove(int idx)

# 5.21.4.at

1 def at(self,idx: int) - > Object

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 nn::Object &at(int idx)

# 5.21.5. __getitem__

1 def __getitem__(self, idx: int) - > Object

Get object item

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 nn::Object &operator[](int idx)

# 5.21.6. __len__

1 def __len__(self) - > int

Get size

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

size_t size()

5.21.7. iter

1 | def __iter__(self) - > typing.Iterator

Begin

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<Object>::iterator begin()

# 5.22. Classifier

Classifier

$\mathtt{C + + }$  defination code:

class Classifier

# 5.22.1. init

1 | def __init__(self, model: str = '', dual_buff: bool = True) - > None

Construct a new Classifier object

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: MUD model path, if empty, will not load model, you can call load() later. if not empty, will load model and will raise err:Exception if load failed. dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff. If you want to ensure every time forward output the input&#x27;s result, set this arg to false please. Default true to ensure speed.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C} + +$  definition code:

1 | Classifier(const string &model = "", bool dual_buff = true)

# 5.22.2. load

1 | def load(self, model: str) - > maix.err.Err

Load model from file, model format is .mud,\nMUD file should contain [extra] section, have key- values:\n- model_type: classifier\n- input_type: rgb or bgr\n- mean: 123.675, 116.28, 103.53\n- scale: 0.017124753831663668, 0.01750700280112045, 0.017429193899782137\n- labels: imagenet_classes.txt

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: MUD model path</td></tr><tr><td>return</td><td>error code, if load failed, return error code</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | err::Err load(const string &model)

# 5.22.3. classify

1 | def classify(self, img: maix.image.Image, softmax: bool = True, fit: maix.image.Fit = ...) - > list[tuple[int, float]]

Forward image to model, get result. Only for image input, use classify_raw for tensor input.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: image, format should match model input_type, or will raise err.Exception softmax: if true, will do softmax to result, or will return raw value fit: image resize fit mode, default Fit.FIT_COVER, see image.Fit.</td></tr><tr><td>throw</td><td>If error occurred, will raise err::Exception, you can find reason in log, mostly caused by args error or hardware error.</td></tr><tr><td>return</td><td>result, a list of (label, score). If in dual_buff mode, value can be one element list and score is zero when not ready. In C++, you need to delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<std::pair<int, float>> *classify(image::Image & img, bool softmax = true, image::Fit fit = image::FIT_COVER)

# 5.22.4. classify_raw

1 | def classify_raw(self, data: maix.tensor.Tensor, softmax: bool = True) - > list[tuple[int, float]]

Forward tensor data to model, get result

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>data: tensor data, format should match model input_type, or will raise err.Execution softmax: if true, will do softmax to result, or will return raw value</td></tr><tr><td>throw</td><td>If error occurred, will raise err::Exception, you can find reason in log, mostly caused by args error or hardware error.</td></tr><tr><td>return</td><td>result, a list of (label, score). In C++, you need to delete it after use.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::vector<std::pair<int, float>> *classify_raw(tensor::Tensor &data, bool softmax = true)

# 5.22.5. input_size

Get model input size, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>model input size</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Size input_size()

# 5.22.6.input_width

Get model input width, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of width</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

int input_width()

# 5.22.7.input_height

Get model input height, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>model input size of height</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int input_height()

# 5.22.8.input_format

1 def input_format(self) - > maix.image.Format

Get input image format, only for image input

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input image format, image::Format type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

image::Format input_format()

# 5.22.9.input_shape

1 def input_shape(self) - > list[int]

Get input shape, if have multiple input, only return first input shape

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input shape, list type</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> input_shape()

# 5.22.10. labels

Labels list

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<string> labels

# 5.22.11. label_path

Label file path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::string label_path

# 5.22.12. mean

Get mean value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> mean

# 5.22.13. scale

Get scale value, list type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<float> scale

# 5.23. MUD

MUD(model universal describe file) class

$\mathtt{C + + }$  definition code:

1 | class MUD

# 5.23.1. init

1 | def init_(self, model_path: str = '') - > None

MUD constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model_path: direction [in], model file path, model format can be MUD(model universal describe file) file.
If model_path set, will load model from file, load failed will raise err.Exception.
If model_path not set, you can load model later by load function.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | MUD(const std::string &model_path = "")

# 5.23.2. load

1 | def load(self, model_path: str) - > maix.err.Err

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model_path: direction [in], model file
path, model format can be MUD(model universal describe file) file.</td></tr><tr><td>return</td><td>error code, if load success, return
err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err load(const std::string &model_path)

# 5.23.3. type

Model type, string type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::string type

# 5.23.4. items

Model config items, different model type has different config items

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::map<std::string, std::map<std::string, std::string>> items

# 5.23.5. model_path

Model path

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 std::string model_path

# 5.23.6. parse_labels

1 def parse_labels(self, key: str = 'labels') - > list[str]

Please load() first, parse labels in items["extra"] ["labels"],\nif items["extra"]["labels"] is a file path: will parse file, every one line is a label;\nif items["extra"] ["labels"] is a string, labels split by comma(",").\nExecute this method will replace items["extra"]["labels"];

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>key: parse from items[key], default &quot;labels&quot;.</td></tr><tr><td>return</td><td>parsed labels list.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<std::string>parse_labels(const std::string key = "labels")

# 5.24. LayerInfo

NN model layer info

$\mathtt{C + + }$  defination code:

1 | class LayerInfo

# 5.24.1. init

1 | def init_(self, name: str = '', dtype: maix.tensor.DType = ..., shape: list[int] = []) - > None

LayerInfo constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>name: direction [in], layer name
dtype: direction [in], layer data type
shape: direction [in], layer shape</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | LayerInfo(const std::string &name = "", tensor::DType dtype = tensor::DType::FLOAT32,

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/49540294c466aa60fb8b35dfefab475f8a12a88a3a2407ae77b96dae93a80a87.jpg)

# 5.24.2. name

Layer name

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/3e67e082-e8c1-4a38-a4dd-4ee29d290f4d/067cde6016e91992648890f7dcbc9b3627747b8e4f58a705cd21352955326607.jpg)

# 5.24.3. dtype

Layer data type

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>attention</td><td>If model is quantized, this is the real quantized data type like int8 float16, in most scene, inputs and outputs we actually use float32 in API like forward.</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | tensor::DType dtype

# 5.24.4. shape

Layer shape

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> shape

# 5.24.5. shape_int

1 | def shape_int(self) - > int

Shape as one int type, multiply all dims of shape

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int shape_int()

# 5.24.6. to_str

1 | def to_str(self) - > str

To string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string to_str()

# 5.24.7. str

1 | def __str__(self) - > str

To string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::string __str__()

# 5.25. NN

Neural network class

$\mathtt{C + + }$  defination code:

1 class NN

# 5.25.1. init

1 def init_(self, model: str = '', dual_buff: bool = False) - > None

Neural network constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: direction [in], model file path, model format can be MUD(model universal describe file) file.
If model_path set, will load model from file, load failed will raise err.Exception.
If model_path not set, you can load model later by load function.
dual_buff: direction [in], prepare dual input output buffer to accelerate forward, that is, when NPU is forwarding we not wait and prepare the next input buff.
If you want to ensure every time forward output the input&#x27;s result, set this arg to</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>false please.
Default false to ensure easy use.</td></tr><tr><td>static</td><td>False</td></tr><tr><td colspan="2">C++ definition code:</td></tr><tr><td colspan="2">1 | NN(const std::string &amp;amp;model = &quot;&quot;, 
    bool dual_buff = false)</td></tr></table>

# 5.25.2. load

<table><tr><td>1 | def load(self, model: str) -&amp;gt; maix.err.Err</td></tr></table>

Load model from file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>model: direction [in], model file path, model format can be MUD(model universal describe file) file.</td></tr><tr><td>return</td><td>error code, if load success, return err::ERR_NONE</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | err::Err load(const std::string &model)

# 5.25.3. loaded

1 | def loaded(self) - > bool

Is model loaded

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>true if model loaded, else false</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | bool loaded()

# 5.25.4. set_dual_buff

1 | def set_dual_buff(self, enable: bool) - > None

Enable dual buff or disable dual buff

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>enable: true to enable, false to disable</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void set_dual_buff(bool enable)

# 5.25.5. inputs_info

1 | def inputs_info(self) - > list[LayerInfo]

Get model input layer info

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>input layer info</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<nn::LayerInfo> inputs_info()

# 5.25.6. outputs_info

1 | def outputs_info(self) - > list[LayerInfo]

Get model output layer info

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>output layer info</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<nn::LayerInfo> outputs_info()

# 5.25.7. extra_info

1 | def extra_info(self) - > dict[str, str]

Get model extra info define in MUD file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>extra info, dict type, key-value object, attention: key and value are all string type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::map<std::string, std::string> extra_info()

# 5.25.8. extra_info_labels

1 | def extra_info_labels(self) - > list[str]

Get model parsed extra info labels define in MUD file

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>labels list in extra info, string list type.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

std::vector<std::string> extra_info_labels()

# 5.25.9. forward

1 def forward(self, inputs: maix.tensor.Tensors, copy_result: bool = True, dual_buff_wait: bool = False) - > maix.tensor.Tensors

forward run model, get output of model\nthis is specially for MaixPy, not efficient, but easy to use in MaixPy

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>input: direction [in], input tensor
copy_result: If set true, will copy result
to a new variable; else will use a internal
memory, you can only use it until to the
next forward.
Default true to avoid problems, you can
set it to false manually to make speed
faster.
dual_buff_wait: bool type, only for</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>dual_buff mode, if true, will inference this image and wait for result, default false.</td></tr><tr><td>return</td><td>output tensor. In C++, you should manually delete tensors in return value and return value.
If dual_buff mode, it can be NULL(None in MaixPy) means not ready.</td></tr><tr><td>throw</td><td>if error occurs like no memory or arg error, will raise err.Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | tensor::Tensors *forward(tensor::Tensors &inputs, bool copy_result = true, bool dual_buff_wait = false)

# 5.25.10. forward_image

1 | def forward_image(self, img: maix.image.Image, mean: list[float] = [], scale: list[float] = [], fit: maix.image.Fit = ..., copy_result: bool = True, dual_buff_wait: bool = False, chw: bool = True) - > maix.tensor.Tensors

forward model, param is image

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>img: input image
mean: mean value, a list type, e.g. [0.485, 0.456, 0.406], default is empty list means not normalize.
scale: scale value, a list type, e.g. [1/0.229, 1/0.224, 1/0.225], default is empty list means not normalize.
fit: fit mode, if the image size of input not equal to model&#x27;s input, it will auto resize use this fit method, default is image.Fit.FIT_FILL for easy coordinate calculation, but for more accurate result, use image.Fit.FIT_CONTAIN is better.
copy_result: If set true, will copy result to a new variable; else will use a internal memory, you can only use it until to the next forward.
Default true to avoid problems, you can set it to false manually to make speed faster.
dual_buff_wait: bool type, only for dual_buff mode, if true, will inference this image and wait for result, default false.
chw:chw channel format, forward model with hwc format image input if set to false, default true(chw).</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>output tensor. In C++, you should manually delete tensors in return value and return value.
If dual_buff mode, it can be NULL(None in MaixPy) means not ready.</td></tr><tr><td>throw</td><td>If error occurs, like arg error or alloc memory failed, will raise err.Exception.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | tensor::Tensors *forward_image(image::Image &img, std::vector<float> mean = std::vector<float>(), std::vector<float> scale = std::vector<float>(), image::Fit fit = image::Fit::FIT_FILL, bool copy_result = true, bool dual_buff_wait = false, bool chw = true)