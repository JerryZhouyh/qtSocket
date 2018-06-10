#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void socket_send_data();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
private slots:
    void socketReadData();
    void socketDisconnected();
    void sever_new_connect();
    void on_btn_listen_clicked();
    void on_btn_send_clicked();
};

#endif // MAINWINDOW_H
