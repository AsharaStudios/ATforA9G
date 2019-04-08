# A9G Driver Library

[![Build Status](https://travis-ci.com/AsharaStudios/ATforA9G.svg?branch=master)](https://travis-ci.com/AsharaStudios/ATforA9G)

Library to drive a Serial connected to an A9G Module. Based on the [GPRS Wiki (chinese)](https://wiki.ai-thinker.com/gprs) mentioned in the [official english documentation](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en/).

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
