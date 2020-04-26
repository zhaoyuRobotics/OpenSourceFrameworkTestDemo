TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    precisetimer.cpp


HEADERS +=  precisetimer.h

LIBS += -lpthread -latomic

#system(sudo usermod -aG dialout $USER && echo 1 | sudo tee /sys/bus/usb-serial/devices/ttyUSB0/latency_timer)
#system(cat /sys/bus/usb-serial/devices/ttyUSB0/latency_timer)
