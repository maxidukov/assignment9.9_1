#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{

    QByteArray data;
    data = datagram.data();
    QHostAddress senderAddress = datagram.senderAddress();
    qint64 datagramSize= data.size();

    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    QString str;
    inStr >> str;
    //dateTime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
    if(str.isEmpty()){
    //if(dateTime.isValid()){
        QDataStream inStr(&data, QIODevice::ReadOnly);
        inStr >> dateTime;
        emit sig_sendTimeToGUI(dateTime);
    }else{
        //qDebug() << "String sent is " << str;
        str = "Принято сообщение от " + senderAddress.toString() + ", размер сообщения(байт) " + QString::number(datagramSize) + ":\n" + str;
        emit sig_sendTextToGUI(str);
    }
}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }

}
