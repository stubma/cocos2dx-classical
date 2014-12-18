#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $DIR
host_os=`uname -s | tr "[:upper:]" "[:lower:]"`

SRCDIR=$DIR/src
PREBUILT_DIR=$DIR/prebuilt/android
cd "$SRCDIR"

NDK=$NDK_ROOT
NDKABI=9
NDKVER=$NDK/toolchains/arm-linux-androideabi-4.6
NDKP=$NDKVER/prebuilt/${host_os}-x86_64/arm-linux-androideabi/bin/
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm -DANDROID"

# Android/ARM, armeabi (ARMv5TE soft-float), Android 2.2+ (Froyo)
DESTDIR=$PREBUILT_DIR/armeabi
rm "$DESTDIR"/*.a
make clean
make linux CROSS_COMPILE="$NDKP" TARGET_FLAGS="$NDKF"

if [ -f $SRCDIR/src/liblua.a ]; then
    mv $SRCDIR/src/liblua.a $DESTDIR/liblua.a
fi;

# Android/ARM, armeabi-v7a (ARMv7 VFP), Android 4.0+ (ICS)
NDKARCH="-march=armv7-a -mfloat-abi=softfp -Wl,--fix-cortex-a8"
DESTDIR=$PREBUILT_DIR/armeabi-v7a
rm "$DESTDIR"/*.a
make clean
make linux CROSS_COMPILE="$NDKP" TARGET_FLAGS="$NDKF $NDKARCH"

if [ -f $SRCDIR/src/liblua.a ]; then
    mv $SRCDIR/src/liblua.a $DESTDIR/liblua.a
fi;

# Android/x86, x86 (i686 SSE3), Android 4.0+ (ICS)
NDKABI=14
DESTDIR=$PREBUILT_DIR/x86
NDKVER=$NDK/toolchains/x86-4.6
NDKP=$NDKVER/prebuilt/${host_os}-x86_64/i686-linux-android/bin/
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-x86 -DANDROID"
rm "$DESTDIR"/*.a
make clean
make linux CROSS_COMPILE="$NDKP" TARGET_FLAGS="$NDKF"

if [ -f $SRCDIR/src/liblua.a ]; then
    mv $SRCDIR/src/liblua.a $DESTDIR/liblua.a
fi;

make clean
