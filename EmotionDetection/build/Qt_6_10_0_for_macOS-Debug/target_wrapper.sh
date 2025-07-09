#!/bin/bash
DYLD_FRAMEWORK_PATH=/Users/olga_zalutskaya/Qt/6.10.0/macos/lib${DYLD_FRAMEWORK_PATH:+:$DYLD_FRAMEWORK_PATH}
export DYLD_FRAMEWORK_PATH
QT_PLUGIN_PATH=/Users/olga_zalutskaya/Qt/6.10.0/macos/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
