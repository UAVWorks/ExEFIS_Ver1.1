#pragma once
#include <unistd.h>

class RotaryEncoder
{
public:
	
	static int encoderCount;
	static RotaryEncoder* encoders[2];
	static void eventHandler(void);
	static void pressHandler(void);
	
	RotaryEncoder(int a, int b, int c, int index);
	~RotaryEncoder();
	int getValue(void);
	void setValue(int val);
	int getPress(bool clear);
	bool getSinglePress(void);
	
protected:
	

	int value = 0;
	int press = 0;
	
private:
	int pin_a;
	int pin_b;
	int pin_c;
	
	int lastEncoded;
	int lastPress;
	char lastPressState;
	
};

