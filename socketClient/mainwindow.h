#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
private slots:
    void socket_Read_Data();
    void socket_Disconnected();
    void on_btn_connect_clicked();
    void on_btn_sende_clicked();
};

#endif // MAINWINDOW_H
