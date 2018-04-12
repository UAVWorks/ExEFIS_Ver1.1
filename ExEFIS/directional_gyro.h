#pragma once
#include <QWidget.h>
#include <QTimer>
#include <QPen.h>
#include <QPainter>

class directional_gyro :public QWidget
{
	Q_OBJECT
		
public :
	directional_gyro(QWidget *parent = 0);
	~directional_gyro();
	int value;
	int setting;
	bool editMode = false;
	
	void toggleEditMode()
	{
		editMode = !editMode;
		if (editMode) blinkTimer->start();
		else
		{
			blinkTimer->stop();
			blinking = false;
		}
	}
	
	void setSetting(int arg1)
	{
		setting = arg1;
	}
	
	public slots :
			void onBlinkTimer(void)
	{
		blinking = !blinking;
		update();
	}
	
	
protected: 
	void paintEvent(QPaintEvent *event) override;
	
	
private:
	QColor penColor;
	QTimer *blinkTimer;
	bool blinking = false;
	
	int values[12] = 
	{ 
		36,
		33,
		30,
		27,
		24,
		21,
		18,
		15,
		12,
		9,
		6,
		3		
	};

};

