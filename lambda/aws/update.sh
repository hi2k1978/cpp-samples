#!/usr/bin/env bash

set -u

##
## read modules
##
. ./aws/modules.sh

##
## read run commands
##
. ./aws/rc.conf


if true; then
    print_title "create lambda functions"
    update_lambda_functions
    print_result
fi

