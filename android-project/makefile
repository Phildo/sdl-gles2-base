CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/jni/src/src
BINDIR = $(CURDIR)/bin

DEVICE=-d #-e = emulator, -d = device (usb)

PLATFORM_FLAG=DO_PLATFORM_PC

HEADERS=$(wildcard $(SRCDIR)/*.h)
SOURCES=$(wildcard $(SRCDIR)/*.cpp)

b: build
	

define:
	sed -i .bak 's/DO_PLATFORM .*$$/DO_PLATFORM DO_PLATFORM_ANDROID/' $(SRCDIR)/defines.h

build: define
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


