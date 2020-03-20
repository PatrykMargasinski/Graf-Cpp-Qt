#include "mainwindow.h"


using namespace std;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QDesktopWidget dw;
    int x=1200;
    int y=800;
    this->setFixedSize(x,y);
    this->setWindowTitle("Graf");
    this->setCentralWidget(&g);

    PrzyciskDodaj = new QPushButton("Nowy wierzchołek",this);
    connect(PrzyciskDodaj, SIGNAL(clicked()), &g, SLOT(dodawanie()));
    PrzyciskDodaj->setGeometry((x/10)-60,15,120,30);

    PrzyciskPolacz = new QPushButton("Połącz wierzchołki",this);
    connect(PrzyciskPolacz, SIGNAL(clicked()), &g, SLOT(laczenie()));
    PrzyciskPolacz->setGeometry(x/10*2-60,15,120,30);

    PrzyciskUsun = new QPushButton("Usuń wierzchołek",this);
    connect(PrzyciskUsun, SIGNAL(clicked()), &g, SLOT(usuwanie()));
    PrzyciskUsun->setGeometry(x/10*3-60,15,120,30);

    PrzyciskDFS = new QPushButton("DFS",this);
    connect(PrzyciskDFS, SIGNAL(clicked()), &g, SLOT(dfs()));
    PrzyciskDFS->setGeometry(x/10*4-60,15,120,30);

    PrzyciskBFS = new QPushButton("BFS",this);
    connect(PrzyciskBFS, SIGNAL(clicked()), &g, SLOT(bfs()));
    PrzyciskBFS->setGeometry(x/10*5-60,15,120,30);

    PrzyciskZmien = new QPushButton("Zmień",this);
    connect(PrzyciskZmien, SIGNAL(clicked()), &g, SLOT(zmiana()));
    PrzyciskZmien->setGeometry(x/10*6-60,15,120,30);

    PrzyciskZapisz = new QPushButton("Zapisz",this);
    connect(PrzyciskZapisz, SIGNAL(clicked()), &g, SLOT(zapis()));
    PrzyciskZapisz->setGeometry(x/10*7-60,15,120,30);

    PrzyciskWczytaj = new QPushButton("Wczytaj",this);
    connect(PrzyciskWczytaj, SIGNAL(clicked()), &g, SLOT(odczyt()));
    PrzyciskWczytaj->setGeometry(x/10*8-60,15,120,30);

    PrzyciskWyczysc = new QPushButton("Wyczyść",this);
    connect(PrzyciskWyczysc, SIGNAL(clicked()), &g, SLOT(czyszczenie()));
    PrzyciskWyczysc->setGeometry(x/10*9-60,15,120,30);
}

MainWindow::~MainWindow()
{

}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
   painter.setBrush(QBrush{Qt::cyan});
   painter.drawRect(0,0,dw.width(),45);
   painter.setBrush(QBrush{Qt::blue});
   painter.drawRect(0,45,dw.width(),dw.height()-45);
}
int i=0;
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    //qDebug()<<"MouseMoveEventdziala"<<i;
    if(event->buttons() == Qt::LeftButton)
    {
    //i++;
    int x = event->pos().rx();
    int y = event->pos().ry();
    g.mysz(x,y);
    }
}

