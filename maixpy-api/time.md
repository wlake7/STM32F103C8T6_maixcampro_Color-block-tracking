# maix.time

maix.time module

You can use maix.time to access this module with MaixPyThis module is generated from MaixPy and MaixCDK

# 1. Module

No module

2. Enum

3. Variable

4. Function

# 4.1. time

1 def time() - > float

Get current time in s

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in s, double type</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>attention</td><td>If board have no RTC battery, when bootup and connect to network, system will automatically sync time by NTP, will cause time() have big change, e.g. before NTP: 10(s), after: 1718590639.5149617(s). If you want to calculate time interval, please use ticks_s().</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/95809d3ec6ea3c5ef9704f63527d90bac753e73a849059415b15f06e44b5a3f3.jpg)

# 4.2. time_ms

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/dd7cbedcd1de68b92605bf313aaf4d4c851cb4a572afec4cd21c2eb7b4f1d278.jpg)

Get current time in ms

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in ms, uint64_t type</td></tr><tr><td>attention</td><td>If board have no RTC battery, when bootup and connect to network, system will automatically sync time by NTP, will cause time() have big change, e.g. before NTP: 10000(ms), after: 1718590639000(ms)</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>If you want to calculate time interval, 
please use ticks_ms().</td></tr></table>

$\mathtt{C + + }$  definition code:

uint64_t time_ms()

# 4.3. time_s

1 def time_s() - > int

Get current time in s

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in s, uint64_t type</td></tr><tr><td>attention</td><td>If board have no RTC battery, when bootup and connect to network, system will automatically sync time by NTP, will cause time() have big change, e.g. before NTP: 10(s), after: 1718590639(s)</td></tr></table>

$\mathtt{C + + }$  definition code:

uint64_t time_s()

# 4.4. time_us

1 def time_us() - > int

Get current time in us

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in us, uint64_t type</td></tr><tr><td>attention</td><td>If board have no RTC battery, when bootup and connect to network, system will automatically sync time by NTP, will cause time() have big change, e.g. before NTP: 100000000(us), after: 1718590639000000(s) If you want to calculate time interval, please use ticks_us().</td></tr></table>

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/5542f0ebba65fbe8f3dca37673b6531e1e487e6b32e1fdd1607e396a9af1d428.jpg)

# 4.5. time_diff

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/90f4a5a416afbdbc856f24d088838245a1ac7c80b9923b37a9d0a205549a8218.jpg)

Calculate time difference in s.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>last: last time
now: current time, can be -1 if use current time</td></tr><tr><td>return</td><td>time difference</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>attention</td><td>If board have no RTC battery, when bootup and connect to network, system will automatically sync time by NTP, will cause time() have big change, and lead to big value. e.g. before NTP: 1(s), after: 1718590500(s) If you want to calculate time interval, please use ticks_diff().</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | double time_diff(double last, double now = - 1)

# 4.6. ticks_s

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/78ef8aaabd0635ac1e033df75e3c4898afe00f24a5d1f9e510786a555b001416.jpg)

Get current time in s since bootup

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in s, double type</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | double ticks_s()

# 4.7. ticks_ms

1 | def ticks_ms() - > int

Get current time in ms since bootup

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in ms, uint64_t type</td></tr></table>

$\zeta + +$  definition code:

1 | uint64_t ticks_ms()

# 4.8. ticks_us

1 | def ticks_us() - > int

Get current time in us since bootup

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current time in us, uint64_t type</td></tr></table>

$\zeta + +$  definition code:

1 | uint64_t ticks_us()

# 4.9. ticks_diff

1 | def ticks_diff(last: float, now: float = - 1) - > float

Calculate time difference in s.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>last: last time
now: current time, can be -1 if use current time</td></tr><tr><td>return</td><td>time difference</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | double ticks_diff(double last, double now = - 1)

# 4.10. sleep

Sleep seconds

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>s: seconds, double type</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void sleep(double s)

# 4.11. sleep_ms

