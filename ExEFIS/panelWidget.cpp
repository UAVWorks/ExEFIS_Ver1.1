#include "panelWidget.h"
#include "horizon_instrument.h"
#include "vertical_instrument.h"
#include "directional_gyro.h"
#include "reticle.h"
#include "airspeed.h"
#include "altitude.h"
#include <QWidget>
#include <QGridLayout>

int counter = 0;

panelWidget::panelWidget(QWidget *parent)
	: QWidget(parent)
{
	setCursor(Qt::BlankCursor);

	/* SSK Note that this order matters and affects draw order*/
	h1 = new horizon_instrument(this);
	vi1 = new vertical_instrument(this, Qt::black);

	int altvals[10] = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000 };	
	vi2 = new vertical_instrument(this, Qt::black);
	vi2->setupInstrument(altvals, 10);
	vi2->setValue(6350);
	vi2->setting = 2992;
	vi2->showSetting = true;
	
	ss = new slipskid_instrument(this);
	dg = new directional_gyro(this);
	dg->value = 7;
	r = new reticle(this);
	
	sw = new StatusWidget(this);

	
	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->setColumnStretch(0, 1);
	mainLayout->setColumnStretch(1, 3);
	mainLayout->setColumnStretch(2, 1);
	mainLayout->setRowStretch(0, 1);
	mainLayout->setRowStretch(1, 1);
	mainLayout->setRowStretch(2, 3);
	mainLayout->setRowStretch(3, 1);
	mainLayout->setRowStretch(4, 1);
	
	
	mainLayout->addWidget(h1, 0, 0, 5, 3, 0);
	
	/* SSK - note the magic here is the 4th arg "1" that is the column span */
	mainLayout->addWidget(vi1, 1, 0, 3, 1, 0);
	mainLayout->addWidget(vi2, 1, 2, 3, 1, 0);
	mainLayout->addWidget(r, 2, 1, 1, 1, 0);
	mainLayout->addWidget(ss, 3, 1, 1, 1, 0);
	mainLayout->addWidget(dg, 0, 1, 2, 1, 0);
	mainLayout->addWidget(sw, 4, 1, 1, 1, 0);
	
	qtimer = new QTimer(this);
	qtimer->setInterval(100);
	connect(qtimer, SIGNAL(timeout()), this, SLOT(onTimer()));
}


panelWidget::~panelWidget()
{
}


void panelWidget::onTimer(void)
{
	//add 90 to y for pitch
	//use z for roll
	adhr->readAll();
	float adhrdata[6];
	int status = adhr->getAllSixRaw(adhrdata);
	
	
	h1->setAzimuth(adhrdata[4]); // range is 0 (up) to -180 (down)
	h1->setAngle(adhrdata[3]);
	dg->value = adhrdata[2];
	vi1->setValue(airspeed::getAirspeedMph(adhrdata[1], 25, adhrdata[0]));
	vi2->setValue(altitude::getAltitudeFt(adhrdata[0], vi2->setting/pow(10, vi2->settingPrec)));
	ss->setValue(adhrdata[5]/-2.0f);
	
	counter++;
	if (counter >= 5)
	{
		char cal[4];
		counter = 0;
		adhr->getCalibration(cal);
		sw->status = "Sys: " + QString::number(cal[0]) + " Gyro: " + QString::number(cal[1]) + "\r" + "\n" +
			"Accel: " + QString::number(cal[2]) + " Mag: " + QString::number(cal[3]);
	}
	
	if (knob->left->getSinglePress())
	{
		dg->toggleEditMode();
		knob->left->setValue(dg->setting);
	}
	if (knob->right->getSinglePress())
	{
		vi2->toggleEditMode();
		knob->right->setValue(vi2->setting);
	}
	
	if (dg->editMode)dg->setSetting(knob->left->getValue());
	if (vi2->editMode)vi2->setSetting(knob->right->getValue());
	
	if (knob->right->getPress(false) > 10)
	{
		qtimer->stop();
		close();
		launchDiag(2);		
	}
}


void panelWidget::setADHRS(adhrs* a)
{
	adhr = a;
}


void panelWidget::setKNOBS(knobs* k)
{
	/* be sure and read the presses and clear them when you set the variable*/
	knob = k;
	knob->left->getPress(true);
	knob->right->getPress(true);
}


void panelWidget::showEvent(QShowEvent *event)
{
	qtimer->start();
}
