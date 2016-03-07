#include <hid_custom_rq.h>

const int ledPin = 13;

void setup() {
  hid_custom_rq.ledPin = ledPin;
  pinMode(hid_custom_rq.ledPin, OUTPUT);
}

void loop() {
  hid_custom_rq.poll();
}
