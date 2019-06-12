# gpio-manager


** Building **

export NDK_PROJECT_PATH=.

ndk-build NDK_APPLICATION_MK=./Application.mk


** Pushing to the Android device **

adb push main /data/path-to-app


** References **

This project was based on information coming from these sources:

- gpioClass:  
https://github.com/halherta/RaspberryPi-GPIOClass-v2

- Building a native Android Commandline Application:
https://software.intel.com/en-us/articles/building-an-android-command-line-application-using-the-ndk-build-tools

- C++ Reference:
http://www.cplusplus.com/reference/

- Using std::poll:
http://www.unixguide.net/unix/programming/2.1.2.shtml
https://raspberrypi.stackexchange.com/questions/44416/polling-gpio-pin-from-c-always-getting-immediate-response/44417#44417