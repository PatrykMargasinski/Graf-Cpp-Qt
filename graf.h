#include <iostream>
#include <list>
#include <vector>
#include <QWidget>
#include <QToolBar>
#include <QDebug>
#include <QPainter>
#include <QDesktopWidget>
#include <QLabel>
#include <QVector>
#include <QXmlStreamWriter>
#include <QMouseEvent>
using namespace std;



struct Element
{
    int x;
    int y;
    int nr;
    vector <Element*> nast;
    Element(int,int);
    Element();
};

class Graf : public QWidget
{
    Q_OBJECT
    public:
    Graf();
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QDesktopWidget dw;
    list <Element> elementy;
    static QFont tekst;
    QPointF lastMousePosition;
    QPointF mouseMoveOffset;
    void polacz(int,int);
    void usun(int);
    void lista_sasiedztwa();
    void dodaj(int,int);
    void dodaj2(int,int);
    void zmien(int,int,int);
    void mysz(int x, int y);
    void myszowelaczenie();
    int lacz1; int lacz2;
    //void pozycja(QPoint position);
    bool test(bool*);
    int aktywator;
    int xmyszy;
    int ymyszy;
public slots:
    void dodawanie();
    void laczenie();
    void usuwanie();
    void bfs();
    void dfs();
    void zmiana();
    void zapis();
    void odczyt();
    void czyszczenie();

};

