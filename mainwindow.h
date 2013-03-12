#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTimer>
#include <QSharedPointer>
#include "cmdfieldsmodel.h"
#include "errors.h"
#include "packet.h"
#include "dumpmodel.h"

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
    DumpModel dumpModel;
    CmdFieldsModel model;
    QHostAddress ip;
    quint16 localPort, remoutePort;
    bool circle;
    QUdpSocket udpSocket;
    CmdFieldsDelegate delegate;
    QSharedPointer<Packet> packet;
    QTimer timer;
    QByteArray datagram;
private slots:
    void on_packetNumber_valueChanged(int );
    void on_delBlock_clicked();
    void on_addBlock_clicked();
    void on_send_clicked(bool checked);
    void on_circle_clicked(bool checked);
    void on_Connect_clicked(bool checked);
    void on_remoutePort_textEdited(QString );
    void on_localPort_textEdited(QString );
    void on_ip_lostFocus();
    void dataChanged();
    void processPendingDatagrams();
    void processSendingDatagrams();
};

#endif // MAINWINDOW_H
