#include "adhrs.h"
#include "BNO055.h"
#include "hsc_pressure.h"



adhrs::adhrs()
{
	staticpress = new hsc_pressure();
	airspeed = new hsc_pressure(1);
	airspeed->set_params(60, -60);
	bno055 = new BNO055(BNO055_ID, BNO055_ADDRESS_A);
	//bno055->begin(BNO055::OPERATION_MODE_NDOF);
	bno055->begin(BNO055::OPERATION_MODE_IMUPLUS);
	if (!bno055->isFullyCalibrated())
	{
		//while (1)
			;
	}
}


adhrs::~adhrs()
{
}


void adhrs::readAll(void)
{
	staticPressurePSI = staticpress->getPressure();
	aspPressureMBAR = airspeed->getPressure();
	imu::Vector<3> v = bno055->getVector(BNO055::adafruit_vector_type_t::VECTOR_EULER);		
	imu::Vector<3> a = bno055->getVector(BNO055::adafruit_vector_type_t::VECTOR_GRAVITY);
	//imu::Quaternion v = bno055->getQuat();
	this->euHeading = v.x(); //page 35 in BNO055 manual for order here
	this->euRoll = v.y();
	this->euPitch = v.z();
	slipRAW = a.x();
	char t = bno055->getTemp();
}


int adhrs::getAllSixRaw(float* data)
{
	int status = 0;
	data[0] = this->staticPressurePSI;
	data[1] = this->aspPressureMBAR;
	data[2] = this->euHeading;
	data[3] = this->euRoll;
	data[4] = this->euPitch;
	data[5] = this->slipRAW;
	
	return status;
}


uint adhrs::readBNORegister(uint reg)
{
	return(this->bno055->readRegister(reg));
}


int adhrs::writeBNORegister(uint reg, uint value)
{
	this->bno055->writeRegister(reg, value);
	return (1);
}

int adhrs::getOffsets(char* calData)
{
	if (this->bno055->getSensorOffsets(calData)) return 1;
	return 0;
}


int adhrs::setOffsets(char* calData)
{
	this->bno055->setSensorOffsets(calData);
	return 1;
}


void adhrs::getCalibration(char* cal)
{
	this->bno055->getCalibration(&cal[0], &cal[1], &cal[2], &cal[3]);
}
