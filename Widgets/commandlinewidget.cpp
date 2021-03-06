#include "commandlinewidget.h"
#include "ui_commandlinewidget.h"

CommandLineWidget::CommandLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandLineWidget)
{
    ui->setupUi(this);
    this->setFocusPolicy( Qt::StrongFocus );
    ui->commandLE->installEventFilter(this);
    _commandIndex = -1;
}

CommandLineWidget::~CommandLineWidget()
{
    delete ui;
}

void CommandLineWidget::on_commandPB_clicked()
{
    sendCommand();
}

// Catch key presses
bool CommandLineWidget::eventFilter(QObject* obj, QEvent* event)
{
    if( obj == ui->commandLE )
    {
        if( event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            switch( keyEvent->key() )
            {
             case Qt::Key_Up:
                _commandIndex++;

                if(_commandIndex > _commandHistory.count())
                {
                    _commandIndex = 0;
                }

                setOldCommand();
                return true;

             case Qt::Key_Down:
                _commandIndex--;

                if(_commandIndex < 0)
                {
                    _commandIndex = _commandHistory.count();
                }

                setOldCommand();
                return true;

            case Qt::Key_Return:
                sendCommand();
                return true;

            default:
                break;
            }
        }
        return false;
    }
    return CommandLineWidget::eventFilter(obj, event);
}

void CommandLineWidget::setOldCommand()
{
    if( (_commandIndex >= 0) && ( _commandIndex < _commandHistory.count() ) )
    {
        ui->commandLE->setText( _commandHistory.at( _commandIndex ) );
    }
}
void CommandLineWidget::addCommandToHistory()
{
    //Check if command already exists
    QString newCommand = ui->commandLE->text();

    for(int i = 0; i < _commandHistory.count() ; i++ )
    {
        if( newCommand == _commandHistory.at(i) )
        {
           _commandHistory.removeAt(i);
        }
    }

    //Add command in front
    _commandHistory.prepend( ui->commandLE->text() );

    //If more than maxsize delete last one
    if ( _commandHistory.size() > 100 )
    {
        _commandHistory.pop_back();
    }
}

void CommandLineWidget::sendCommand()
{
    if (ui->commandLE->text().count() > 0)
    {
        addCommandToHistory();
        parseCommand();
        //emit executeCommand( ui->commandLE->text() );

        ui->commandLE->clear();
    }

    _commandIndex = -1;
}
void CommandLineWidget::focusInEvent(QFocusEvent *)
{
    //If the commandline widget gets focus, it gives focus to the line edit
    ui->commandLE->setFocus();
}
void CommandLineWidget::parseCommand()
{
    QStringList commandParts = splitCommandInArguments( lastCommand() );

    if ( firstPartIs( "Preview" ) )
    {
        if( commandParts.count() == 4 )
        {
            QString processStep = commandParts.at(1);
            QString streamName = commandParts.at(2);
            int channelId = commandParts.at(3).toInt();

            commandParseStatus(" Previewing " + streamName + " of processStep " + processStep + " on channel " + QString::number(channelId) , true);
            emit subscribeToStream( channelId, processStep, streamName, false );
            return;
        }
        else
        {
            QString message = "Error parsing command:  <br>Command should be structured like following:";
            message.append(" <br> preview &lt;processStep&gt; &lt;streamname&gt; &lt;channelNumber&gt;");
            commandParseStatus(message,false);
        }
    }

    if( firstPartIs("set") )
    {
        if( commandParts.count() == 4)
        {
            commandParseStatus("set " + commandParts.at(1) +" "+ commandParts.at(2) +" "+ commandParts.at(3) , true);
            emit set( commandParts.at(1), commandParts.at(2), commandParts.at(3) );
            return;
        }
        else
        {
            QString message = "Error parsing command:  <br>Command should be structured like following:";
            message.append(" <br> Set &lt;processStep&gt; &lt;parameter&gt; &lt;value&gt;");
            commandParseStatus(message,false);
        }
    }
    if ( firstPartIs("save") )
    {
        if ( equals( commandParts.at(1), "preview") )
        {
            commandParseStatus("Preview Saved", true);
            return;
        }
        if ( equals( commandParts.at(1), "log") )
        {
            emit saveLog();
            commandParseStatus("Log Saved", true);
            return;
        }
        else
        {
            commandParseStatus("Error parsing command: <br>Save must always be followed by either &quot;preview&quot; or &quot;log&quot;" ,false);
        }
    }

    if ( firstPartIs("view") )
    {
        if( commandParts.at(1).toInt() > 0 )
        {
            commandParseStatus("Setting preview mode to 2 views",true);
            return;
        }
    }

    if ( firstPartIs("s2s") )
    {
        QString command;

        for( int i = 1; i < commandParts.size(); i++ )
        {
            if( i == commandParts.size() - 1)
            {
                command.append( commandParts.at(i) );
            }
            else
            {
                command.append( commandParts.at(i) + " " );
            }
        }

        commandParseStatus("Sending to server  """ + command + """", true );
        emit sendCommandToServer( command );
        return;
    }
    //commandParseStatus( lastCommand(),false);
    emit commandForGui( lastCommand() );
}
QStringList CommandLineWidget::splitCommandInArguments( QString command )
{
    QStringList commandParts;

    if( command.contains("\"") )
    {
        commandParts = command.split( QRegExp(" "), QString::SkipEmptyParts );

        bool partToJoin = false;
        for( int i = 0; i < commandParts.count(); i++ )
        {
            if( commandParts.at(i).contains( "\"") )
            {
               partToJoin = !partToJoin;
            }
            if( !partToJoin )
            {
                i++;
                commandParts.insert(i, ",");
            }
            else
            {
                i++;
                commandParts.insert(i, " ");
            }
        }

        QString commaSeparatedCommand = commandParts.join("");
        commandParts = commaSeparatedCommand.split(",", QString::SkipEmptyParts);
        commandParts.replaceInStrings( QString("\""),QString("") );
    }
    else
    {
        commandParts = command.split(" ");
    }
    return commandParts;

}

bool CommandLineWidget::equals( QString string1, QString string2, Qt::CaseSensitivity sensitivity)
{
    return QString::compare( string1, string2, sensitivity) == 0;
}
bool CommandLineWidget::firstPartIs( QString command )
{
    QStringList commandParts = lastCommand().split(" ");

    return equals( commandParts.first(), command );
}
QString CommandLineWidget::lastCommand()
{
    return _commandHistory.first();
}
void CommandLineWidget::commandParseStatus( QString message, bool succesfull )
{
    if(succesfull)
    {
        message.prepend("<font color=\"green\">>>");
    }
    else
    {
        message.prepend("<font color=\"red\">>>");
    }
    message.append("</font>");

    emit printToConsole("CommandLine", message );
}

