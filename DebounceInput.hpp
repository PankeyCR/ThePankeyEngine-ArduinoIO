
#ifndef DebounceInput_hpp
	#define DebounceInput_hpp

	#if defined(pankey_Log) && (defined(DebounceInput_Log) || defined(pankey_Global_Log) || defined(pankey_States_Log))
		#include "Logger_status.hpp"
		#define DebounceInputLog(status,method,mns) pankey_Log(status,"DebounceInput",method,mns)
	#else
		#define DebounceInputLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoIO{

			class DebounceInput{
				public:
					bool inverted = false;
					int pin = -1;
					bool state = false;
					bool reading = false;
					long start = 0;
					long check = 100;

					DebounceInput(){
						DebounceInputLog(pankey_Log_StartMethod, "Constructor", "");
						DebounceInputLog(pankey_Log_EndMethod, "Constructor", "");
					}
					DebounceInput(int a_pin){
						DebounceInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						DebounceInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					DebounceInput(int a_pin, bool a_inverted, long a_check){
						DebounceInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						pin = a_pin;
						inverted = a_inverted;
						check = a_check;
						DebounceInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					DebounceInput(const DebounceInput& a_di){
						DebounceInputLog(pankey_Log_StartMethod, "CopyConstructor", "");
						inverted = a_di.inverted;
						pin = a_di.pin;
						state = a_di.state;
						DebounceInputLog(pankey_Log_EndMethod, "CopyConstructor", "");
					}
					virtual ~DebounceInput(){}

					void initialize(){
						DebounceInputLog(pankey_Log_StartMethod, "initialize", "");
						DebounceInputLog(pankey_Log_Statement, "initialize", "initializing pin");
						DebounceInputLog(pankey_Log_Statement, "initialize", pin);
						if(pin != -1){
							pinMode(pin, INPUT);
							DebounceInputLog(pankey_Log_Statement, "initialize", "pin has been initialize");
						}
						DebounceInputLog(pankey_Log_EndMethod, "initialize", "");
					}
						
					virtual void operator=(DebounceInput a_di){
						DebounceInputLog(pankey_Log_StartMethod, "operator=", "");
						inverted = a_di.inverted;
						pin = a_di.pin;
						state = a_di.state;
						DebounceInputLog(pankey_Log_EndMethod, "operator=", "");
					}
					virtual bool operator==(DebounceInput a_di){
						return inverted == a_di.inverted && pin == a_di.pin && state == a_di.state;
					}
					virtual bool operator!=(DebounceInput a_di){
						return inverted != a_di.inverted && pin != a_di.pin && state != a_di.state;
					}
			};

			bool DebounceInputAction(DebounceInput& a_input, long a_tpc){
				DebounceInputLog(pankey_Log_StartMethod, "DebounceInputAction", "");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "Pin number:");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", a_input.pin);
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "Pin state:");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", digitalRead(a_input.pin));

				bool i_input = false;
				if(a_input.inverted){
					i_input = !digitalRead(a_input.pin);
				}else{
					i_input = digitalRead(a_input.pin);
				}
				if(i_input == a_input.state){
					DebounceInputLog(pankey_Log_EndMethod, "DebounceInputAction", "i_input == a_input.state");
					a_input.reading = false;
					return false;
				}
				if(!a_input.reading){
					DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "!a_input.reading");
					a_input.reading = true;
					a_input.start = millis();
				}
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "start time:");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", a_input.start);
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "time:");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", millis());
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "check time:");
				DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", a_input.check);
				if((millis() - a_input.start) < a_input.check){
					DebounceInputLog(pankey_Log_EndMethod, "DebounceInputAction", "(millis() - a_input.start) < a_input.check");
					return false;
				}
				if(a_input.inverted){
					DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "a_input.state = !i_input;");
					a_input.state = !i_input;
				}else{
					DebounceInputLog(pankey_Log_Statement, "DebounceInputAction", "a_input.state = i_input;");
					a_input.state = i_input;
				}
				DebounceInputLog(pankey_Log_EndMethod, "DebounceInputAction", "return true");
				return true;
			}

		}

	}

#endif