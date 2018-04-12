#include "SplashWidget.h"
#include "panelWidget.h"
#include "DiagWidget.h"
#include "knobs.h"
#include "adhrs.h"
#include <QApplication>
#include <QStackedWidget>
#include <QProcess>
#include <QWidget>
#include <QScreen>
#include <bcm2835.h>

int main(int argc, char *argv[])
{	
	QStringList list = QProcessEnvironment::systemEnvironment().toStringList();
		

	
	system("gpio edge 12 both");
	system("gpio edge 13 both");
	system("gpio edge 19 both");
	
	system("gpio edge 5 both");
	system("gpio edge 6 both");
	system("gpio edge 16 both");
	
	bcm2835_init();

	QApplication a(argc, argv);

	QScreen *screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	
	adhrs *ad = new adhrs();
	knobs *k = new knobs();
	
	QStackedWidget *w = new QStackedWidget();
	
	panelWidget *p = new panelWidget();
	p->setADHRS(ad);
	p->setKNOBS(k);
	p->showFullScreen();
	p->update();
	
	
//	SplashWidget *s = new SplashWidget(0, ad, k);
//	s->showFullScreen();
//	s->update();
	
//	DiagWidget *m = new DiagWidget();
//	m->setADHRS(ad);
//	m->setKnobs(k);
	//m->show();
	
//	w->addWidget(s);
//	w->addWidget(p);
//	w->addWidget(m);
	
	//s->setParent(w);
	//p->setParent(p);
	//m->setParent(m);
	//QStackedWidget::connect(p, SIGNAL(launchDiag(int)), w, SLOT(setCurrentIndex(int)));
//	QStackedWidget::connect(s, SIGNAL(launchPanel(int)), w, SLOT(setCurrentIndex(int)));
//	QApplication::connect(s, SIGNAL(closeStacked()), w, SLOT(quit()));
	w->setCurrentIndex(0);
//	w->showFullScreen();
//	w->update();
	
	//panelWidget *w = new panelWidget();
	//w->showFullScreen();
	

	
    return a.exec();
}
