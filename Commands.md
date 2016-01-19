# Introduction #

Because the client can be used via the commandline, a list of available commands can be viewed here.
Whenever a command has a part in it in between `< >` that should be replaced by a variable

# Commands #

## GUI ##

> | **maximize**   | Maximizes the window |
|:---------------|:---------------------|
> | **minimize**   | Minimizes the window |
> | **fullscreen** | Sets the window to fullscreen |
> | **close**      | Exits the program    |
> | **TAB `<tabName>`** | Changes view to tab `<tabName>` |

## Processtep ##

> | **`<processStep> <parameter_name> <value>`** | `Sets the <parameter> of the <processStep> to the requested <value> if it is valid and in range` |
|:---------------------------------------------|:-------------------------------------------------------------------------------------------------|

## Previewwindow ##

| **`preview <processStep> <streamname> <channelNumber>`** | `Requests the stream with the name <streamname> of <processStep> and puts it in preview channel <channelNumber>` |
|:---------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------|
| **`save preview <channelNumber> <filePath>`**            | `Tries to save the image in previewchannel <channelNumber> to file in <filePath> `                               |

## Log ##

| **`save log <filePath>`** | `Tries to save the complete log to filePath` |
|:--------------------------|:---------------------------------------------|