Sleep milliseconds

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>ms: milliseconds, uint64_t type</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | void sleep_ms(uint64_t ms)

# 4.12. sleep_us

Sleep microseconds

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>us: microseconds, uint64_t type</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void sleep_us(uint64_t us)

# 4.13. fps

1 def fps() - > float

Calculate FPS since last call this method.\nAttention, this method is not multi thread safe, only call this method in one threads.\nIf you want to use in multi threads, please use time.FPS class.\nFPS is average value of recent n(buff_len) times, and you can call fps_set_buff_len(10) to change buffer length, default is 20. \nMultiple invoke this function will calculate fps between two invoke, and you can also call fps_start() first to manually assign fps calculate start point.

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>float type, current fps since last call this method</td></tr></table>

$\mathtt{C + + }$  defination code:

# 4.14. fps_start

Manually set fps calculation start point, then you can call fps() function to calculate fps between fps_start() and fps().

$\mathtt{C + + }$  defination code:

void fps_start()

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/018ec9b622c9c200ed7396ffc879fee1e61dbad91a3e1181f84318d6a4762fe9.jpg)

# 4.15. fps_set_buff_len

1 def fps_set_buff_len(len: int) - > None

Set fps method buffer length, by default the buffer length is 10.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>len: Buffer length to store recent fps value.</td></tr></table>

$\mathtt{C + + }$  defination code:

void fps_set_buff_len(int len)

# 4.16. now

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/aadf2a37d9ac2ac430fdf856b6bbe3175f01d56c21f25818241ea3420594bfd5.jpg)

Get current UTC date and time

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>current date and time, DateTime type</td></tr></table>

$\zeta + +$  definition code:

1 | time::DateTime *now()

# 4.17. localtime

1 | def localtime() - > DateTime

Get local time

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>local time, DateTime type</td></tr></table>

$\zeta + +$  definition code:

1 | time::DateTime *localtime()

# 4.18. strptime

1 | def strptime(str: str, format: str) - > DateTime

DateTime from string

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>str: date time string
format: date time format</td></tr><tr><td>return</td><td>DateTime</td></tr></table>

$\mathtt{C + + }$  defination code:

time::DateTime *strptime(const std::string &str, const std::string &format)

# 4.19. gmtime

1 def gmtime(timestamp: float) - > DateTime

timestamp to DateTime(time zone is UTC (value 0))

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>timestamp: double timestamp</td></tr><tr><td>return</td><td>DateTime</td></tr></table>

$\mathtt{C + + }$  defination code:

time::DateTime *gmtime(double timestamp)

# 4.20. timezone

1 def timezone(timezone: str = '') - > str

Set or get timezone

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>timezone: string type, can be empty and default to empty, if empty, only return current timezone, a &quot;region/city&quot; string, e.g. Asia/Shanghai, Etc/UTC, you can get all by list_timezones function.</td></tr><tr><td>return</td><td>string type, return current timezone setting.</td></tr><tr><td>attention</td><td>when set new timezone, time setting not take effect in this process for some API, so you need to restart program.</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::string timezone(const std::string &timezone = "")

# 4.21. timezone2

1 | def timezone2(region: str = '', city: str = '') - > list[str]

Set or get timezone

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>region: string type, which region to set, can be empty means only get</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>current, default empty.
city: string type, which city to set, can be empty means only get current, default empty.</td></tr><tr><td>return</td><td>list type, return current timezone setting, first is region, second is city.</td></tr><tr><td>attention</td><td>when set new timezone, time setting not take effect in this process for some API, so you need to restart program.</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<std::string> timezone2(const std::string &region = "", const std::string &city = "")

# 4.22. list timezones

1 | def list_timezones() - > dict[str, list[str]]

List all timezone info

<table><tr><td>item</td><td>description</td></tr><tr><td>return</td><td>A dict with key are regions, and value are region&#x27;s cities.</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::map<std::string, std::vector<std::string>> list_timezones()

# 4.23. ntp_timetuple

