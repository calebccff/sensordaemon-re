
# MSM8996 RE

The MSM8996 is the first Qualcomm SoC with a real SLPI. Older SoCs (and some newer mid-tier ones such as MSM8953) either use the ADSP to process sensor data, or just use the AP.

## Getting messages
```
strace -p PID -f -xx -tt -s 2000 2>&1 /dev/null | grep AF_IB
```
Replace `PID` with the PID of `android.hardware.sensors@1.0-service`.
## Proximity sensor
These messages appear to contain proximity sensor data. They were captured with the screen turned off and the sensor covered then uncovered with a finger:

```
[pid  1024] 11:50:32.265624 recvfrom(97, "\x04\x66\x00\x05\x00\x1a\x00\x01\x01\x00\x29\x02\x04\x00\xcb\x72\x5b\x0b\x03\x0c\x00\x00\x00\x01\x00\x80\x76\x29\xb2\x00\x00\x00\x00", 820, MSG_DONTWAIT, {sa_family=AF_IB, sa_data="\x00\x00\x02\x00\x00\x00\x09\x00\x00\x00\x3f\x00\x00\x00\x00\x00\x00\x00"}, [20]) = 33
[pid  1024] 11:50:32.673140 recvfrom(97, "\x04\x67\x00\x05\x00\x1a\x00\x01\x01\x00\x29\x02\x04\x00\x15\xa7\x5b\x0b\x03\x0c\x00\x00\x00\x00\x00\x80\x76\x29\xb2\x00\x00\x00\x00", 820, MSG_DONTWAIT, {sa_family=AF_IB, sa_data="\x00\x00\x02\x00\x00\x00\x09\x00\x00\x00\x3f\x00\x00\x00\x00\x00\x00\x00"}, [20]) = 33
```

They contain this data (with timecodes in the beginning of each line):
```
11:50:32.265624: 04 66 00 05 00 1a 00 01 01 00 29 02 04 00 cb 72 5b 0b 03 0c 00 00 00 01 00 80 76 29 b2 00 00 00 00
11:50:32.673140: 04 67 00 05 00 1a 00 01 01 00 29 02 04 00 15 a7 5b 0b 03 0c 00 00 00 00 00 80 76 29 b2 00 00 00 00
```

This is the structure of the message roughly resembled by a C struct:
```c
struct msg {
	const u8 header;
	u8 counter;
	u8 unknown1[12];
	u32 ticks;
	u8 unknown2[5];
	u8 data;
	u8 unknown3[9];
};
```
**Description:**
+ `header`: Always `0x04`.
+ `counter`: Increases by 1 every message.
+ `ticks`: Timestamp in 32768Hz ticks, Time(s) = `ticks / 32768`
+ `data`: Sensor data. In this case, it is 1 when the proximity sensor is triggered, 0 otherwise.

**NOTE:** Some of `unknown2` and `unknown3` might be part of `data` which would make it `u32` instead of `u8`, but in this case the data is boolean so these bytes are always 0.

There should be a sensor ID somewhere here, possibly in `unknown1`.

## Accelerometer
Messages from the acclerometer are larger, probably since there is more data to carry:
```
[pid  2387] 10:17:09.676886 recvfrom(106, "\x04\x6b\x05\x22\x00\x2c\x00\x01\x01\x00\x01\x02\x0d\x00\x01\x00\x00\x00\x01\x0c\x28\x6a\x00\x00\x00\x1a\x00\x03\x11\x00\x01\xd3\x46\x02\x00\xfa\xbe\xff\xff\xbf\x5c\xf6\xff\x00\x00\x16\x00\x10\x01\x00\x00", 1684, MSG_DONTWAIT, {sa_family=AF_IB, sa_data="\x00\x00\x02\x00\x00\x00\x09\x00\x00\x00\x17\x00\x00\x00\x00\x00\x00\x00"}, [20]) = 51
```
```
04 6b 05 22 00 2c 00 01 01 00 01 02 0d 00 01 00 00 00 01 0c 28 6a 00 00 00 1a 00 03 11 00 01 d3 46 02 00 fa be ff ff bf 5c f6 ff 00 00 16 00 10 01 00 00
```
These also have the `0x04` header, a counter and a timestamp:
```c
struct msg {
	const u8 header;
	u8 counter;
	u8 unknown1[12];
	u32 ticks;
	u8 unknown2[8]
	u32 x;
	u32 z;
	u32 y;
	u8 unknown3[8];
	...
};
```
```
			Y
			|
		_________________
		|	|	|
		|	|    Z	|
		|	|   /	|
		|	|  /	|
		|	| /	|
		|	|/	|
	 X<-----|-------/--------|----->X
		|      /|	|
		|     /	|	|
		|    /	|	|
		|   /	|	|
		|  Z	|	|
		|_______|_______|
			|
			|
			Y
```