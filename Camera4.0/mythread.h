#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

#pragma execution_character_set("utf-8") //防止中文乱码

class UIUpdater : public QObject
{
    Q_OBJECT
public:
    explicit UIUpdater(QObject *parent = nullptr);
    ~UIUpdater();

    void working();

private:
    static QString dataFromUpd;
    static int flag;
    QThread workerThread;

public slots:
    void receiveDataFromUdp(const QString& data);

signals:
    void updateUI(const QString& data);
};

#endif // UIUPDATER
