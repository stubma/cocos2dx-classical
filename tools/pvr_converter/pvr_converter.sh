#!/bin/bash
# this script is used to convert a png atlas into pvr format
# if you want to compact a bunch of png into one atlas, use following command with your modification
# TexturePacker --sheet fish.pvr.ccz --texture-format pvr2ccz --data fish.plist --premultiply-alpha --dither-fs-alpha --border-padding 0 --max-size 1024 --format cocos2d --opt RGBA4444 --disable-rotation *.png 

if [ $# -lt 1 ]; then
	echo "usage: pvr_converter.sh [directory] [file ext(optional)] [image opt(optional)]"
	exit
fi

DIR=$1
EXT="*.png"
OPT=PVRTC4
if [ $# -gt 1 ]; then
	EXT="*.$2"
fi
if [ $# -gt 2 ]; then
	OPT=$3
fi
TP=/Applications/TexturePacker.app/Contents/MacOS/TexturePacker
for f in $DIR/$EXT
do
	FILENAME=`basename "$f"`
	FILEDIR=`dirname "$f"`
	FN_NO_EXT=`echo $FILENAME | awk -F '.' '{ print $1 }'`
	FN_PVR="$FN_NO_EXT.pvr.ccz"
	FP_PVR=$FILEDIR/$FN_PVR
	echo "converting $f"
	$TP "$f" --sheet "$FP_PVR" --texture-format pvr2ccz --opt $OPT --premultiply-alpha --dither-fs-alpha --border-padding 0 --disable-rotation
done