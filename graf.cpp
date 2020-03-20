#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include "mainwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QtCore>
#include <string>
#include <QInputDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QtXml>
#include <QMouseEvent>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
int numer=0;
int promienkola=40;
QRect* rectangle;
bool porownanie(const pair<int, int>&i, const pair<int, int>&j)
{
    return i.first < j.first;
}
Graf::Graf()
{
    aktywator=-1;
    lacz1=-1;lacz2=-1;
}
QFont Graf::tekst("Arial", 15);
Element::Element(int xx, int yy):x(xx),y(yy+20),nr(numer++)
{
}
Element::Element():x(0),y(0),nr(numer++)
{
}
void Graf::czyszczenie()
{
    for(list<Element>::iterator it=elementy.begin();it!=elementy.end();it++)
    {
        (*it).nast.clear();
    }
    elementy.clear();
    numer=0;
    lacz1=-1;lacz2=-1;
    update();
}
void Graf::dodaj(int x,int y)
{
    elementy.push_back(Element(x,y));
}
void Graf::polacz(int pier, int dr)
{
    list<Element>::iterator temp=elementy.begin();
    list<Element>::iterator temp2=elementy.begin();
    for(int i=0; i<pier; i++)
    {
        temp++;
    }
    for(int i=0; i<dr; i++)
    {
        temp2++;
    }
    if(temp!=temp2)
    {

    (*temp).nast.push_back(&*temp2);
    (*temp2).nast.push_back(&*temp);

    }
    else
    {
        //qDebug()<<"To samo";
    }
}

void Graf::lista_sasiedztwa()
{

    for(list<Element>::iterator it=elementy.begin(); it!=elementy.end(); it++)
    {
        //qDebug()<<(*it).nr<<" o adresie - "<<&*it<<" :";
        for(int i=0; i<(*it).nast.size(); i++)
        {
            //qDebug()<<" "<<(*it).nast[i]->nr;
        }
        //qDebug()<<endl;
    }
}

void Graf::usun(int pier)
{
    list<Element>::iterator it=elementy.begin();
    for(int i=0; i<pier; i++)
    {
        it++;
    }
    for(int i=0;i<(*it).nast.size();i++)
    {
        for(int j=0;j<(*it).nast[i]->nast.size();j++)
            {
                if((*it).nast[i]->nast[j]->nr==pier)
                {
                    (*it).nast[i]->nast.erase((*it).nast[i]->nast.begin()+j);
                }
            }
        cout<<endl;
    }
    list<Element>::iterator it2=it;
    it++;
    elementy.erase(it2);
    for(;it!=elementy.end();it++)
    {
        (*it).nr--;
    }
    numer--;
}
void Graf::paintEvent(QPaintEvent *event)
{
    string a;
     QPainter painter(this);

        painter.setFont(tekst);
        for(list<Element>::iterator it=elementy.begin();it!=elementy.end();it++)
        {
            for(int i=0;i<(*it).nast.size();i++)
            {
                painter.setPen(QPen(Qt::black, 3));
                painter.drawLine((*it).x,(*it).y,(*it).nast[i]->x,(*it).nast[i]->y);
            }
        }
        for(list<Element>::iterator it=elementy.begin();it!=elementy.end();it++)
        {
            a=to_string((*it).nr);
            painter.setBrush(QBrush{Qt::red});
            painter.setPen(QPen(Qt::black, 1));
            painter.drawEllipse((*it).x-20,(*it).y-20,promienkola,promienkola);
            rectangle = new QRect((*it).x-(7*a.size()), (*it).y-13,promienkola, promienkola);
             painter.drawText(*rectangle, 0, tr(a.c_str()), nullptr);
             delete rectangle;
        }
        if(aktywator!=-1)
        {
            list<Element>::iterator it=elementy.begin();
            for(int i=0;i<aktywator;i++)it++;
            a=to_string((*it).nr);
            rectangle = new QRect((*it).x-(7*a.size()), (*it).y-13,40, 40);
            painter.setBrush(QBrush{Qt::green});
            painter.drawEllipse((*it).x-20,(*it).y-20,40,40);
            painter.drawText(*rectangle, 0, tr(a.c_str()), nullptr);
            delete rectangle;
            //cout<<aktywator;
            aktywator=-1;
            sleep(1);
        }
}
void Graf::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
    dodaj(event->pos().rx(),event->pos().ry());
    update();
    }
    if(event->buttons() == Qt::RightButton)
    {
        bool warunek{0};
        list<Element>::iterator it;
        for(it=elementy.begin(); it!=elementy.end(); it++){
            double temp{(double)(pow(xmyszy-(*it).x,2))+(double)(pow(ymyszy-(*it).y,2))};
            if(temp<pow(40, 2))
            {
                warunek = 1;
                break;
            }
        }
        if(warunek==1)
        {
          usun((*it).nr);
          lacz1=-1;lacz2=-1;
          update();
        }
    }
}

