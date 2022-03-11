// Masks On Code
// By: Kahani Ploessl
// 03/07/2022


#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>


// input variables
// sound
float value;
// x rotation
float x;

// pixel # 0-9
int led;
// delay 
float d=60;

// # of on pixels
int total;

// color
int r,g,b;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  // grab input variables
  value = floor(CircuitPlayground.mic.soundPressureLevel(10)/10)-5;
  x = floor(CircuitPlayground.motionX());

  //delay slows overtime
  d+=20;

  // color determined by value
  // squared to make distinct volume levels
  // no noise means no lights
  r = 10*pow(value,2);
  g = 10*pow(value,2);
  b = 25*pow(value,2);

  if (x>3) {
    // if head is titled to the left, only pixels on right half may turn on

    // number of pixels that may be turned on
    // 0-5 because only half is active
    total = random(6);
    
    for (int b=0;b<5;b++){
      //left half set to no color
      CircuitPlayground.setPixelColor(b, 0,0,0);
    }

    for (int i=0;i<total;i++){
      // random # of pixels from positions 5-9 turn (if there is noise)
      led = random(5,10);
      CircuitPlayground.setPixelColor(led, r,g,b);
    }

    
  } else if (x<-3) {
    // if head is titled to the right, only pixels on left half may turn on

    // number of pixels that may be turned on
    // 0-5 because only half is active
    total = random(6);
    
    for (int i=0;i<total;i++){
      // random # of pixels from positions 0-4 turn on (if there is noise)
      led = random(4);
      CircuitPlayground.setPixelColor(led, r,g,b);
    }
    
    for (int b=5;b<11;b++){
      //right half set to no color
      CircuitPlayground.setPixelColor(b, 0,0,0);
    }
    
  } else {
    // if head is in netural position, all pixels may turn on

    // number of pixels that may be turned on
    // 0-10 because all is active 
    total = random(11);
    
  for (int i=0;i<total;i++){
    // random # of pixels from positions 0-9 turn on (if there is noise)
    led = random(10);
    CircuitPlayground.setPixelColor(led, r,g,b);
  }
 
  }

  // speed reset
  delay(d);
  if (d>300) {
    d=60;
  }
  
  CircuitPlayground.clearPixels();

  // debug
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" r: ");
  Serial.print(r);
  Serial.print(" g: ");
  Serial.print(g);
  Serial.print(" b: ");
  Serial.println(b);
}
