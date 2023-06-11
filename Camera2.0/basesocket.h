#ifndef BASESOCKET_H
#define BASESOCKET_H

#include <QObject>

class BaseSocket : public QObject
{
    Q_OBJECT
public:
    explicit BaseSocket(QObject *parent = nullptr);

    virtual void connect() = 0;
    //virtual bool connect() = 0;
    //virtual QString getServerKey() = 0;
    virtual void write() = 0;
    virtual bool closeSocket() = 0;

private:
    QString mServerAddress;
    uint16_t mServerPort;
};


#endif // BASESOCKET_H
