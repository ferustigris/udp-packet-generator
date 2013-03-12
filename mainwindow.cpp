#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model ("1\t1\t1\t"),
    ip (QHostAddress::Broadcast)
{
	Log::add (Log::LOG_DEBUG,  QString (__FUNCTION__) + " (line " + __LINE__ + "): " + "Main window created");
    ui->setupUi(this);
    ui->dump->setModel(&dumpModel);
    ui->CommandsFields->setModel(&model);
    ui->CommandsFields->setItemDelegate(&delegate);
    localPort = 45454;
    remoutePort = 45455;
    ui->remoutePort->setText(QString::number(remoutePort));
    ui->localPort->setText(QString::number(localPort));
    ui->ip->setText(ip.toString());
    ui->data->setEnabled(false);
    circle = false;
    ui->CommandsFields->setColumnWidth(0, 50);
    ui->CommandsFields->setColumnWidth(1, 50);
    ui->CommandsFields->setColumnWidth(2, 50);
    ui->CommandsFields->setColumnWidth(3, 50);
    ui->CommandsFields->setColumnWidth(4, 590);
    QObject::connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(processSendingDatagrams()));
    QObject::connect(&model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(dataChanged()));
    dataChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!\func
 * lost focus after enter ip
 * \param no
 * \return  no
 */
void MainWindow::on_ip_lostFocus()
{
	QStringList list = ui->ip->text().split('.');
	QString text ("");
	if (list.count() != 4)goto ERROR;
	for (int i = 0; i < 4;i++)
	{
		int section = list[i].toInt ();
		if((section > 255)||(section < 0))goto ERROR;
		text += QString::number(section) + ".";
	}
	text = text.left(text.length() - 1);
	if(text == "127.0.0.1")
	{
		ip.setAddress(QHostAddress::LocalHost);
		return;
	}
	else if(text == "255.255.255.255")
	{
		ip.setAddress(QHostAddress::Broadcast);
		return;
	}
	else
	    ip.setAddress(text);
ERROR:
	ui->ip-> setText(ip.toString());
}
/*!\func
 * change local port
 * \param no
 * \return  no
 */
void MainWindow::on_localPort_textEdited(QString text)
{
	quint16 port = text.toInt();
	if(port)
	{
		localPort = port;
	}
	else ui->localPort->setText(QString::number(localPort));
}
/*!\func
 * change remoute port
 * \param no
 * \return  no
 */
void MainWindow::on_remoutePort_textEdited(QString text )
{
	quint16 port = text.toInt();
	if(port)
	{
		remoutePort = port;
	}
	else ui->remoutePort->setText(QString::number(remoutePort));
}
/*!\func
 * change remoute port
 * \param no
 * \return  no
 */
void MainWindow::on_Connect_clicked(bool checked)
{
	if (checked)
	{
		ui->data->setEnabled(true);
		udpSocket.bind(localPort);
	}
	else
	{
		udpSocket.close();
		ui->data->setEnabled(false);
	}
}
/*!\func
 * send in circle
 * \param no
 * \return  no
 */
void MainWindow::on_circle_clicked(bool checked)
{
	circle = checked;
	ui->send->setCheckable(circle);
}
/*!\func
 * send in circle
 * \param no
 * \return  no
 */
void MainWindow::on_send_clicked(bool checked)
{
	QString value(ui->packet->text());
	value.remove("(").remove(")").remove(" ").remove("[").remove("]").remove("-");
	bool ok;
	int data_index = 0;
	while (value.length()%2)value = "0" + value;
	datagram.resize(value.length()/2);
	for (int i = 0; i < value.length()-1;i+=2)
		datagram[data_index++] = QString("0x" + value[i] + value[i+1]).toInt(&ok, 16);
	if (!circle)
	{
		processSendingDatagrams();
	}
	else
	if (checked)
	{
		ui->circle->setEnabled(false);
		timer.start(ui->frequency->value());
	}
	else
	{
		timer.stop();
		ui->circle->setEnabled(true);
	}
}
/*!\func
 * when user data changed
 * \param no
 * \return  no
 */
void MainWindow::dataChanged()
{
	qint32 id = ui->packetNumber->value();
	packet = QSharedPointer<Packet>(new Packet(id, model.getList()));
	ui->packet->setText(packet->toText());
}
/*!\func
 * send datagrams
 * \param no
 * \return  no
 */
void MainWindow::processSendingDatagrams()
{
    //QByteArray datagram = packet->getBody();
    udpSocket.writeDatagram(datagram, ip, remoutePort);
    dumpModel.add(false, IPacket::getPacket(datagram));
}
/*!\func
 * receive datagrams
 * \param no
 * \return  no
 */
void MainWindow::processPendingDatagrams() {
    static QByteArray datagram;
    static QHostAddress addr;
    static quint16 port;
    while (udpSocket.hasPendingDatagrams()) {
	datagram.resize(udpSocket.pendingDatagramSize());
	udpSocket.readDatagram(datagram.data(), datagram.size(), &addr, &port);
	dumpModel.add(true, IPacket::getPacket(datagram));
    }
}
/*!\func
 * add block
 * \param no
 * \return  no
 */
void MainWindow::on_addBlock_clicked()
{
	model.insertRow(model.rowCount());
	dataChanged();
}
/*!\func
 * remove block
 * \param no
 * \return  no
 */
void MainWindow::on_delBlock_clicked()
{
	QModelIndex index = ui->CommandsFields->selectionModel()->currentIndex();
	model.removeRow(index.row());
	dataChanged();
}
/*!\func
 * remove block
 * \param no
 * \return  no
 */
void MainWindow::on_packetNumber_valueChanged(int )
{
	dataChanged();
}
