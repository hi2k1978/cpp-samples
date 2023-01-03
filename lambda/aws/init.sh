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

print_title "read run commands"
echo "aws_dir = ${aws_dir}"
echo "policy_dir = ${policy_dir}"
print_result

if true; then
    print_title "create lambda iam roles"
    create_lambda_iam_roles
    print_result
fi

if true; then
    print_title "create lambda functions"
    create_lambda_functions
    print_result
fi



