#
# This makefile mainly forwards make commands to correct project
#
SRC_DIR=src
MAC_DIR=pc-project
LINUX_DIR=linux-project
PC_DIR=pc-project
ANDROID_DIR=android-project
IOS_DIR=ios-project

#
# first to handle argumentless make
#
b: build
	

r: run
	

#
# defaults (switch out for sugar w/r/t currently working-on platform)
#
vmake: avmake
	

build: abuild
	

install: ainstall
	

run: arun
	

debug: adebug
	

kill: akill
	


#
# mac
#
mvmake:
	vim $(MAC_DIR)/makefile

mbuild:
	cd $(MAC_DIR); amake build;

minstall:
	cd $(MAC_DIR); amake install;

mrun:
	cd $(MAC_DIR); amake run;

mdebug:
	cd $(MAC_DIR); amake debug;

mkill:
	cd $(MAC_DIR); amake kill;


#
# linux
#
lvmake:
	vim $(LINUX_DIR)/makefile

lbuild:
	cd $(LINUX_DIR); amake build;

linstall:
	cd $(LINUX_DIR); amake install;

lrun:
	cd $(LINUX_DIR); amake run;

ldebug:
	cd $(LINUX_DIR); amake debug;

lkill:
	cd $(LINUX_DIR); amake kill;


#
# pc
#
pvmake:
	vim $(PC_DIR)/makefile

pbuild:
	cd $(PC_DIR); amake build;

pinstall:
	cd $(PC_DIR); amake install;

prun:
	cd $(PC_DIR); amake run;

pdebug:
	cd $(PC_DIR); amake debug;

pkill:
	cd $(PC_DIR); amake kill;


#
# android
#
avmake:
	vim $(ANDROID_DIR)/makefile

abuild:
	cd $(ANDROID_DIR); amake build;

ainstall:
	cd $(ANDROID_DIR); amake install;

arun:
	cd $(ANDROID_DIR); amake run;

adebug:
	cd $(ANDROID_DIR); amake debug;

akill:
	cd $(ANDROID_DIR); amake kill;

#
# ios
#
ivmake:
	vim $(IOS_DIR)/makefile

ibuild:
	cd $(IOS_DIR); amake build;

iinstall:
	cd $(IOS_DIR); amake install;

irun:
	cd $(IOS_DIR); amake run;

idebug:
	cd $(IOS_DIR); amake debug;

ikill:
	cd $(IOS_DIR); amake kill;

