# gpio-watch

## Prerequisites

you should have the android ndk installed and the path to `ndk-build` should be in the `PATH` var.

## Building and Pushing

There's a script for convenience called `deploy.sh`.  
Well... My convenience, you'll have to modify it for your own situation.  
You can either use the script or build and push manually.

## Building

```export NDK_PROJECT_PATH=.```  
```ndk-build NDK_APPLICATION_MK=./Application.mk```

## Pushing to the Android device

To push the app and config to the android device use:  
```adb push gpiowatch /data/<path-to-app>```  
```adb push gpio-inputs.config /data/<path-to-app>```<sup>1</sup>

<sup>1</sup>
*The ap and config file should be in the same directory*

## References

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
