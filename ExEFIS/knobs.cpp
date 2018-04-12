#include "knobs.h"
#include "RotaryEncoder.h"
#include <wiringPi.h>

knobs::knobs()
{

	
	wiringPiSetupGpio();
	left = new RotaryEncoder(12, 13, 19, 0);
	right = new RotaryEncoder(5, 6, 16, 1);
}


knobs::~knobs()
{
}
