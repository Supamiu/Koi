#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <avr/sleep.h>

int Jack = 2;
int DEBOUNCE_UP_THRESHOLD = 1000;
int DEBOUNCE_DOWN_THRESHOLD = 5000;

unsigned long previousLoop = 0;

RF24 NRF24L01 (7, 8);
const byte address[6] = "00001";
uint8_t detectorNumber = 1;

int debounceUp = 0;
int debounceDown = 0;

void sendSignal() {
  Serial.println("BIP");
  bool result = NRF24L01.write(&detectorNumber, sizeof(detectorNumber));
  delay(100);
}

void wakeUp() {
}

void sleep() {
  Serial.println("Sleep time");
  debounceUp = 0;
  debounceDown = 0;
  NRF24L01.powerDown();
  delay(1000);
  sleep_enable();
  attachInterrupt(0, wakeUp, RISING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  // WOKE UP
 
  sleep_disable();
  detachInterrupt(0);
  Serial.println("WAKEUP");
  previousLoop = millis();
  NRF24L01.powerUp();
}

void setup() {
  // disable ADC
  ADCSRA = 0;
  Serial.begin(9600);
  pinMode(2, INPUT);
  NRF24L01.begin();
  NRF24L01.setRetries(0, 15);
  NRF24L01.openWritingPipe(address);
  // Stop listening to make it transmitter only.
  NRF24L01.stopListening();
  Serial.println("Started");
  if (NRF24L01.isChipConnected()) {
    Serial.println("NRF24L01 connected");
  } else {
    Serial.println("NFR24L01 MISSING ! NOTHING WILL BE EMITTED !");
  }
  // Send test signal to tell the hub we're ready and functional
  sendSignal();
}

void loop() {
  if (digitalRead(Jack) == HIGH) {
    debounceUp += millis() - previousLoop;
    debounceDown = 0;
  } else {
    debounceDown += millis() - previousLoop;
  }

  previousLoop = millis();

  if (debounceUp >= DEBOUNCE_UP_THRESHOLD) {
    sendSignal();
  }

  if (debounceDown >= DEBOUNCE_DOWN_THRESHOLD) {
    sleep();
  }
}
