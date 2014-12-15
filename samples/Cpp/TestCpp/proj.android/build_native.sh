APPNAME="TestCpp"

# options
BUILD_EXTERNALS_FROM_SOURCE=

# print usage
usage() {
	cat << EOF
usage: $0 [options]
Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}

# process options
while getopts "sh" OPTION; do
	case "$OPTION" in
		s)
			BUILD_EXTERNALS_FROM_SOURCE=1
		;;
		h)
			usage
			exit 0
		;;
	esac
done

# read local.properties
_LOCALPROPERTIES_FILE=$(dirname "$0")"/local.properties"
if [ -f "$_LOCALPROPERTIES_FILE" ]
then
    [ -r "$_LOCALPROPERTIES_FILE" ] || die "Fatal Error: $_LOCALPROPERTIES_FILE exists but is unreadable"

    # strip out entries with a "." because Bash cannot process variables with a "."
    _PROPERTIES=`sed '/\./d' "$_LOCALPROPERTIES_FILE"`
    for line in "$_PROPERTIES"; do
        declare "$line";
    done
fi

# import environments
source $HOME/.bash_profile

# check NDK_ROOT
if [ -z "${NDK_ROOT+aaa}" ]; then
	echo "NDK_ROOT not defined. Please define NDK_ROOT in your environment or in local.properties"
	exit 1
fi

# ... use paths relative to current directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR/../../../.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"

# cpu cores
CPU=`sysctl -n hw.ncpu`

# print paths
echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# start build
if [[ "$BUILD_EXTERNALS_FROM_SOURCE" ]]; then
    echo "Building external dependencies from source"
    "$NDK_ROOT"/ndk-build -j $CPU -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$NDK_ROOT"/ndk-build -j $CPU -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi