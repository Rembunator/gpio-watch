#!/bin/sh
ANDROIDDEST="/data/gpio"

export NDK_PROJECT_PATH=.
ndk-build NDK_APPLICATION_MK=./Application.mk

retVal=$?
if [ $retVal -ne 0 ]; then
    echo "The build process didn't complete without errors."
    exit $retval
    
else
    # create application dir on android device if it doesn't exist
    adb shell -x "mkdir -p $ANDROIDDEST"
    # push config to android device
    adb push ./gpio_inputs.config "$ANDROIDDEST/"
    # push application to android device
    adb push ./libs/armeabi-v7a/gpiowatch "$ANDROIDDEST/"
fi
