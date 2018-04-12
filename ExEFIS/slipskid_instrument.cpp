#include <QWidget>
#include <QPainter>
#include <QPen>
#include "slipskid_instrument.h"



slipskid_instrument::slipskid_instrument(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	this->penColor = Qt::white;
	value = -1.0f;
}


slipskid_instrument::~slipskid_instrument()
{
}


void slipskid_instrument::setValue(float val)
{
	value = val;
	update();
}


void slipskid_instrument::paintEvent(QPaintEvent *event)
{
	int wide = width() / 10;
	int hi = wide;
	int tlx = (width() / 2) - (wide / 2); /* Top Left X */
	int tly = (height() / 2) - (hi / 2); /* Top Left Y */
	
	QRect r = QRect(tlx, tly, wide, hi);
	
	int wr = wide / 5;
	QRect lv = QRect(tlx - (2*wr), tly, wr, hi);
	QRect lr = QRect(((tlx + wide) + (wr)), tly, wr, hi);
	
	QPainter painter(this);
	painter.setPen(penColor);
	painter.setBrush(Qt::white);
	
	painter.translate(value*wide, 0);
	painter.drawEllipse(r);
	
	painter.translate(-value*wide, 0);
	painter.setPen(Qt::black);
	painter.drawRect(lv);
	painter.drawRect(lr);
}
