#include "altitude.h"
#include <math.h>



float altitude::getAltitudeFt(float pressurePSI, float setting)
{
	float mbars = 68.946f * pressurePSI;
	//altitude ft = ((mbars / 1013.25) ^ 0.190284) * 145366.45;
	float alt = (1-pow((mbars / 1013.25), 0.190284)) * 145366.45;
	alt = (setting - 29.92) * 1000 + alt;
	return (alt);
}
