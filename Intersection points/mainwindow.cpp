#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

inline float sqr(float x)
{
    return x * x;
}

QString intersection_points(float r, float x0, float y0, float x1, float y1,float x2, float y2){
    const float eps = 1e-8;
    float dx01 = x1 - x0, dy01 = y1 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
        float a = sqr(dx12) + sqr(dy12);
        if (fabs(a) < eps)
        {
            return  "The beginning and end of the segment are the same!";
        }
        float k = dx01 * dx12 + dy01 * dy12;
        float c = sqr(dx01) + sqr(dy01) - sqr(r);
        float d1 = sqr(k) - a * c;
        if (d1 < 0)
            return "The line does not intersect with the circle - the segment is outside";
        else if (fabs(d1) < eps)
        {
            float t = -k / a;
            float xi = x1 + t * dx12, yi = y1 + t * dy12;
            return ("A line touches a circle at a point (" + QString::number(xi) + "; " + QString::number(yi) + ")");
            if (t > 0 - eps && t < 1 + eps)
                return "Segment outside, has a common point with a circle";
            else
                return "Segment strictly outside";
        }
        else
        {
            float t1 = (-k + sqrt(d1)) / a, t2 = (-k - sqrt(d1)) / a;
            if (t1 > t2)
                std::swap(t1, t2);
            float xi1 = x1 + t1 * dx12, yi1 = y1 + t1 * dy12;
            float xi2 = x1 + t2 * dx12, yi2 = y1 + t2 * dy12;
            return ("A straight line intersects a circle at two points: ("
                    + QString::number(xi1) + "; "
                    + QString::number(yi1) + ")" + " and "
                    + "(" + QString::number(xi2) + "; "
                    + QString::number(yi2) + ")");
            if (t1 >= 0 - eps && t2 <= 1 + eps)
                if (t1 > 0 - eps && t2 < 1 + eps)
                    return "Segment strictly inside";
                else
                    return "A segment inside, has at least one common point with a circle";
            else if (t2 <= 0 + eps || t1 >= 1 - eps)
                if (t2 < 0 + eps || t1 > 1 - eps)
                    return "Segment strictly outside";
                else
                    return "Segment outside, has a common point with a circle";
            else
                return "A line segment intersects a circle at two points";
        }
}

void MainWindow::on_pushButton_clicked()
{
    r =ui->Circle_radius_set->value();
    x0 = ui->Circle_x_set->value();
    y0 = ui->Circle_y_set->value();
    x1 = ui->Line_x1_set->value();
    y1 = ui->Line_y1_set->value();
    x2 = ui->Line_x2_set->value();
    y2 = ui->Line_y2_set->value();
    ui->TEST_CHECK->setText(intersection_points(r, x0, y0, x1, y1, x2, y2));
}


void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)
{
}

void MainWindow::on_Circle_radius_set_textChanged(const QString &arg1)
{
}


void MainWindow::on_Circle_x_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_Circle_y_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_Line_x1_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_Line_y1_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_Line_x2_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_Line_y2_set_textChanged(const QString &arg1)
{
}

void MainWindow::on_TEST_CHECK_linkActivated(const QString &link)
{
}
