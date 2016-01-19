# Software needed #

First of all install the proper software:
  * **Qt SDK** from http://qt-project.org/downloads
  * **SVN client**
    * http://www.Sliksvn.com/en/download (Windows)
    * sudo apt-get subversion (Ubuntu)

# Setup #

## Setup Qt Creator ##

  * Install all the above mentioned software.
  * Open up Qt Creator
  * Go to _Tools > Options > Version Control > Subversion_
  * Specify the install location of your svn client (svn.exe)
    * For example: _C:\Program Files\SlikSvn\bin\svn.exe_
  * Fill out the authentication field
    * Your username is your G-mail address
    * Your password can be found at  _https://code.google.com/hosting/settings_
  * Confirm your settings with _OK_

## Checkout the project ##

  * Now press the _Create Project_ button
  * Select _Project from Version Control_
  * In the right screen select _Subversion Checkout_
  * Press _Choose_
  * Specify the address of the repository field _( https://stereo-vision-client.googlecode.com/svn/trunk )_
  * Specify the folder where your working copy should be stored in _Checkout path_
  * Leave the _Checkout directory_ field unchanged (should be automatically filled with trunk)
  * Press _next_
  * You might be asked for some building parameters, just click next/ok
    * It's also possible that you will get a warning about a user file, it will ask if you want to discard it, which is a good idea, because it's my Ubuntu user file.
  * The project should be downloaded.
  * When you press the play icon in the lower left corner the program will be build and your up and running.