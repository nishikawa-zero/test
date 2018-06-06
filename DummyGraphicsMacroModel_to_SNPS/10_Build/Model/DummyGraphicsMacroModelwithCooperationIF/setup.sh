#!/bin/sh

if [ -z ${CARBON_GNU_PATH} ]; then
    echo "not found Carbon GNU tools settings"
    echo "setup is imcomplete"
else
    export REPOSITORY_TOP=`readlink -f ../../../../`
    echo REPOSITORY_TOP=\"$REPOSITORY_TOP\"
fi
