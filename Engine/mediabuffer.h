#ifndef MEDIABUFFER_H
#define MEDIABUFFER_H

// Global includes
#include <QObject>
#include <QImage>
#include <deque>

// Local includes
#include "DataTypes/ClientServerProtocol.h"
#include "DataTypes/ImageTypes/allimagetypes.h"
#include "Widgets/PreviewWidget/previewwindowconfig.h"

class MediaBuffer : public QObject
{
    Q_OBJECT

public:
    explicit MediaBuffer(QObject *parent = 0);
    
    void initImageBuffers();

signals:
    void imageReceived( QImage image, int channel);
    void print( QString message );

public slots:
    void processImageDatagram( QByteArray datagram );
    void subscribeChannelToStream( int channelID, int streamID);
    void flushBuffers();

private:
    QList< int > _subscriptions;

    std::deque< AbstractImageFrame* > _imageBuffer;

    void resetBuffer(int channelID);
    void addFrame(clientServerProtocol::imageTypes type, quint8 streamId, quint8 frameID, QByteArray data);
};

#endif // MEDIABUFFER_H