1 def ntp_timetuple(host: str, port: int = - 1, retry: int = 3, timeout_ms: int = 0) - > list[int]

Retrieves time from an NTP server\nThis function fetches the current time from the specified NTP server and port,\nreturning a tuple containing the time details.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>host: The hostname or IP address of the NTP server.
port: The port number of the NTP server. Use -1 for the default port 123.
retry: The number of retry attempts. Must be at least 1.
timeout_ms: The timeout duration in milliseconds. Must be non-negative.</td></tr><tr><td>return</td><td>A list of 6 elements: [year, month, day, hour, minute, second]</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int> ntp_timetuple(std::string host, int port=- 1, uint8_t retry=3, int

# 4.24. ntp_timetuple_with_config

1 | def ntp_timetuple_with_config(path: str) - > list[int]

Retrieves time from an NTP server using a configuration file\nThis function reads the configuration from a YAML file to fetch the current time\nfrom a list of specified NTP servers, returning a tuple containing the time details.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>path: The path to the YAML
configuration file, which should include:
- Config:
- retry: Number of retry attempts (must be at least 1)
- total_timeout_ms: Total timeout
duration in milliseconds (must be non-negative)
- NtpServers:
- host: Hostname or IP address of the NTP server
- port: Port number of the NTP server (use 123 for default)
Example YAML configuration:
Config:
- retry: 3
- total_timeout_ms: 10000
NtpServers:</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>- host: &quot;pool.ntp.org&quot;
port: 123
- host: &quot;time.nist.gov&quot;
port: 123
- host: &quot;time.windows.com&quot;
port: 123</td></tr><tr><td>return</td><td>A list of 6 elements: [year, month, day, hour, minute, second]</td></tr></table>

$\mathtt{C + + }$  definition code:

1 | std::vector<int>  ntp_timeout_t with_config(std::string path)

# 4.25. ntp_sync_sys_time

1 | def ntp_sync_sys_time(host: str, port: int = - 1, retry: int = 3, timeout_ms: int = 0) - > list[int]

Retrieves time from an NTP server and synchronizes the system time\nThis function fetches the current time from the specified NTP server and port,\nthen synchronizes the system time with the retrieved time.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>host: The hostname or IP address of the NTP server.
port: The port number of the NTP server.
Use 123 for the default port.</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>retry: The number of retry attempts.
Must be at least 1.
timeout_ms: The timeout duration in milliseconds. Must be non-negative.</td></tr><tr><td>return</td><td>A list of 6 elements: [year, month, day, hour, minute, second]</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int>  ntp_sync_sys_time(std::string host,  int port=- 1, uint8_t retry=3, int timeout_ms=0)

# 4.26.  ntp_sync_sys_time_with_config

1 | def ntp_sync_sys_time_with_config(path: str) - > list[int]

Retrieves time from an NTP server using a configuration file and synchronizes the system time\nThis function reads the configuration from a YAML file to fetch the current time\nfrom a list of specified NTP servers, then synchronizes the system time with the retrieved time.

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>path: The path to the YAML configuration file, which should include: - Config</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>- retry: Number of retry attempts (must be at least 1)
- total_timeout_ms: Total timeout duration in milliseconds (must be non-negative)
- NtpServers:
- host: Hostname or IP address of the NTP server
- port: Port number of the NTP server (use 123 for default)
Example YAML configuration:
Config:
- retry: 3
- total_timeout_ms: 10000
NtpServers:
- host: &quot;pool.ntp.org&quot;
port: 123
- host: &quot;time.nist.gov&quot;
port: 123
- host: &quot;time.windows.com&quot;
port: 123</td></tr><tr><td>return</td><td>A vector of integers containing the time details: (year, month, day, hour, minute, second)</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::vector<int>  ntp_sync_sys_time_with_config(std::stripath)

# 5. Class

# 5.1. FPS

FPS class to use average filter to calculate FPS.

$\mathtt{C + + }$  defination code:

1 class FPS

# 5.1.1. init

1 | def init_(self, buff_len: int = 20) - > None

FPS class constructor

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>param</td><td>buff_len: Average buffer length, default 20, that is, fps() function will return the average fps in recent buff_len times fps.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 FPS(int buff_len = 20)

# 5.1.2. start

1 def start(self) - > None

Manually set fps calculation start point, then you can call fps() function to calculate fps between start() and fps().

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void start()

# 5.1.3. fps

<table><tr><td>1 | def fps(self) -&amp;gt; float</td></tr></table>

The same as end function.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>float type, current fps since last call this method</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | float fps()

# 5.1.4. end

1 | def end(self) - > float

Calculate FPS since last call this method.\nFPS is average value of recent n(buff_len) times, and you can call fps_set_buff_len(10) to change buffer length, default is 20. \nMultiple invoke this function will calculate fps between two invoke, and you can also call fps_start() first to manually assign fps calculate start point.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>float type, current fps since last call this method</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | float end()

# 5.1.5. set_buff_len

1 | def set_buff_len(self, len: int) - > None

Set fps method buffer length, by default the buffer length is 10.

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>param</td><td>len: Buffer length to store recent fps
value.</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | void set_buff_len(int len)

# 5.2. DateTime

Date and time class

$\mathtt{C + + }$  defination code:

1 | class DateTime

# 5.2.1. year

Year

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | int year

# 5.2.2. month

Month, 1~12

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int month

# 5.2.3. day

Day

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int day

# 5.2.4. hour

Hour

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int hour

# 5.2.5. minute

Minute

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 int minute

# 5.2.6. second

Second

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int second

# 5.2.7. microsecond

Microsecond

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

1 int microsecond

# 5.2.8. yearday

Year day

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  definition code:

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/b823c6c7164c5d950efc7edf1479ad20a9d9d64bd236e583f227173db45d3492.jpg)

