#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QPainter"
#include "QPainterPath"
#include "math.h"
#include "QPen"
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    button->setGeometry(width()/2+245, height()/2+200, 150, 50);
    button->setText("Нажми");
    connect(button, SIGNAL(clicked()), this, SLOT(mybuttonclik()));
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString s1 = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_2_editingFinished()
{
    QString xma = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_3_editingFinished()
{
    QString xmi = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_4_editingFinished()
{
    QString yma = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_5_editingFinished()
{
    QString ymi = ui->lineEdit->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mybuttonclik(){
    QString s1 = ui->lineEdit->text();
    QString xma = ui->lineEdit_2->text();
    QString xmi = ui->lineEdit_3->text();
    QString yma = ui->lineEdit_4->text();
    QString ymi = ui->lineEdit_5->text();



    double xmax, xmin;
    double ymax, ymin;
    if (xma == "") xmax = 10; else xmax =  xma.toDouble();
    if (xmi == "") xmin = -10; else xmin = xmi.toDouble();
    if (yma == "") ymax = 1; else ymax =  yma.toDouble();
    if (ymi == "") ymin = -1; else ymin = ymi.toDouble();

    ui->label->setGeometry(5, 5, width() -5 -5 -5 - button->width(), height() - 5 - 5);
    QPixmap pm(width() -5 -5 -5 - button->width(), height() - 5 - 5);

    QPainter painter;
    painter.begin(&pm);
    QPainterPath path;
    QPen pen;

    pen.setColor(Qt::red);
    painter.setPen(pen);

    pm.fill(Qt::white);



    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double step = (xmax - xmin)/(xgmax - xgmin);

    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;

    painter.drawLine(0, y0, xgmax, y0);
    painter.drawLine(x0, 0, x0, ygmax);
    painter.setPen(Qt::black);
    bool check = true;

    for (double x = xmin; x <= xmax; x += step){
        QString tp = s1;
        tp.replace("x", "(" + QString().setNum(x, 'G', 8) + ")");
        double y = 0.0;
        bool g = calculate(tp.toStdString(), y);
        if (y <= ymax && y >= ymin && g){
            int xg = xgmin + kx * (x - xmin);
            int yg = ygmin + ky * (y - ymax);

            if(check == true){
                path.moveTo(xg, yg);
                check = false;
            }
            else{
                path.lineTo(xg, yg);
            }
        }
        else{
            check = true;}
    }

    painter.drawPath(path);
    ui->label->setPixmap(pm);

}