void Graf::dodawanie()
{
    int x = QInputDialog::getInt(this, tr("Dodawanie"), tr("Podaj X"), 0, 0, 1000, 1,nullptr);
    if(x<=25)
    {
        x=25;
    }
    else if(x>=(int)(dw.height()*0.5)-40)
    {
        x=(int)(dw.height()*0.5)-40;
    }
    int y = QInputDialog::getInt(this, tr("Dodawanie"), tr("Podaj Y"), 0, 0, 1000, 1,nullptr);
    if(y<=35)
    {
        y=35;
    }
    else if(y>=(int)(dw.width()*0.5)-40)
    {
        y=(int)(dw.width()*0.5)-40;
    }
    dodaj(x,y);
    update();
}
void Graf::laczenie()
{
    int x = QInputDialog::getInt(this, tr("Łączenie"), tr("Podaj nr pierwszego wierzchołka"), 0, 0, 1000, 1,nullptr);
    int y = QInputDialog::getInt(this, tr("Łączenie"), tr("Podaj nr drugiego wierzchołka"), 0, 0, 1000, 1,nullptr);

    if(x<elementy.size()&&y<elementy.size()) polacz(x,y);
    else if(x>=elementy.size())
    {
        QMessageBox msgBox;
        msgBox.setText("Przynajmniej jeden z podanych przez Ciebie wierzchołków nie istnieje.");
        msgBox.exec();
    }

    update();
}
void Graf::usuwanie()
{
    int y = QInputDialog::getInt(this, tr("Usuwanie"), tr("Podaj nr wierzchołka"), 0, 0, 1000, 1,nullptr);
    if(y<elementy.size()) usun(y);
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Nie ma takiego wierzchołka.");
        msgBox.exec();
    }
    update();
}

void Graf::zapis()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz"),"",tr("Plik XML (*xml)"));
    if(fileName == ""){
        return;
    }
    QFile file(fileName);
    if(!(file.open(QIODevice::WriteOnly))){
        return;
    }
    QDomDocument document;
    QDomElement root = document.createElement("Graf");

    for(list<Element>::iterator it=elementy.begin();it!=elementy.end();it++)
    {
       QDomElement wierz = document.createElement("Wierzcholek");
        QString polozenie{QString::number((*it).x)
                               +","+QString::number((*it).y)};
        wierz.setAttribute("polozenie", polozenie);
        wierz.setAttribute("numer", (*it).nr);
        root.appendChild(wierz);
        for(int i=0;i<(*it).nast.size();i++){
            QDomElement lacznik = document.createElement("lacznik");
            QDomText edgeText = document.createTextNode(QString::number((*it).nast[i]->nr));
            lacznik.appendChild(edgeText);
            wierz.appendChild(lacznik);
        }
    }

    document.appendChild(root);
    QTextStream stream(&file);
    stream<<document;
    file.close();
}

