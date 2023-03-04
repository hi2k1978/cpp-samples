#!/usr/bin/env bash

set -euo pipefail

##
## read modules
##
. ./aws/modules.sh

##
## read run commands configurations
##
. ./aws/rc.conf


if true; then
    print_title "update lambda functions"
    deploy_lambda_functions
    print_result
fi

