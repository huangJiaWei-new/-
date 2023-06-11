#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class UIUpdater : public QObject
{
    Q_OBJECT
public:
    explicit UIUpdater(QObject *parent = nullptr);
    ~UIUpdater();

private:
    QThread workerThread;

public slots:
    void processData(QString data);

signals:
    void updateUI(QString data);
};

#endif // UIUPDATER
