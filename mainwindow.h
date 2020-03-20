#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QLineF>
#include <QLabel>
#include <QWidget>
#include <vector>
#include <QPushButton>
#include <vector>
#include <list>
#include <QDesktopWidget>
#include "graf.h"
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //QPushButton *PrzyciskDodaj;
    explicit MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    ~MainWindow();
    int i;
    Graf g;
    QPushButton *PrzyciskDodaj;
    QPushButton *PrzyciskPolacz;
    QPushButton *PrzyciskUsun;
    QPushButton *PrzyciskDFS;
    QPushButton *PrzyciskBFS;
    QPushButton *PrzyciskZmien;
    QPushButton *PrzyciskZapisz;
    QPushButton *PrzyciskWczytaj;
    QPushButton *PrzyciskWyczysc;
    QDesktopWidget dw;

};

#endif // MAINWINDOW_H
