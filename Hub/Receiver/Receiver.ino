#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <ErriezTM1637.h>

// Prepare radio
RF24 NRF24L01 (7, 8);
const byte address[6] = "00001";

// Prepare display
#define TM1637_CLK_PIN   2
#define TM1637_DIO_PIN   3

// Create tm1637 object
TM1637 display(TM1637_CLK_PIN, TM1637_DIO_PIN);

uint8_t digits[] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111,
};

void setup() {
  Serial.begin(9600);
  NRF24L01.begin();
  NRF24L01.openReadingPipe(1, address);
  NRF24L01.setAutoAck(1);
  NRF24L01.startListening();
  pinMode(5, OUTPUT);
  
  if (NRF24L01.isChipConnected()) {
    Serial.println("NRF24L01 connected");
  } else {
    Serial.println("NFR24L01 MISSING ! NOTHING WILL BE EMITTED !");
    displayNumber(4444);
    delay(30000);
  }

  display.begin();
  display.setBrightness(2);
  beep(8888);
  beep(8888);
  beep(8888);
}

void loop() {
  if (NRF24L01.available()) {
    uint8_t detectorNumber = 0;
    NRF24L01.read(&detectorNumber, sizeof(detectorNumber));
    beep(detectorNumber);
  }
}

void beep(int number) {
  digitalWrite(5, HIGH);
  displayNumber(number);
  delay(200);
  digitalWrite(5, LOW);
  display.clear();
}

void displayNumber(int number) {
  uint8_t buf[] = {0, 0, 0, 0};

  buf[3] = digits[number % 10];

  if (number > 9) {
    buf[2] = digits[(number % 100) / 10];
  }

  if (number > 99) {
    buf[1] = digits[(number % 1000) / 100];
  }

  if (number > 999) {
    buf[0] = digits[(number % 10000) / 1000];
  }
  display.writeData(0, buf, sizeof(buf));
}
