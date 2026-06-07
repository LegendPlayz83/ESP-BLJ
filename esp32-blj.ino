#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SPIClass hspi(HSPI);
SPIClass vspi(VSPI);

RF24 radio1(16, 15);
RF24 radio2(22, 21);

#define BUTTON_PIN 27

int mode = 0;
bool lastButton = HIGH;

int hits[125];

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Wire.begin(4, 5);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  hspi.begin(14, 12, 13, 15);
  vspi.begin(18,19, 23, 21);

  radio1.begin(&hspi);
  radio2.begin(&vspi);

  radio1.setAutoAck(false);
  radio2.setAutoAck(false);

  radio1.setPALevel(RF24_PA_MAX);
  radio2.setPALevel(RF24_PA_MAX);

}

void fastScan(){
  for (int ch = 0; ch < 125; ch++){
    radio1.setChannel(ch);
    radio2.setChannel(ch);

    delayMicroseconds(80);

    if (radio1.testCarrier()) hits[ch]++;
    if (radio2.testCarrier()) hits[ch]++;
  }
}

void deepScan() {
  for (int ch = 0; ch < 125; ch++) {
    radio1.setChannel(ch);
    radio2.setChannel(ch);

    for (int i = 0; i < 5; i++){
      delayMicroseconds(150);

      if (radio1.testCarrier()) hits[ch]++;
      if (radio2.testCarrier()) hits[ch]++;

    }
  }
}

void peakScan(){
  int strongest = 0;
  int strongestCh = 0;

for (int ch = 0; ch < 125; ch++){
  radio1.setChannel(ch);
  radio2.setChannel(ch);

  delayMicroseconds(100);

  int level = 0;

  if (radio1.testCarrier()) level++;
  if (radio2.testCarrier()) level++;

  if (level > strongest) {
    strongest = level;
    strongestCh = ch;
  }
}

hits[strongestCh] = strongest * 5;
}
/// 100 lines done :p

void drawDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);

  if (mode == 0) display.println("FAST SCAN");
  if (mode == 1) display.println("DEEP SCAN");
  if (mode == 2) display.println("PEAK MODE");

  int maxVal = 1;

  for (int i = 0; i < 125; i++) {
    if (hits[i] > maxVal) maxVal = hits[i];
  }

  for (int x = 0; x < 128; x++) {
    int ch = map(x, 0, 127, 0, 124);

    int h = map(hits[ch], 0, maxVal, 0, 20);

    display.drawLine(x, 31, x, 31 - h,WHITE);
  }

  display.display();
}

void loop() {
  bool current = digitalRead(BUTTON_PIN);

  if (lastButton == HIGH && current == LOW) {
    mode++;


    if (mode > 2) mode = 0;

    memset(hits, 0, sizeof(hits));

    delay(250);
  }

  lastButton = current;

  memset(hits, 0,sizeof(hits));

  if (mode == 0) fastScan();
  if (mode == 1) deepScan();
  if (mode == 2) peakScan();

  drawDisplay();
}

/// Thats all!!!!!