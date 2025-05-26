
#include "AnalogInput.hpp"
#include "TPC.hpp"

using namespace pankey::Base;
using namespace pankey::ArduinoIO;

AnalogInput input;
TPC tpc;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  input = AnalogInput(2, 100, 1.0f, 0);
  input.initialize();
  tpc.initialize(millis());
}

void loop() {
  AnalogInputAction(input, tpc.generateTpc(millis()));
  Serial.print("Analog input: ");
  Serial.println(input.value);
}
