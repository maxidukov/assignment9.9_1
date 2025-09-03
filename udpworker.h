#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345

enum dataType{

    textType = 0,
    dateTimeType  = 1,

};

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data, int dataType);


private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket;
    int _dataType = textType;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString text);

};

#endif // UDPWORKER_H
