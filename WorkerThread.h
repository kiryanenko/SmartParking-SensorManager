#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "ReceiverTransmitter.h"

class WorkerThread : public QThread
{
    Q_OBJECT

    ReceiverTransmitter *m_receiverTransmitter;

public:
    WorkerThread(ReceiverTransmitter *receiverTransmitter);

private:
    void run();
};

#endif // WORKERTHREAD_H
