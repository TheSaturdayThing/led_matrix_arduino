/*
 * Leap Motion -> Processing -> Arduino -> NeoPixel
 *
 * Michelle Leonhart 2014-01-30
 * @at0mbmxb www.tinwhiskers.net
 *
 */
 
import de.voidplus.leapmotion.*;
import processing.serial.*; 

Serial port;
LeapMotion leap;
int previousPosition = 0, previousPosition1 = 0;
int currentPosition = 0, currentPosition1 = 0;
void setup() {
  size(800, 800, P3D);
  background(255);

  leap = new LeapMotion(this);
  port = new Serial(this, Serial.list()[0], 9600);  
  /* If you want to change from port /dev/tty.usbmodem1411,
   * Use this to list out all available serial ports:
   * println(Serial.list());
   *
   * And pick the number of the one you want.
   * Like this: 
   * port = new Serial(this, Serial.list()[0], 9600);   <-- This would pick the first port from the list
   */  
}

double K(double a, double l, double r, double x, double y) {
  if (a > r) a = r;
  if (a < l) a = l;
  return x + (a - l) / (r - l) * (y - x);
}

void draw() {
  background(255);
  
  for (Hand hand : leap.getHands()) {
    hand.draw();
    
    // 0 - 24: 25 LEDs on my NeoPixel Strip
    int x = (int) K(hand.getPosition().z, 0, 100, 0, 7.999);
    int y = (int) K(hand.getPosition().x, 0, 650, 0, 7.999);
    currentPosition = x * 8 + y;
    if (hand.getPosition().y < 250) {
      currentPosition += 64;
    }
    //if (previousPosition != currentPosition || previousPosition1 != currentPosition1) {
      previousPosition = currentPosition;
      previousPosition1 = currentPosition1;
      
      port.write(previousPosition);
      //port.write(128 + z);+++++
    //}
  }
}