void Graf::odczyt(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Wczytaj"),"",tr("Plik XML (*xml)"));
    if(fileName == ""){
        return;
    }
    QFile file(fileName);
    if(!(file.open(QIODevice::ReadOnly))){
        return;
    }
    czyszczenie();
    vector<pair<int,int>> pary;
    int sz;
    int wierzch=-1;
    QXmlStreamReader xmlReader(&file);
    while(!xmlReader.atEnd()){

        xmlReader.readNext();
        if(xmlReader.name() == "Wierzcholek" && xmlReader.attributes().hasAttribute("polozenie")){
                   wierzch++;
            QString pos = xmlReader.attributes().value("polozenie").toString();
            QStringList posList = pos.split(',');
            QString x = posList.at(0);
            QString y = posList.at(1);
            dodaj(x.toInt(),y.toInt()-20);
        }
        if(xmlReader.name() == "lacznik"){
            sz=xmlReader.readElementText().toInt();
            if(sz<wierzch)
            {
                pary.push_back({sz,wierzch});
            }
            else
            {
                pary.push_back({wierzch,sz});
            }
        }
       }
    file.close();
    sort(pary.begin(), pary.end(),porownanie);
    int pier=-1;int dr=-1;
    while(pary.empty()==0)
    {

        if(pier!=(*pary.begin()).first || dr!=(*pary.begin()).second)
        {
        //qDebug()<<(*pary.begin()).first<<(*pary.begin()).second;
        polacz((*pary.begin()).first,(*pary.begin()).second);
        pier=(*pary.begin()).first;
        dr=(*pary.begin()).second;
        }
        pary.erase(pary.begin());
    }

    repaint();
}

bool Graf::test(bool uz[])
{
    for(int i=0; i<elementy.size(); i++)
    {
        if(uz[i]==0)
        {
            return 0;
        }
    }
    return 1;
}


void Graf::bfs()
{
    QPainter painter;
    priority_queue < int,vector<int>,greater<int>> kolejka;
    queue < int > stos;

    bool uzyte[elementy.size()];
    for(int i=0; i<elementy.size(); i++)uzyte[i]=0;
    stos.push(0);
    list<Element>::iterator temp;
    while(test(uzyte)==0&&stos.empty()==0)
    {
        //cout<<endl<<"Wchodze"<<endl;
        while(uzyte[stos.front()]==1&&stos.empty()==0)
        {
            stos.pop();
        }
        if(stos.empty()==0)
        {
            temp=elementy.begin();
            for(int i=0; i<stos.front(); i++)temp++;
            //cout<<"Nastêpny: "<<(*temp).nr<<endl;

            uzyte[(*temp).nr]=1;
            aktywator=(*temp).nr;
            repaint();
            for(int i=0; i<(*temp).nast.size(); i++)
            {
                kolejka.push((*temp).nast[i]->nr);

            }
            for(int i=0; !kolejka.empty(); i++)
            {
                stos.push(kolejka.top());
                //cout<<endl<<"Na stos idzie:"<<kolejka.top();
                kolejka.pop();
            }
            //cout<<endl<<"Wartosc stosu: "<<stos.top();
        }
    }
sleep(1);
update();
}

void Graf::dfs()
{
    priority_queue <int> kolejka;
    stack < int > stos;

    bool uzyte[elementy.size()];
    for(int i=0; i<elementy.size(); i++)uzyte[i]=0;
    stos.push(0);
    list<Element>::iterator temp;
    while(test(uzyte)==0&&stos.empty()==0)
    {

      //  cout<<endl<<"Wchodze"<<endl;
        while(stos.empty()==0&&uzyte[stos.top()]==1)
        {
           // cout<<endl<<"Wchodze2";
            stos.pop();
           // cout<<"good"<<endl;
        }
        //cout<<endl<<"Wchodze3"<<endl;
        if(stos.empty()==0)
        {
            temp=elementy.begin();

            for(int i=0; i<stos.top(); i++)temp++;
            aktywator=(*temp).nr;
            repaint();
            uzyte[(*temp).nr]=1;
            for(int i=0; i<(*temp).nast.size(); i++)
            {
                kolejka.push((*temp).nast[i]->nr);
            }
            for(int i=0; !kolejka.empty(); i++)
            {
                stos.push(kolejka.top());
            //    cout<<endl<<"Na stos idzie:"<<kolejka.top();
                kolejka.pop();
            }
          //  cout<<endl<<"Wartosc stosu: "<<stos.top();
        }
    }
    sleep(1);
    update();

}

