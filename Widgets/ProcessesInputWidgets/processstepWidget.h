#ifndef PROCESSSTEPWIDGET_H
#define PROCESSSTEPWIDGET_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The processstepWidget is a object which displays information about a single processstep

*/

// Global includes
#include <QWidget>
#include <QDebug>

// Local includes
#include "DataTypes/processstep.h"
#include "Widgets/ProcessesInputWidgets/parameterwidget.h"
#include "Widgets/ProcessesInputWidgets/streamselectwidget.h"

namespace Ui {
    class ProcessStepWidget;
}

class ProcessStepWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProcessStepWidget( ProcessStep* processStep, QWidget *parent = 0);
    ~ProcessStepWidget();

    void setName(QString name);
    void setColor( QColor color );
    
    void setParameter(QString parameter, QString value);

signals:
    void illegalUpdate( QString message );
    void valueChanged( QString processStepName, QString parameterName, QString value);

private slots:
    void valueChangedOfChild(QString name, QString value);
    void illegalUpdateOfChild(QString message);

private:
    Ui::ProcessStepWidget *ui;
    QString _styleSheet;
    StreamSelectWidget* _inputStreamWidget;
    StreamSelectWidget* _outputStreamWidget;

    void setParameters( ProcessStep* processStep );
    void createParameter( AbstractParameter* parameter );
};

#endif // PROCESSSTEPWIDGET_H
