#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    ui->lineEdit_IP->setText("127.0.0.1");
    ui->lineEdit_port->setText("8076");
    QObject::connect(socket,&QTcpSocket::readyRead,this,&MainWindow::socket_Read_Data);
    QObject::connect(socket,&QTcpSocket::disconnected,this,&MainWindow::socket_Disconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::socket_Read_Data()
{
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty()){
        QString str = ui->textEdit_recive->toPlainText();
        str +=tr(buffer);
        ui->textEdit_recive->setText(str);
    }
}

void MainWindow::socket_Disconnected()
{
    ui->btn_sende->setEnabled(false);
    ui->btn_connect->setText("连接");
}

void MainWindow::on_btn_connect_clicked()
{
    if(ui->btn_connect->text() == tr("连接")){
        QString IP;
        int port;
        //获取IP地址
        IP = ui->lineEdit_IP->text();
        //获取端口号
        port = ui->lineEdit_port->text().toInt();
        //取消已经有的连接
        socket->abort();
        socket->connectToHost(IP,port);
        //等待连接成功
        if(!socket->waitForConnected()){
            qDebug()<<"connection failed";
            return;
        }
        qDebug()<<"Connect successfully";
        //发送按键使能
        ui->btn_sende->setEnabled(true);
        //修改连接按键文字
        ui->btn_connect->setText("断开连接");
    }else{
        //断开连接
        socket->disconnectFromHost();
        ui->btn_connect->setText("连接");
        ui->btn_sende->setEnabled(false);
    }
}

void MainWindow::on_btn_sende_clicked()
{
    qDebug()<<"send:"<<ui->textEdit_sender->toPlainText();
    socket->write(ui->textEdit_sender->toPlainText().toLatin1());
    socket->flush();
}