void Graf::zmien(int x, int y, int pier)
{
    list<Element>::iterator it=elementy.begin();
    for(int i=0; i<pier; i++)
    {
        it++;
    }
    if(x<=25)
    {
        x=25;
    }
    else if(x>=(int)(dw.height()*0.8)-40)
    {
        x=(int)(dw.height()*0.8)-40;
    }
    if(y<=55)
    {
        y=55;
    }
    else if(y>=(int)(dw.width()*0.8)-40)
    {
        y=(int)(dw.width()*0.8)-40;
    }
    (*it).x=x;
    (*it).y=y;
    update();
}
void Graf::zmiana()
{
    int pier = QInputDialog::getInt(this, tr("Zmiana"), tr("Którego wierzchołka współrzędne chcesz zmienić?"), 0, 0, 1000, 1,nullptr);
    int x = QInputDialog::getInt(this, tr("Zmiana"), tr("Podaj nr nowej współrzędnej X"), 0, 0, 1000, 1,nullptr);
    int y = QInputDialog::getInt(this, tr("Zmiana"), tr("Podaj nr nowej współrzędnej Y"), 0, 0, 1000, 1,nullptr);
    zmien(x,y,pier);
}

void Graf::mousePressEvent(QMouseEvent *event){
    //qDebug()<<event->pos().rx()<<event->pos().ry();
    xmyszy=event->pos().rx();
    ymyszy=event->pos().ry();
    if(event->buttons() == Qt::RightButton)
    {
       // qDebug()<<"Prawy";
    //i++;
    int x = event->pos().rx();
    int y = event->pos().ry();
    myszowelaczenie();
    }
}

void Graf::mysz(int x, int y){
            //qDebug()<<"wiec";
    bool warunek{0};
    list<Element>::iterator it;
    for(it=elementy.begin(); it!=elementy.end(); it++){
        double temp{(double)(pow(xmyszy-(*it).x,2))+(double)(pow(ymyszy-(*it).y,2))};
        if(temp<pow(40, 2))
        {
            warunek = 1;
            break;
        }
    }
    if(warunek==1){
        //qDebug()<<"O dziwo, jest tu";
        (*it).x = xmyszy;
        (*it).y = ymyszy;
        xmyszy=x;
        ymyszy=y;
        update();
    }
    //qDebug()<<"KOniec";
}

void Graf::myszowelaczenie(){
            //qDebug()<<"wiec";
    bool warunek{0};
    list<Element>::iterator it;
    for(it=elementy.begin(); it!=elementy.end(); it++){
        double temp{(double)(pow(xmyszy-(*it).x,2))+(double)(pow(ymyszy-(*it).y,2))};
        if(temp<pow(40, 2))
        {
            warunek = 1;
            break;
        }
    }
    if(warunek==1){
        if(lacz1==-1)
        {
            lacz1=(*it).nr;
            //qDebug()<<"aktywacja 1.: "<<lacz1;
            return;
        }
        else {
           if(lacz2==-1)
           {
               lacz2=(*it).nr;
               //qDebug()<<"aktywacja 2.: "<<lacz2;
               //qDebug()<<"Akcja"<<lacz1<<lacz2;
               if(lacz1!=lacz2)
               {polacz(lacz1,lacz2);
               update();
               lacz1=-1;lacz2=-1;}
               else
               lacz2=-1;
           }
        }

    }
    //qDebug()<<"KOniec";
}
