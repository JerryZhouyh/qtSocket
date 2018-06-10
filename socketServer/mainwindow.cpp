
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_port->setText("8076");
    ui->btn_send->setEnabled(false);
    server = new QTcpServer();

    connect(server,&QTcpServer::newConnection,this,&MainWindow::sever_new_connect);
}

MainWindow::~MainWindow()
{
    server->close();
    server->deleteLater();
    delete ui;
}

void MainWindow::socketReadData()
{
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty()){
        QString str = ui->textEdit_receive->toPlainText();
        str +=tr(buffer);
        ui->textEdit_receive->setText(str);
    }
}

void MainWindow::socketDisconnected()
{
    ui->btn_send->setEnabled(false);
}

void MainWindow::sever_new_connect()
{
    socket = server->nextPendingConnection();
    QObject::connect(socket,&QTcpSocket::readyRead,
                     this,&MainWindow::socketReadData);
    QObject::connect(socket, &QTcpSocket::disconnected,
                     this, &MainWindow::socketDisconnected);
    ui->btn_send->setEnabled(true);
}

void MainWindow::on_btn_listen_clicked()
{
    if(ui->btn_listen->text() == tr("监听")){
        int port = ui->lineEdit_port->text().toInt();
        if(!server->listen(QHostAddress::Any,port)){
            qDebug()<<server->errorString();
            return;
        }
        ui->btn_listen->setText("取消监听");
        qDebug()<<"listen successfully!!";
    }else{
        if(socket->state()==QAbstractSocket::ConnectedState){
            socket->disconnectFromHost();
        }
        server->close();
        ui->btn_listen->setText("监听");
        ui->btn_send->setEnabled(false);
        qDebug()<<"cancel listen sucessful!!";
    }


}

void MainWindow::on_btn_send_clicked()
{
    socket->write(ui->textEdit_send->toPlainText().toLatin1());
    socket->flush();
}
