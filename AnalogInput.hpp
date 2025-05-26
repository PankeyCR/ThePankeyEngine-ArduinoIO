
#ifndef AnalogInput_hpp
	#define AnalogInput_hpp

	#if defined(pankey_Log) && (defined(AnalogInput_Log) || defined(pankey_Global_Log) || defined(pankey_States_Log))
		#include "Logger_status.hpp"
		#define AnalogInputLog(status,method,mns) pankey_Log(status,"AnalogInput",method,mns)
	#else
		#define AnalogInputLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoIO{

			class AnalogInput{
				public:
					int pin = -1;
					float value = -1.0f;
					float resolution = 1.0f;
					float offset = 0.0f;
					bool pause = false;
					long start = 0;
					long interval = 0;

					AnalogInput(){
						AnalogInputLog(pankey_Log_StartMethod, "Constructor", "");
						AnalogInputLog(pankey_Log_EndMethod, "Constructor", "");
					}
					AnalogInput(int a_pin){
						AnalogInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						AnalogInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					AnalogInput(int a_pin, long a_interval){
						AnalogInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						interval = a_interval;
						AnalogInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					AnalogInput(int a_pin, long a_interval, float a_resolution){
						AnalogInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						interval = a_interval;
						resolution = a_resolution;
						AnalogInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					AnalogInput(int a_pin, long a_interval, float a_resolution, float a_offset){
						AnalogInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						interval = a_interval;
						resolution = a_resolution;
						offset = a_offset;
						AnalogInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					AnalogInput(const AnalogInput& a_di){
						AnalogInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_di.pin;
						value = a_di.value;
						resolution = a_di.resolution;
						offset = a_di.offset;
						pause = a_di.pause;
						interval = a_di.interval;
						AnalogInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					virtual ~AnalogInput(){}

					void initialize(){
						AnalogInputLog(pankey_Log_StartMethod, "initialize", "");
						AnalogInputLog(pankey_Log_Statement, "initialize", "initializing pin");
						AnalogInputLog(pankey_Log_Statement, "initialize", pin);
						if(pin != -1){
							pinMode(pin, INPUT);
							AnalogInputLog(pankey_Log_Statement, "initialize", "pin has been initialize");
						}
						AnalogInputLog(pankey_Log_EndMethod, "initialize", "");
					}
						
					virtual void operator=(const AnalogInput& a_di){
						AnalogInputLog(pankey_Log_StartMethod, "operator=", "");
						pin = a_di.pin;
						value = a_di.value;
						resolution = a_di.resolution;
						offset = a_di.offset;
						pause = a_di.pause;
						interval = a_di.interval;
						AnalogInputLog(pankey_Log_EndMethod, "operator=", "");
					}
					virtual bool operator==(AnalogInput a_di){
						return resolution == a_di.resolution && offset == a_di.offset && pause == a_di.pause && interval == a_di.interval && pin == a_di.pin && value == a_di.value;
					}
					virtual bool operator!=(AnalogInput a_di){
						return resolution != a_di.resolution && offset != a_di.offset && pause != a_di.pause && interval != a_di.interval && pin != a_di.pin && value != a_di.value;
					}
			};

			bool AnalogInputAction(AnalogInput& a_input, long a_tpc){
				AnalogInputLog(pankey_Log_StartMethod, "AnalogInputAction", "");

				if(a_input.pause){
					AnalogInputLog(pankey_Log_EndMethod, "AnalogInputAction", "a_input.pause");
					return false;
				}
				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", "Pin number:");
				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", a_input.pin);

				int i_value = analogRead(a_input.pin);

				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", "Pin value:");
				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", i_value);

				if((millis() - a_input.start) <= a_input.interval){
					AnalogInputLog(pankey_Log_EndMethod, "AnalogInputAction", "(millis() - a_input.start) < a_input.check");
					return false;
				}

				a_input.start = millis();
				a_input.value = (i_value * a_input.resolution) + a_input.offset;

				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", "value:");
				AnalogInputLog(pankey_Log_Statement, "AnalogInputAction", a_input.value);
				
				AnalogInputLog(pankey_Log_EndMethod, "AnalogInputAction", "return true");
				return true;
			}

		}

	}

#endif