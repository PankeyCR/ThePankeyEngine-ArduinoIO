
#include "InputEventAppState.hpp"
#include "AnalogInput.hpp"
#include "TPC.hpp"

using namespace pankey::Base;
using namespace pankey::IO;
using namespace pankey::ArduinoIO;

InputEventAppState<int,AnalogInput> state;
AnalogInput input;
TPC tpc;
int a_app = 15;

void setup() {
  delay(3000);
  Serial.begin(9600);
  Serial.println("start");

  input = AnalogInput(2, 100, 1.0f, 0);
  state.add(0, input, AnalogInputAction, Event);
  state.add(1, input, AnalogInputAction, AppEvent);
  tpc.initialize(millis());
  state.initialize(a_app);
  state.onEnable();
}

void loop() {
  state.update(a_app, tpc.generateTpc(millis()));
}

void Event(int a_interrupt, AnalogInput& a_input){
  Serial.print("Analog input: ");
  Serial.println(a_input.value);
}

void AppEvent(int& a_app, int a_interrupt, AnalogInput& a_input){
  Serial.print("App Analog input: ");
  Serial.println(a_input.value);
}


