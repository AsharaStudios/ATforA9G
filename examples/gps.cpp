/*
 * GPS Example using A9G's GPS pins, based on TinyGPS "test_with_gps_device.ino" example
 */

#include <Arduino.h>
#include "a9gdriver.h"
#include <TinyGPS.h>
#include <SoftwareSerial.h>

// Connect to HST pins on the A9(G)
#define A9Gtx 4
#define A9Grx 5
SoftwareSerial SerialA9G(A9Gtx,A9Grx);
A9Gdriver A9G(SerialA9G);

// Connect to GPS pins on the A9(G)
#define GPStx 6
#define GPSrx 7
SoftwareSerial SerialGPS(GPStx,GPSrx);
TinyGPS gps;

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

// MAIN LOGIC

void setup(){
    Serial.begin(115200);   //Debug (hardware) serial

    // A9G SETUP
    SerialA9G.begin(115200); // A9G Baud Rate
    while (!A9G.GPS_setStatus(1)) {
        Serial.println(F("Error while turning on GPS. Retrying..."));
        delay(2000);
    }

    // TinyGPS NMEA Decoder Setup
    SerialGPS.listen();
    Serial.print(F("Testing TinyGPS library v. ")); Serial.println(TinyGPS::library_version());
    Serial.println(F("by Mikal Hart"));
    Serial.println();
    Serial.println(F("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
    Serial.println(F("          (deg)     (deg)      Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
    Serial.println(F("-------------------------------------------------------------------------------------------------------------------------------------"));
    SerialGPS.begin(9600);  // A9G's Internal GPS Baud Rate
}

void loop(){
    float flat, flon;
    unsigned long age, chars = 0;
    unsigned short sentences = 0, failed = 0;
    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

    print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
    print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
    gps.f_get_position(&flat, &flon, &age);
    print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
    print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
    print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
    print_date(gps);
    print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);
    print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
    print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2);
    print_str(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(gps.f_course()), 6);
    print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0xFFFFFFFF : (unsigned long)TinyGPS::distance_between(flat, flon, LONDON_LAT, LONDON_LON) / 1000, 0xFFFFFFFF, 9);
    print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? TinyGPS::GPS_INVALID_F_ANGLE : TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
    print_str(flat == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(TinyGPS::course_to(flat, flon, LONDON_LAT, LONDON_LON)), 6);

    gps.stats(&chars, &sentences, &failed);
    print_int(chars, 0xFFFFFFFF, 6);
    print_int(sentences, 0xFFFFFFFF, 10);
    print_int(failed, 0xFFFFFFFF, 9);
    Serial.println();

    smartdelay(1000);
}

// UTILITARY FUNCTIONS

static void smartdelay(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (SerialGPS.available())
            gps.encode(SerialGPS.read());
    } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec)
{
    if (val == invalid)
    {
        while (len-- > 1)
            Serial.print('*');
        Serial.print(' ');
    }
    else
    {
        Serial.print(val, prec);
        int vi = abs((int)val);
        int flen = prec + (val < 0.0 ? 2 : 1); // . and -
        flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
        for (int i=flen; i<len; ++i)
            Serial.print(' ');
    }
    smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
    char sz[32];
    if (val == invalid)
        strcpy(sz, "*******");
    else
        sprintf(sz, "%ld", val);
    sz[len] = 0;
    for (int i=strlen(sz); i<len; ++i)
        sz[i] = ' ';
    if (len > 0)
        sz[len-1] = ' ';
    Serial.print(sz);
    smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age;
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age == TinyGPS::GPS_INVALID_AGE)
        Serial.print("********** ******** ");
    else
    {
        char sz[32];
        sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
            month, day, year, hour, minute, second);
        Serial.print(sz);
    }
    print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
    smartdelay(0);
}

static void print_str(const char *str, int len)
{
    int slen = strlen(str);
    for (int i=0; i<len; ++i)
        Serial.print(i<slen ? str[i] : ' ');
    smartdelay(0);
}
