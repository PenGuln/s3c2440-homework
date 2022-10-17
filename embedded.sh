cd /home/uptech/
mkdir for_arm
cd /home/uptech/QT4/for_arm
tar xjvf /UP-CUP2440/SRC/gui/tslib-1.4.tar.bz2 -C /home/uptech/QT4/for_arm/
cd /home/uptech/QT4/for_arm/tslib-1.4/
./build.sh
cd /home/uptech/QT4/for_arm/
tar xjvf /UP-CUP2440/SRC/gui/qt-embedded-linux-opensource-src-4.4.0.tar.bz2 –C /home/uptech/QT4/for_arm/
cd qt-embedded-linux-opensource-src-4.4.0/
./ build4arm.sh
