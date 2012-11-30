#include "datasendsocket.h"

DataSendSocket::DataSendSocket(QObject *parent) :
    QUdpSocket(parent)
{

}
void DataSendSocket::connectToServer( QHostAddress hostAdress, quint16 port )
{
    //Close current connection
    close();

    //Try to connect
    connectToHost( hostAdress, port, QIODevice::WriteOnly );

    //Check if succes
    if( state() )
    {
        emit print("Connected succesfully to" + peerAddress().toString() + " on port " + QString::number( peerPort() ) );
        emit connectionSucces();
    }
    else
    {
        print("Connection failed");
        emit connectionFailed();
    }
}
void DataSendSocket::setParameter(QString processStep, QString parameter, QString value)
{
    using namespace clientServerProtocol;
    QString command = QString( "%1;%2;%3").arg(processStep).arg(parameter).arg(value);

    QByteArray commandInBytes = createDatagram( command );
    int length = commandInBytes.length();
    commandInBytes.prepend( length );

    writeDataToServer( SET_PARAMETER, commandInBytes );
}
void DataSendSocket::sendImage( QImage* image, int streamID )
{
   // QByteArray announceImage = QByteArray("<image>");
   // writeData( announceImage );
    using namespace clientServerProtocol;
    for( int i = 0; i < image->height(); i++ )
    {
        // !!!!-- Probably highly dangerous code --!!!! ////
        QByteArray scanLine = QByteArray( (char*) image->scanLine(i) );
        writeDataToServer( IMAGE_DATA, scanLine );
    }

    //QByteArray closeImage = QByteArray("</image>");
    // writeData( closeImage );
}

void DataSendSocket::sendCommand(QString command)
{
    using namespace clientServerProtocol;
    writeDataToServer( UNFORMATTED_COMMAND, command.toAscii() );
}

void DataSendSocket::getImage(clientServerProtocol::imageTypes type, int streamID, bool continous)
{
    qDebug() << type << streamID << continous ;

    QByteArray datagram;
    datagram.append( (char) streamID  );
    datagram.append( (char) type );

    if( continous )
    {
        datagram.append( clientServerProtocol::getImage::CONTINOUS );
    }
    else
    {
        datagram.append( clientServerProtocol::getImage::SINGLE_SHOT );
    }

    writeDataToServer( clientServerProtocol::GET_IMAGE, datagram );
}

void DataSendSocket::writeDataToServer( clientServerProtocol::clientDataTypes type, QByteArray datagram)
{
    int typeID = type;

    datagram.prepend( typeID );
    datagram.append( "\0" );

    write( datagram );

    print( QString("Sent %1 bytes to server").arg( datagram.size() ) );
}

QByteArray DataSendSocket::createDatagram(QString command)
{
    QByteArray datagram = QByteArray( command.toAscii() );

    return datagram;
}