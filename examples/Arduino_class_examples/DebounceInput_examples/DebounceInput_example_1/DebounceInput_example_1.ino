
#include "DebounceInput.hpp"
#include "TPC.hpp"

using namespace pankey::Base;
using namespace pankey::ArduinoIO;

DebounceInput input;
TPC tpc;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  input = DebounceInput(26, false, 100);
  input.initialize();
  tpc.initialize(millis());
}

void loop() {
  DebounceInputAction(input, tpc.generateTpc(millis()));
  Serial.print("Debounce input: ");
  Serial.println(input.state);
}