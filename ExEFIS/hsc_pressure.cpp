#include "hsc_pressure.h"
#include <bcm2835.h>



hsc_pressure::hsc_pressure()
{
	InitSPI();
}

hsc_pressure::hsc_pressure(int cs)
{
	chipEnable = cs;
	InitSPI();
}

hsc_pressure::~hsc_pressure()
{
}

float hsc_pressure::getPressure(void)
{
	char vals[4];
	char args[4] = { 0, 0, 0, 0 };
	SPITransfer(args, vals, 4);
	/* Check the MSBs of vals[0] for normal operation - should be zero*/
	float ret = 0.0f;
	int tics = 0;
	if (!(vals[0] & 0xC0))
	{
		tics = (vals[0] & 0x3F) * 256;
		tics += vals[1];
		ret = ((((float)tics - MIN_OUTPUT)*(maxPress - minPress)) /
			(MAX_OUTPUT - MIN_OUTPUT)) + minPress;
	}
	return (ret);
}
/**********************************************************************************************//**
* Module: hsc_pressure::InitSPI
***************************************************************************************************
* @brief	Setup the SPI

* @note		
*
* @todo		
*
* @param[in,out]	
* @param[in]		
* @returns			
***************************************************************************************************
***************************************************************************************************
* @author
* @li SSK - 11/06/17 - Created & Commented
**************************************************************************************************/
int hsc_pressure::InitSPI(void)
{
	if (!bcm2835_init())
	{		
		return 1;
	}

	if (!bcm2835_spi_begin())
	{		
		return 1;
	}
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);         // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                       // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_512);  		// The default
	bcm2835_spi_chipSelect(chipEnable);                            // The default
	bcm2835_spi_chipSelect(chipEnable); 	
	bcm2835_spi_setChipSelectPolarity(chipEnable, LOW);          // the default
	
	
	return 0;
}


/**********************************************************************************************//**
* Module: hsc_pressure::SPITransfer
***************************************************************************************************
* @brief	

* @note 
*
* @todo 
*
* @param[in,out]	
* @param[in]		
* @returns			
***************************************************************************************************
***************************************************************************************************
* @author
* @li SSK - 11/06/17 - Created & Commented
**************************************************************************************************/
void hsc_pressure::SPITransfer(char* arg, char*resp, int length)
{		
	bcm2835_spi_chipSelect(chipEnable);                             // The default
	bcm2835_spi_setChipSelectPolarity(chipEnable, LOW);           // the default
	bcm2835_spi_transfernb(arg, resp, length);
}



void hsc_pressure::set_params(int max, int min)
{
	maxPress = max;
	minPress = min;
}
