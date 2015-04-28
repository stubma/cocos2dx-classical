#!/bin/bash

if [ $# != 1 ]; then
	echo "usage: pvr_converter.sh [directory]"
	exit
fi

DIR=$1
TP=/Applications/TexturePacker.app/Contents/MacOS/TexturePacker
for f in $DIR/*.png 
do
	FILENAME=`basename "$f"`
	FILEDIR=`dirname "$f"`
	FN_NO_EXT=`echo $FILENAME | awk -F '.' '{ print $1 }'`
	FN_PVR="$FN_NO_EXT.pvr.ccz"
	FP_PVR=$FILEDIR/$FN_PVR
	echo "converting $f"
	$TP "$f" --sheet "$FP_PVR" --texture-format pvr2ccz --opt PVRTC4 --premultiply-alpha --dither-fs-alpha --border-padding 0
done