#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_textBrowser_anchorClicked(const QUrl &arg1);

    void on_Circle_radius_set_textChanged(const QString &arg1);

    void on_Circle_x_set_textChanged(const QString &arg1);

    void on_Circle_y_set_textChanged(const QString &arg1);

    void on_Line_x1_set_textChanged(const QString &arg1);

    void on_Line_y1_set_textChanged(const QString &arg1);

    void on_Line_x2_set_textChanged(const QString &arg1);

    void on_Line_y2_set_textChanged(const QString &arg1);

    void on_TEST_CHECK_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    double x0,y0,x1,y1,x2,y2,r;
};
#endif // MAINWINDOW_H
