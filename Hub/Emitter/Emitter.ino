#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <avr/sleep.h>

int Jack = 2;
int DEBOUNCE_UP_THRESHOLD = 2000;
int DEBOUNCE_DOWN_THRESHOLD = 5000;

RF24 NRF24L01 (7, 8);
const byte address[6] = "000001";
uint8_t detectorNumber = 1;

int debounceUp = 0;
int debounceDown = 0;

void sendSignal() {
  for (int i = 0; i < 5; i++) {
    NRF24L01.write(&detectorNumber, sizeof(detectorNumber));
  }
  delay(100);
}

void wakeUp() {
  sleep_disable();
  detachInterrupt(0);
}

void sleep() {
  delay(100);
  debounceUp = 0;
  debounceDown = 0;
  sleep_enable();
  attachInterrupt(0, wakeUp, RISING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  NRF24L01.begin();
  // Set PA level to max for maximum range.
  NRF24L01.setPALevel(RF24_PA_MAX);
  NRF24L01.setDataRate(RF24_250KBPS);
  NRF24L01.openWritingPipe(address);
  // Stop listening to make it transmitter only.
  NRF24L01.stopListening();
  // Send test signal to tell the hub we're ready and functional
  sendSignal();
}

void loop() {
  if (digitalRead(Jack) == HIGH) {
    debounceUp += millis();
    debounceDown = 0;
  } else {
    debounceDown += millis();
  }

  if (debounceUp >= DEBOUNCE_UP_THRESHOLD) {
    sendSignal();
  }

  if (debounceDown >= DEBOUNCE_DOWN_THRESHOLD) {
    sleep();
  }
}
