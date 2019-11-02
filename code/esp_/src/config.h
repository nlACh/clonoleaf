#ifndef CONFIG_H_
#define CONFIG_H_
#endif

/**
 * For server and IP related things:
 * Possibility to keep a static address for your ESP device. Following settings are needed.
 * Usual SSID and password need to be provided to let the thing connect to your router.
 * Also define the port of the server and the time interval for which it checks for wifi connectivity.
 * IF you don't want it to periodically connect to the local network then turn it off.
 * On losing connection the first neopixel can be set to blink red continuously.
 * AND FINALLY GIVE YOUR DEVICE A NAME! CLONOLEAF SOUNDS GOOD!
 **/
#define STATIC_IP
#ifndef STASSID
#define STASSID "give your ssid"
#define STAPSK  "give your network password"
#endif
#define HTTP_PORT 80
#define BLINK_ON_LOST
#define DEVICE_NAME "CLONOLEAF"

/**
 * Define the number of LEDs and the PIN number to which DIN is connected.
 * Use NEO_GRBW or NEO_GRB as required...
 * For the pin mappings, check references to the specific board.
 * For ESP-12S the GPIOs exposed are 15, 2, 0, 4, 5, 13, 12, 14, 16.
 **/
#define LED_TYPE NEO_GRBW
#define LEDKHZ NEO_KHZ800
#define PIN 2 // GPIO2
#define LED 24

/**
 * Color and mode stuff
 **/
#define DEFAULT_COLOR 0xFF00FFAA
#define TIMECYCLE 100000
#define NUM_MODES 12