# 5.2.9. weekday

Weekday, 0 is Monday, 6 is Sunday

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

![](https://cdn-mineru.openxlab.org.cn/extract/31233e36-8048-488b-8654-f5f5d0aab38e/26a057b21d0b0a1f710d80ac564ada23d8b004eb2a4ba15df2ecf8ce0fc0752e.jpg)

# 5.2.10. zone

Time zone

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | float zone

# 5.2.11. zone_name

Time zone name

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>var</td></tr><tr><td>static</td><td>False</td></tr><tr><td>readonly</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::string zone_name

# 5.2.12. init

1 def init_(self, year: int = 0, month: int = 0, day: int = 0, hour: int = 0, minute: int = 0, second: int = 0, microsecond: int = 0, yearday: int = 0, weekday: int = 0, zone: int = 0) - > None

# Constructor

https://wiki.sipeed.com/maixpy/api/maix/time.html  

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td rowspan="8">param</td><td>year: year</td></tr><tr><td>month: month</td></tr><tr><td>day: day</td></tr><tr><td>hour: hour</td></tr><tr><td>minute: minute</td></tr><tr><td>second: second</td></tr><tr><td>microsecond: microsecond</td></tr><tr><td>yearday: year day</td></tr></table>

<table><tr><td>item</td><td>description</td></tr><tr><td></td><td>weekday: weekday
zone: time zone</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | DateTime(int year = 0, int month = 0, int day = 0, int hour = 0, int minute = 0, int second = 0, int microsecond = 0, int yearday = 0, int weekday = 0, int zone = 0)

# 5.2.13. strftime

1 | def strftime(self, format: str) - > str

Convert to string

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>date time string</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | std::string strftime(const std::string &format)

# 5.2.14. timestamp

1 | def timestamp(self) - > float

Convert to float timestamp

<table><tr><td>item</td><td>description</td></tr><tr><td>type</td><td>func</td></tr><tr><td>return</td><td>float timestamp</td></tr><tr><td>static</td><td>False</td></tr></table>

$\mathtt{C + + }$  defination code:

1 | double timestamp()