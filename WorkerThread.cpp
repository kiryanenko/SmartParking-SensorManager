#include "WorkerThread.h"


WorkerThread::WorkerThread(ReceiverTransmitter *receiverTransmitter) :
    m_receiverTransmitter(receiverTransmitter)
{
}


void WorkerThread::run()
{
    while (true) {
        m_receiverTransmitter->handleRecieveMessages();
        msleep(300);
    }
}
