//Disclaimer: This code was partially extended by the aid of ChatGPT.


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// PIN where NeoPixels are connected
const byte LEDPIN = 14;

// Number of NeoPixels in the strip
const byte NUMPIXELS = 30;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

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
  float fHue;

  // hue range on the color wheel in degrees (rotation in mathematic positive direction)
  fHue = randomFloat(5.0, 10.0); 
  
  // Scale hue to 0-65535 for ColorHSV
  uint16_t h_scaled = (uint16_t)(fHue * 182.04); 

  // hotter fires have more white color, decrease s value for more whites
  uint8_t s = random(250, 255);   

  // play with brightness settings to make the fire flicker
  uint8_t v = random(80, 255);   

  // Return a 32-bit color value in RGB format
  return pixels.ColorHSV(h_scaled, s, v);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void setup() {
  pixels.begin(); // Initialize the NeoPixel library
  pixels.setBrightness(255);
}

void loop() {
  // Create a fire effect by randomly changing colors and brightness
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, randomFireColor());
  }

  pixels.show();


  while(setDelay.delayTime + setDelay.lastTimeStamp < millis()){
    //wait
  }

  setDelay.lastTimeStamp = millis();
  setDelay.delayTime = random(90, 150); // Random delay between 90 and 150 milliseconds
}
