# A9G Driver Library

[![Build Status](https://travis-ci.com/AsharaStudios/ATforA9G.svg?branch=master)](https://travis-ci.com/AsharaStudios/ATforA9G)

Library to drive a Serial connected to an A9G Module. Based on the [GPRS Wiki (chinese)](https://wiki.ai-thinker.com/gprs) mentioned in the [official english documentation](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en/). And from there, based on the AT [Usage Examples (chinese)](https://wiki.ai-thinker.com/gprs/examples), [English Instruction Set (pdf)](https://wiki.ai-thinker.com/_media/gprs/b000at00a0_gprs_series_module_at_instruction_set_v1.0.pdf) and [Chinese Instruction Set (pdf)](https://wiki.ai-thinker.com/_media/gprs/at%E6%8C%87%E4%BB%A4%E9%9B%8620180825.pdf)

## Usage

### Linking the library in your PlatformIO project

If you are using [PlatformIO](https://platformio.org), you can copy the URL of this repo, and paste it in the `lib_deps` section of your platformio.ini

```ini
...
lib_deps =
  ...
  https://github.com/AsharaStudios/ATforA9G.git
```

Doing as above, PlatformIO will download for you, the library in a folder inside .piolibdeps folder. You can also download one of the [released versions](https://github.com/AsharaStudios/ATforA9G/releases) and extract it into your lib folder of your PlatformIO project. For the first method, you can also specify an specific version by just adding `#v0.0.0` (or whatever version you want) at the end of the URL.

### Including it in your code

Simply `#include "a9gdriver.h"` at the beginning of the .cpp / .ino files you want to use the library. In the a9gdriver.h are more documentation about every function.

```c++
#include "a9gdriver.h"
#include <Arduino.h>
#include <SoftwareSerial.h> // Unless your device have more than one Serial (Serial1, Serial2, ...)

// Update according your current connection
#define A9Gtx 3
#define A9Grx 4

SoftwareSerial A9Gserial(A9Gtx,A9Grx);
A9Gdriver A9G(A9Gserial); // Pass the Serial connected to the A9G, to the A9G Driver

void setup(){
  ...
  A9Gserial.begin(9600);
}

```

## To keep in mind

Currently there is no echo handling of AT commands, so the echoes are being disabled because the library disable it by sending `ATE0`. This means that after using this library, you want to test your A9(G) back on terminal, you will see that as you type the AT commands you will **not** see what you have typed: you will only see the AT corresponding replies (yes, press "Intro", it will work even if you no saw what you typed), *unless* you enable the echoes back by sending `ATE1`.
