# qmlnotify

![gif1](https://raw.githubusercontent.com/alamminsalo/qmlnotify/master/screenshots/record1.gif)
![gif2](https://raw.githubusercontent.com/alamminsalo/qmlnotify/master/screenshots/waveform.gif)
![gif3](https://raw.githubusercontent.com/alamminsalo/qmlnotify/master/screenshots/waveform2.gif)
![gif4](https://raw.githubusercontent.com/alamminsalo/qmlnotify/master/screenshots/animated9.gif)

## What is it?
Desktop notification server which implements org.freedesktop.Notifications, using modern Qt/Qml technologies

## Usage

* Start the server 
* Test via notify-send or similar
* Write your own qml component and start the server with param `--qml $YOUR_QML_NOTIFICATION_COMPONENT`
* Enjoy!

The qml component can be either at `/etc/qmlnotify/` or `$HOME/.config/qmlnotify/`.

Keep in mind that the last path (`$HOME/.config/qmlnotify`) will be prefered when
looking for the qml component.

**NOTE**: Currently, the AppArmor profile is not configured to allow access to `/etc/qmlnotify`

## Building instructions

#### Install needed packages (arch examples)
```
sudo pacman -S qt5-base
```
#### Clone from github and compile
```
git clone https://github.com/alamminsalo/qmlnotify
cd qmlnotify
mkdir build && cd build
qmake ../
make
```
#### Test it
```
./qmlnotify
```

## Securing qmlnotify
This fork of qmlnotify contains an (probably poorly written) AppArmor profile,
which restricts qmlnotify as much as possible.

To make it work, copy `qmlnotify`, after building it, to
`/usr/local/bin/qmlnotify`. Then copy the AppArmor profile `apparmor/qmlnotify`
to `/etc/apparmor.d/custom/qmlnotify` and enable it using `apparmor_parser -a /etc/apparmor.d/custom/qmlnotify` (Using sudo may be required).

Please note that the profile will **not** survive a reboot and will need to be
reactivated.
