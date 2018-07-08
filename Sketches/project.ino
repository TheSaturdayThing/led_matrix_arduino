
#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, 13, NEO_RGB + NEO_KHZ800);


int currentPosition;
int serialInput;
int MODE;
int x[8], y[8];
int dtime;
int T;
int tx[4] = {0, 0, 1, -1}, ty[4] = {1, -1, 0, 0};
int xx[100], yy[100], len, predir = 2, XX, YY, c1[100], c2[100], c3[100];
bool live;
int tarx, tary;

void SetColor(int x, int y, int a, int b, int c) {
  strip.setPixelColor(x * 8 + y, strip.Color(a,b,c));
  strip.show();
}

void setup() {
  strip.begin();
  for (int i = 0; i < 8; i++)
  for (int j = 0; j < 8; j++)
  SetColor(i, j, 0, 0, 0);
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600); // Listen for inp
  START0();
}


void START0() {
  for (int i = 0; i <= 10; i++)
  xx[i] = yy[i] = 1000;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      SetColor(i, j, 0, 0, 0);
  T = 0;
}

void START1() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      SetColor(i, j, 0, 0, 0);
  for (int i = 0; i < 8; i++)
    x[i] = y[i] = -1;
}

void START2() {
  live = true;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
        if (abs(i - x[7]) >= 3 && abs(j - y[7]) >= 3)
          tarx = i, tary = j;
    }
  SetColor(tarx, tary, 255, 0, 0);
}

void switch_MODE() {
  if (MODE == 0) {
    if (Serial.available()) {
      MODE = 1;
      START1();
    }
  }else if (MODE == 1) {
    if (Serial.available() && Serial.read() >= 64) {
      MODE = 2;
    START2();
    }
  }else if (MODE == 2){
      if (dtime >= 6000 || !live) {
        MODE = 0;
      START0();
    }
  }
  
}

void loop() {
  switch_MODE();
  if (MODE == 0) {
    for (int i = 10; i; i--)
    xx[i] = xx[i - 1], yy[i] = yy[i - 1], c1[i] = c1[i - 1], c2[i] = c2[i - 1], c3[i] = c3[i - 1];
  if (T % 5 == 1) {
    xx[0] = random(0, 7);
    yy[0] = random(0, 7);
    c1[0] = random(0, 255);
    c2[0] = random(0, 255);
    c3[0] = random(0, 255);
    
   }else xx[0] = yy[0] = 1000;
   for (int i = 0; i < 8; i++)
   for (int j = 0; j < 8; j++) {
    int ok = -1;
    for (int p = 0; p <= 10; p++)
    if (abs(i-xx[p]) + abs(j-yy[p])==p) ok = p;
    if (ok >= 0)
      SetColor(i, j, c1[ok], c2[ok], c3[ok]);
    else
      SetColor(i, j, 0, 0, 0);
   }
  }else if (MODE == 1) {
    for (int i = 0; i < 8; i++)
      SetColor(x[i], y[i], 0, 0, 0);
    
      for (int i = 0; i < 7; i++)
        x[i] = x[i + 1], y[i] = y[i + 1];
     int tot = 0, X = 0, Y = 0;
    while (Serial.available()) {
        dtime = 0;
        serialInput = Serial.read();
        X += serialInput % 64 / 8;
        Y += serialInput % 64 % 8;
        tot += 1;
      }
      if (!tot)
        x[7] = y[7] = -1;
      else
        x[7] = int(1.0 * X / tot), y[7] = int(1.0 * Y / tot);
    for (int i = 0; i < 8; i++)
      SetColor(x[i], y[i], 256 / 8 * (i + 1) - 1, 256 / 8 * (i + 1) - 1, 256 / 8 * (i + 1) - 1);
  }else {
    for (int i = 0; i < 8; i++)
      SetColor(x[i], y[i], 0, 0, 0);
    
      for (int i = 0; i < 7; i++)
        x[i] = x[i + 1], y[i] = y[i + 1];
     int tot = 0, X = 0, Y = 0;
    while (Serial.available()) {
        dtime = 0;
        serialInput = Serial.read();
        X += serialInput % 64 / 8;
        Y += serialInput % 64 % 8;
        tot += 1;
      }
      if (!tot)
        x[7] = y[7] = -1;
      else
        x[7] = int(1.0 * X / tot), y[7] = int(1.0 * Y / tot);
    for (int i = 0; i < 7; i++)
      SetColor(x[i], y[i], 32 / 8 * (i + 1) - 1, 32 / 8 * (i + 1) - 1, 32 / 8 * (i + 1) - 1);
    SetColor(x[7], y[7], 255, 255, 255);
    if (x[7] == tarx && y[7] == tary) {live = false; return;}
    int mi = 10000, px, py;
    for (int i = tarx - 1; i <= tarx + 1; i++)
    for (int j = tary - 1; j <= tary + 1; j++) {
      if (0 <= i && i < 8 && 0 <= j && j < 8) {
        if ((i - x[6]) * (i - x[6]) + (j - y[6]) * (j - y[6]) < mi) {
           mi = (i - x[6]) * (i - x[6]) + (j - y[6]) * (j - y[6]);
           px = i;
           py = j;
        }
      }
      }
      if (T % 10 == 0) {
      SetColor(tarx, tary, 0, 0, 0);
      SetColor(px, py, 255, 0, 0);
      
      tarx = px;
      tary = py;}
    }
  T += 1;
  dtime += 100;
  delay(100);
}

