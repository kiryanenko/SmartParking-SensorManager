#include "ReceiverTransmitter.h"

#include <QDataStream>

ReceiverTransmitter::ReceiverTransmitter(AbstractReceiveMessageHandler* handler) :
	m_handler(handler)
{
}

ReceiverTransmitter::~ReceiverTransmitter()
{
}

void ReceiverTransmitter::handleRecieveMessages()
{
    while (available()) {
        size_t size;
        const uint8_t *msg = recv(size);
        if (msg) {
            m_handler->onRecv(msg, size);
            // TODO: Реализовать дальнейшую обработку
            delete[] msg;
        }
    }
}

void ReceiverTransmitter::sendSetId(uint32_t currentId, uint32_t newId)
{
    QByteArray dataToSend;
    QDataStream stream(&dataToSend, QIODevice::WriteOnly);

    stream << currentId << type_of_send_msg_set_id << newId;
    send((uint8_t*) dataToSend.data(), dataToSend.size());
}

void ReceiverTransmitter::sendSetSensorSamplingPeriod(uint32_t sensorId, uint16_t samplingPeriod)
{
    QByteArray dataToSend;
    QDataStream stream(&dataToSend, QIODevice::WriteOnly);

    stream << sensorId << type_of_send_msg_set_sensor_sampling_period << samplingPeriod;
    send((uint8_t*) dataToSend.data(), dataToSend.size());
}

void ReceiverTransmitter::sendSetSendingPeriod(uint32_t sensorId, uint16_t sendingPeriod)
{
    QByteArray dataToSend;
    QDataStream stream(&dataToSend, QIODevice::WriteOnly);

    stream << sensorId << type_of_send_msg_set_sending_period << sendingPeriod;
    send((uint8_t*) dataToSend.data(), dataToSend.size());
}

void ReceiverTransmitter::sendReserve(uint32_t sensorId, uint8_t parkingPlaceId, uint16_t time)
{
    QByteArray dataToSend;
    QDataStream stream(&dataToSend, QIODevice::WriteOnly);

    stream << sensorId << type_of_send_msg_reserve << parkingPlaceId << time;
    send((uint8_t*) dataToSend.data(), dataToSend.size());
}

void ReceiverTransmitter::sendCancelReservation(uint32_t sensorId, uint8_t parkingPlaceId)
{
    QByteArray dataToSend;
    QDataStream stream(&dataToSend, QIODevice::WriteOnly);

    stream << sensorId << type_of_send_msg_cancel_reservation << parkingPlaceId;
    send((uint8_t*) dataToSend.data(), dataToSend.size());
}
