#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LIPO="xcrun -sdk iphoneos lipo"
STRIP="xcrun -sdk iphoneos strip"

SRCDIR=$DIR/src
DESTDIR=$DIR/prebuilt/ios
XCODE_PATH=`xcode-select -print-path`
SDK_PARAM=`xcodebuild -showsdks | awk '/^$/{p=0};p; /iOS SDKs:/{p=1}' | tail -1 | cut -f3`
SYSROOT=`xcodebuild -version $SDK_PARAM Path`
PLATFORM_PATH=`xcodebuild -version $SDK_PARAM PlatformPath`
AR_BIN=$PLATFORM_PATH//Developer/usr/bin/
CC_BIN=$XCODE_PATH/usr/bin/

rm "$DESTDIR"/*.a
cd $SRCDIR

make clean
ISDKF="-arch armv7 -isysroot $SYSROOT"
make macosx CROSS_COMPILE="$CC_BIN" CROSS_COMPILE_AR="$AR_BIN" TARGET_FLAGS="$ISDKF"
mv "$SRCDIR"/src/liblua.a "$DESTDIR"/liblua-armv7.a

make clean
ISDKF="-arch armv7s -isysroot $SYSROOT"
make macosx CROSS_COMPILE="$CC_BIN" CROSS_COMPILE_AR="$AR_BIN" TARGET_FLAGS="$ISDKF"
mv "$SRCDIR"/src/liblua.a "$DESTDIR"/liblua-armv7s.a

make clean
ISDKF="-arch arm64 -isysroot $SYSROOT"
make macosx CROSS_COMPILE="$CC_BIN" CROSS_COMPILE_AR="$AR_BIN" TARGET_FLAGS="$ISDKF"
mv "$SRCDIR"/src/liblua.a "$DESTDIR"/liblua-arm64.a

make clean
make macosx HOST_CC="gcc -m32 -arch i386"
mv "$SRCDIR"/src/liblua.a "$DESTDIR"/liblua-i386.a

make clean
make macosx HOST_CC="gcc -arch x86_64"
mv "$SRCDIR"/src/liblua.a "$DESTDIR"/liblua-x86_64.a

$LIPO -create "$DESTDIR"/liblua-*.a -output "$DESTDIR"/liblua.a
$STRIP -S "$DESTDIR"/liblua.a
$LIPO -info "$DESTDIR"/liblua.a

rm "$DESTDIR"/liblua-*.a

make clean
