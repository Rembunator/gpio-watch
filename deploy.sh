#!/bin/sh
export NDK_PROJECT_PATH=.
ndk-build NDK_APPLICATION_MK=./Application.mk

retVal=$?
if [ $retVal -ne 0 ]; then
    echo "The build process didn't complete without errors."
    exit $retval

else
    # push config to android device
    adb push ./gpio_inputs.config /data/test/
    # push application to android device
    adb push ./libs/armeabi-v7a/main /data/test/
fi
