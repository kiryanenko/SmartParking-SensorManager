#include <QCoreApplication>
#include <iostream>
#include "SerialConnection.h"
#include "ReceiveMessageHandler.h"

using namespace std;

enum COMMANDS {
    HELP = 'h',
    RESERVE = 'r',
    CANCEL_RESERVARVATION = 'c',
    SET_SENSOR_ID = 'i',
    SET_SAMPLING_PERIOD = 's',
    SET_SENDING_PERIOD = 'p',
    QUIT = 'q'
};

void printHelp()
{
    cout << "Commands:" << endl;
    cout << "h - show help" << endl;
    cout << "r - send message to reserve parking place" << endl;
    cout << "c - send message to cancel reservation of parking place" << endl;
    cout << "i - send message to set sensor id" << endl;
    cout << "s - send message to set sensor sampling period" << endl;
    cout << "p - send message to set sensor sending period" << endl;
    cout << "q - quit" << endl;
}

void reserve(ReceiverTransmitter *receiverTransmitter) {
    cout << "Enter sensor id: ";
    uint32_t sensorId;
    cin >> sensorId;

    cout << "Enter parking place id: ";
    quint16 parkingPlaceId;
    cin >> parkingPlaceId;

    cout << "Enter time reservation (sec): ";
    uint16_t time;
    cin >> time;

    receiverTransmitter->sendReserve(sensorId, parkingPlaceId, time);
}

void cancelReservation(ReceiverTransmitter *receiverTransmitter) {
    cout << "Enter sensor id: ";
    uint32_t sensorId;
    cin >> sensorId;

    cout << "Enter parking place id: ";
    quint16 parkingPlaceId;
    cin >> parkingPlaceId;

    receiverTransmitter->sendCancelReservation(sensorId, parkingPlaceId);
}

void setSensorId(ReceiverTransmitter *receiverTransmitter) {
    cout << "Enter sensor id: ";
    uint32_t sensorId;
    cin >> sensorId;

    cout << "Enter new id: ";
    uint32_t newId;
    cin >> newId;

    receiverTransmitter->sendSetId(sensorId, newId);
}

void setSamplingPeriod(ReceiverTransmitter *receiverTransmitter) {
    cout << "Enter sensor id: ";
    uint32_t sensorId;
    cin >> sensorId;

    cout << "Enter sensor sampling period (ms): ";
    uint16_t period;
    cin >> period;

    receiverTransmitter->sendSetSensorSamplingPeriod(sensorId, period);
}

void setSendingPeriod(ReceiverTransmitter *receiverTransmitter) {
    cout << "Enter sensor id: ";
    uint32_t sensorId;
    cin >> sensorId;

    cout << "Enter period (ms) that sensor will be send data: ";
    uint16_t period;
    cin >> period;

    receiverTransmitter->sendSetSendingPeriod(sensorId, period);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Enter port name: ";
    string inputStr;
    cin >> inputStr;

    auto *handler = new ReceiveMessageHandler();
    ReceiverTransmitter *receiverTransmitter = new SerialConnection(inputStr.c_str(), handler);

    printHelp();
    char cmd;
    do {
        cout << "Enter command or q to quit: ";
        cin >> cmd;

        switch (cmd) {
        case HELP:
            printHelp();
            break;
        case RESERVE:
            reserve(receiverTransmitter);
            break;
        case CANCEL_RESERVARVATION:
            cancelReservation(receiverTransmitter);
            break;
        case SET_SENSOR_ID:
            setSensorId(receiverTransmitter);
            break;
        case SET_SAMPLING_PERIOD:
            setSamplingPeriod(receiverTransmitter);
            break;
        case SET_SENDING_PERIOD:
            setSendingPeriod(receiverTransmitter);
            break;
        case QUIT:
            cout << "Quit." << endl;
            break;
        default:
            cout << "The command not found." << endl;
            printHelp();
            break;
        }
    } while (cmd != QUIT);

    delete receiverTransmitter;
    delete handler;
    return a.exec();
}
