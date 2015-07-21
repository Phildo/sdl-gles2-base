DEVICE=-d #-e = emulator, -d = device (usb)

build:
	ndk-build && ant -S debug

install: build
	adb $(DEVICE) install -r bin/DoTest-debug.apk

run: install
	adb shell am start -n com.phildogames.dotest/com.phildogames.dotest.DoTest

debug: run
	adb logcat -c && adb logcat | sed -n /DO/p

debug-unfiltered: run
	adb logcat -c && adb logcat

vactivity:
	vim src/com/phildogames/dotest/DoTest.java

vsrc:
	vim jni/src/Android.mk


