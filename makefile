#
# This makefile mainly forwards make commands to correct project
#
SRC_DIR=src
ANDROID_DIR=android-project
IOS_DIR=ios-project
PC_DIR=pc-project

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
idefine:
	sed -i.bak -E -e 's/define $(ANDROID_DEF)|define $(PC_DEF)/define $(IOS_DEF)/g' $(SRC_DIR)/defines.h && rm $(SRC_DIR)/defines.h.bak

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


#
# pc
#
pdefine:
	sed -i.bak -E -e 's/define $(IOS_DEF)|define $(ANDROID_DEF)/define $(PC_DEF)/g' $(SRC_DIR)/defines.h && rm $(SRC_DIR)/defines.h.bak

pvmake:
	vim $(PC_DIR)/makefile

pbuild:
	cd $(PC_DIR); amake build;

pinstall:
	cd $(PC_DIR); amake install;

prun:
	cd $(PC_DIR); amake run;

prun4:
	cd $(PC_DIR); amake run4;

pdebug:
	cd $(PC_DIR); amake debug;

pdebug4:
	cd $(PC_DIR); amake debug4;

pkill:
	cd $(PC_DIR); amake kill;

