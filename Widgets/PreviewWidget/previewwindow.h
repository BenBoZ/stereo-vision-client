#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMenu>
#include <QVariant>

#include "previewchannel.h"
#include "previewwindowconfig.h"



namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = 0);
    ~PreviewWindow();

    void resizeEvent(QResizeEvent *);

    void reset();
signals:
    void subscribeToStream( int previewChannel, QString procesStep, QString streamName, bool continous);
    void replaceStreamRequest( QString processStep, QString streamName, QImage* image);
    void flushBuffers();

    void print( QString message );

public slots:
    void addPreviewStream( QString processStep, QString streamName);
    void zoomToNumberOfChannels(int number);    
    void imageForChannel(QImage image, int channelID);

private slots:
    void on_modeCB_currentIndexChanged(int index);

private:
    void disableScrollBars();

    void initChannelCountBox();
    void initPreviewScene();
    void initPreviewChannels();
    void initMenuBar();

    void selectChannels(QList<int> channelIDs);

    Ui::PreviewWindow *ui;
    QGraphicsScene* _previewScene;

    QList< PreviewChannel* > _previewChannels;
};

#endif // PREVIEWWINDOW_H
