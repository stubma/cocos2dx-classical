#!/bin/bash

#  Created by Alex Karahalios on 6/12/11
#  Edited by Brian Reinhart on 08/02/2012 .
#  Last edited 8/02/2012
#
# Updates Xcode and to support LUA language for editing
#

# Path where this script is located
#
SCRIPT_PATH="$(dirname "$BASH_SOURCE")"

# Set up path for PlistBuddy helper application which can add elements to Plist files
#
PLISTBUDDY=/usr/libexec/PlistBuddy

# Filename path private framework we need to modify
#
#DVTFOUNDATION_PATH="/Developer/Library/PrivateFrameworks/DVTFoundation.framework/Versions/A/Resources/"
#DVTFOUNDATION_PATH="/XCode4.3/Library/PrivateFrameworks/DVTFoundation.framework/Versions/A/Resources/"

#<string>com.apple.xcode.lua-source</string>

# This framework is found withing the Xcode.app package and is used when Xcode is a monolithic
# install (all contained in Xcode.app)
#
XCODE_PATH=`xcode-select -print-path`
DVTFOUNDATION_PATH="$XCODE_PATH/../SharedFrameworks/DVTFoundation.framework/Resources/"

# Create Plist file of additional languages to add to 'DVTFoundation.xcplugindata'
#
cat >AdditionalLanguages.plist <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>Xcode.SourceCodeLanguage.Lua</key>
	<dict>
		<key>commentSyntax</key>
		<array>
			<dict>
				<key>prefix</key>
				<string>--[[</string>
				<key>suffix</key>
				<string>--]]</string>
			</dict>
			<dict>
				<key>prefix</key>
				<string>--</string>
			</dict>
		</array>
		<key>documentationAbbreviation</key>
		<string>lua</string>
		<key>fileDataType</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>com.apple.xcode.lua-source</string>
			</dict>
		</array>
		<key>id</key>
		<string>Xcode.SourceCodeLanguage.Lua</string>
		<key>point</key>
		<string>Xcode.SourceCodeLanguage</string>
		<key>languageName</key>
		<string>Lua</string>
		<key>languageSpecification</key>
		<string>xcode.lang.lua</string>
		<key>version</key>
		<string>1.0</string>
		<key>name</key>
		<string>Lua Language</string>
		<key>conformsTo</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>Xcode.SourceCodeLanguage.Generic</string>
			</dict>
		</array>
	</dict>
</dict>
</plist>
EOF

# Now merge in the additonal languages to DVTFoundation.xcplugindata
#
$PLISTBUDDY "$DVTFOUNDATION_PATH/DVTFoundation.xcplugindata"  -c 'Merge AdditionalLanguages.plist plug-in:extensions'

# Get rid of the AdditionalLanguages.plist since it was just temporary
#
rm -f AdditionalLanguages.plist

# Copy in the xclangspecs for the languages (assumes in same directory as this shell script)
#
cp "$SCRIPT_PATH/Lua.xclangspec" "$DVTFOUNDATION_PATH"

# Remove any cached Xcode plugins
# Xcode 6 
rm -f /private/var/folders/*/*/*/com.apple.DeveloperTools/*/Xcode/PlugInCache-Debug.xcplugincache
# Xcode 4+5
rm -f /private/var/folders/*/*/*/com.apple.DeveloperTools/*/Xcode/PlugInCache.xcplugincache

# register lua uti so that xcode can choose syntax coloring automatically
open $SCRIPT_PATH/export_lua_uti.app
sleep 3
ps -ef|grep export_lua_uti|grep -v grep|awk '{print $2}'|xargs kill -9
