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

function init(){
    if true; then
	print_title "create lambda iam roles"
	arn=""
	get_lambda_iam_role rc_lambda_iam_role arn
	if [ $? -eq 0 ]; then
	    echo $arn
	    create_lambda_iam_roles rc_lambda_iam_role
	fi
	print_result
    fi

    if true; then
	print_title "create lambda functions"
	create_lambda_functions rc_lambda_function rc_lambda_iam_role
	print_result
    fi
}


init
