#include "airspeed.h"
#include <math.h>


static constexpr int speed[43] =
{ 
	15,
	 21,
	 25,
	 29,
	 33,
	 36,
	 39,
	 41,
	 44, 
	46,
	 49,
	 51,
	 53,
	 55,
	 57,
	 59,
	 62,
	 66,
	 69,
	 72,
	75,
	 78,
	 80,
	 83,
	 86,
	 88, 
	90, 
	93,
	 95,
	 97,
	 100, 
	102, 
	104,
	 109,
	 114,
	 118,
	 123, 
	127,
	131,
	 135,
	 139, 
	143
};
static constexpr int press[43] = 
{ 
	1, 
	2,
	 3,
	 4,
	 5, 
	6, 
	7,
	 8,
	 9,
	 10, 
	11,
	 12,
	 13,
	 14,
	 15, 
	16,
	 18,
	 20,
	 22,
	 24, 
	26,
	 28,
	 30,
	32,
	 34,
	 36,
	 38, 
	40, 
	42, 
	44,
	 46, 
	48, 
	50, 
	55,
	 60,
	 65,
	 70, 
	75, 
	80,
	 85,
	 90,
	 95
};

float airspeed::getAirspeedMph(float pressuremBar, float tempC, float staticPressPSI)
{
	//calc rho for density of air
	//R = 8.3144598×10−6 m3 MPa K−1 mol−1
	//float staticPressMPa = staticPressPSI * 0.00689476; //N / m2
	//float rho = staticPressMPa / ((tempC + 273.15f) * 0.00000083144598f); //RHO IS IN kg / M3
	float rho = 1.225;  //kg / m3
	float unitConversion = 100.0f * 2.23694 / 9.8f;  //(Pa*kg*m*mph) / (mBar * Pa * s2 * m2 *m/2)
	float velocity = sqrt((2*pressuremBar*unitConversion) / rho);
	
	/*
	int inh20 = pressuremBar * 0.401865;
	int i = 0;
	bool found = false;
	while (i < 22 && found == false)
	{
		if (press[i] > inh20)
		{
			i -= 2;
			found = true; 
		}
		i++;
	}
	
	if (i < 0) i = 0;
	
	float percent = (inh20 - press[i]) / (press[i + 1] - press[i]);
	asp = percent * (speed[i + 1] - speed[i]) + speed[i];
	asp *= 0.53997;
	*/
	
	return velocity;
}
