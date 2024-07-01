#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// PIN where NeoPixels are connected
const uint8_t LEDPIN_1 = 3;
const uint8_t LEDPIN_2 = 4;
const uint8_t LEDPIN_3 = 5;
const uint8_t LEDPIN_4 = 6;
const uint8_t LEDPIN_5 = 7;

// Number of NeoPixels in the strip
const uint8_t NUMPIXELS = 30;

Adafruit_NeoPixel ring1 = Adafruit_NeoPixel(22, LEDPIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring2 = Adafruit_NeoPixel(16, LEDPIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring3 = Adafruit_NeoPixel(20, LEDPIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring4 = Adafruit_NeoPixel(24, LEDPIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring5 = Adafruit_NeoPixel(28, LEDPIN_5, NEO_GRB + NEO_KHZ800);

const uint8_t brightness = 200;

/**
 * @brief A structure to hold delay related information.
 * 
 * This struct is used to manage delay operations in the program. It contains two fields:
 * - lastTimeStamp: A 32-bit unsigned integer to store the timestamp of the last delay operation.
 * - delayTime: A 16-bit unsigned integer to store the delay time in milliseconds.
 */
struct delayObject {
  uint32_t lastTimeStamp = 0;  ///< Timestamp of the last delay operation.
  uint16_t delayTime = 0;     ///< Delay time in milliseconds.
};

delayObject setDelay;


// Function to generate a random floating-point number between min and max
/**
 * @brief Function to generate a random floating-point number between min and max
 * 
 * This function uses the rand() function from the C++ standard library to generate a random 
 * floating-point number between the specified minimum and maximum values.
 * 
 * @param min The minimum value for the random number
 * @param max The maximum value for the random number
 * 
 * @return float A random floating-point number between min and max
 */
float randomFloat(float min, float max) {
  return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Function to generate a random color in the range of fire colors using HSV
/**
 * @brief Function to generate a random color in the range of fire colors using HSV
 * 
 * @return uint32_t A 32-bit color value in RGB format
 */
uint32_t randomFireColor() {

  Adafruit_NeoPixel temp;

  float fHue;

  // hue range on the color wheel in degrees (rotation in mathematic positive direction)
  fHue = randomFloat(5.0, 10.0); 
  
  // Scale hue to 0-65535 for ColorHSV
  uint16_t h_scaled = (uint16_t)(fHue * 182.04); 

  // hotter fires have more white color, decrease s value for more whites
  uint8_t s = random(250, 255);   

  // play with brightness settings to make the fire flicker
  uint8_t v = random(50, 255);   

  // Return a 32-bit color value in RGB format
  return temp.ColorHSV(h_scaled, s, v);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void setup() {
  ring1.begin(); // Initialize the NeoPixel library
  ring2.begin();
  ring3.begin();
  ring4.begin();
  ring5.begin();

  ring1.setBrightness(brightness);
  ring2.setBrightness(brightness);
  ring3.setBrightness(brightness);
  ring4.setBrightness(brightness);
  ring5.setBrightness(brightness);

  ring1.clear();
  ring2.clear();
  ring3.clear();
  ring4.clear();
  ring5.clear();

  ring1.show();
  ring2.show();
  ring3.show();
  ring4.show();
  ring5.show();
}

void loop() {

  // Non-blocking delay mechanism
  if (millis() - setDelay.lastTimeStamp > setDelay.delayTime) {
    setDelay.lastTimeStamp = millis();
    setDelay.delayTime = random(100, 200); // Random delay between 90 and 150 milliseconds



      // Create a fire effect by randomly changing colors and brightness
    for (int i = 0; i < NUMPIXELS; i++) {
      ring1.setPixelColor(i, randomFireColor());
      ring2.setPixelColor(i, randomFireColor());
      ring3.setPixelColor(i, randomFireColor());
      ring4.setPixelColor(i, randomFireColor());
      ring5.setPixelColor(i, randomFireColor());
    }

    ring1.show();
    ring2.show();
    ring3.show();
    ring4.show();
    ring5.show();
  }
}
