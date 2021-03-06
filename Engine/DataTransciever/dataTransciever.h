#ifndef DATATRANSCIEVER_H
#define DATATRANSCIEVER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The dataTransciever setups the connection with the server and keeps listening in a seperate thread for incoming messages.

*/



// Global includes
#include <QObject>
#include <QImage>

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>

#include <QFile>
#include <QByteArray>
#include <QByteRef>

#include "DataTypes/ClientServerProtocol.h"
#include "DataTypes/ImageTypes/allimagetypes.h"

#include "datareceivesocket.h"
#include "datasendsocket.h"

class DataTransciever : public QObject
{
    Q_OBJECT
public:
    explicit DataTransciever(QObject *parent = 0);


signals:
    void printToConsole( QString sender, QString message );

    void connectionSucces();
    void connectionFailed();

    void parameterReceived( QString processStep, QString parameter, QString value);
    void imageDataReceived( QByteArray datagram );
    void xmlDataReceived( QFile* file );

    void dataRate( int received, int sent);
    
public slots:

    //Connection methods
    void connectToServer( QHostAddress hostAdress, quint16 port = 7755 );

    //Send methods
    void sendCommand( QString command );
    void setParameter( QString processStep, QString parameter, QString value);
    void sendImage( int streamID, AbstractImageFrame* image);
    void sendImage( QImage* image, int streamID);

    void getImage(int streamID, bool continous);
    void byteCounter( int count );

    void requestXML();

private slots:

    void print( QString message );

private:
    DataReceiveSocket* _receiveSocket;
    DataSendSocket* _sendSocket;

};

#endif // DATATRANSCIEVER_H
