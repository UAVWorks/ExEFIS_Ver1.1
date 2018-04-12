#include "directional_gyro.h"



directional_gyro::directional_gyro(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	this->penColor = Qt::white;
	value = -1.0f;
	setting = 0.0f;
	
	blinkTimer = new QTimer(this);
	blinkTimer->setInterval(500);
	connect(blinkTimer, SIGNAL(timeout()), this, SLOT(onBlinkTimer()));
}


directional_gyro::~directional_gyro()
{
}

void directional_gyro::paintEvent(QPaintEvent *event)
{
	float val = value - setting;
	if (val < 0) val += 360.0f;
	val	/= 10.0f;
	int wide = width() * 0.75f;
	int high = height() * 0.9f;
	int y = height() * 0.4f;
	int x = width() * 0.125f;
	
	int wr = width() / 50;
	if (wr < 2) wr = 2;
	
	QPoint tl = QPoint((width() / 2) - (wr / 2), height() * 0.1f);
	QPoint br = QPoint((width() / 2) + (wr / 2), high);
	QRect lne = QRect(tl, br);
	
	QPainter painter(this);
	painter.setPen(penColor);
	if (blinking)painter.setPen(Qt::blue);
	painter.setBrush(Qt::white);
	painter.drawRect(lne);
	
	
	painter.setPen(Qt::black);
	painter.setBrush(Qt::black);
	int horiz_divs = 4;
	
	/* horiz is the width of each rectangle for values*/
	int horiz = wide / horiz_divs / 2; //"4" is the number of divs
	bool found = false;
	int i;
	/* find the value above the indicated value*/
	for (i = 0; i < 12 && !found; i++)
	{
		if (values[i] < val) found = true;
	}
	
	i -= 2;
	
	if (i < 0)i = 12 + i;
	int abovevalue = values[i];
	int belowvalue = i-1 < 0 ? values[12+i-1] : values[i - 1];
	
	
	/* first idx is the left value in the values list*/
	int firstidx = i + (horiz_divs / 2) - 1;
	int lastidx = firstidx - horiz_divs;
	int horizDistance = horiz * 2; /* dist between them*/
	//int divisor = belowvalue < abovevalue ? abovevalue - belowvalue : abovevalue + (belowvalue - 36);
	float shift = (horizDistance *
		(val - abovevalue)) / (abovevalue - belowvalue);
	
	
	/* Create the rectangles for each of the values*/
	QRect rects[horiz_divs];
	for (int j = 0; j < horiz_divs; j++)
	{
		rects[j] = QRect(x + (horiz * 2*j) + shift, y, high, horiz);
	}
	
	int vIndex = 0;
	for (int j = 0; j < horiz_divs; j++)
	{
		vIndex = (firstidx - j) >= 0 ? firstidx - j : 12 + (firstidx - j);
		/* First index is the highest value of i becuase it reads top down high to low*/
		painter.drawText(rects[j], Qt::AlignLeft, QString::number(values[vIndex]));
	}
}
