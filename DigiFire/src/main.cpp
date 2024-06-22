#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Pin where NeoPixels are connected
#define PIN 14

// Number of NeoPixels in the strip
#define NUMPIXELS 30

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Function to generate a random floating-point number between min and max
float randomFloat(float min, float max) {
  return min + ((float)rand() / RAND_MAX) * (max - min);
}

// Function to generate a random color in the range of fire colors using HSV
uint32_t randomFireColor() {
  float h;
 
    // 10% chance to get a bit of green
    h = randomFloat(5.0, 10.0); // Hue range for yellow-green
  
  uint16_t h_scaled = (uint16_t)(h * 182.04); // Scale hue to 0-65535 for ColorHSV
  uint8_t s = random(250, 255);   // High saturation for vibrant colors
  uint8_t v = random(80, 255);   // High value for bright colors
  return pixels.ColorHSV(h_scaled, s, v);
}

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
  
  delay(random(90, 150)); // Longer delay to slow down the flicker effect
}
