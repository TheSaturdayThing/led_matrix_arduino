
import de.voidplus.leapmotion.*;
import processing.serial.*; 

Serial port;
LeapMotion leap;
int previousPositionx = 0;
int currentPositionx = 0;

int previousPositiony = 0;
int currentPositiony = 0;

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

void draw() {
  background(255);
  
  for (Hand hand : leap.getHands()) {
    hand.draw();
    
    // 0 - 24: 25 LEDs on my NeoPixel Strip
    currentPositionx = (int) map(hand.getPosition().x, 0, 1000, 0, 8);
    //currentPositiony = (int) map(hand.getPosition().y, 0, 1000, 0, 8);
   /* 
    if (previousPositionx != currentPositionx) {
      previousPositionx = currentPositionx;
      port.write(previousPositionx);
    }*/
    //if (previousPositiony != currentPositiony) {
      //previousPositiony = currentPositiony;
      //port.write(previousPositiony);
    //}
  }
}
