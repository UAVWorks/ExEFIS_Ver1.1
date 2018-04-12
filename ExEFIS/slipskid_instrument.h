#pragma once

#include <QWidget>
#include <QPen>

class slipskid_instrument :public QWidget
{
	
public:
	slipskid_instrument(QWidget *parent);
	~slipskid_instrument();
	
	void setValue(float val);
	
protected: 
	void paintEvent(QPaintEvent *event) override;
	
private:
	QPen pen;
	QColor penColor;
	float value; /* number of balls out */
	
};

