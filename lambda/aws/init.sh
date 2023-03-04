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
	declare -A lambda_iam_role
	get_lambda_iam_role lambda_iam_role
	if [ ${lambda_iam_role["arn"]} == "__lambda_iam_role__" ]; then
	    create_lambda_iam_roles
	fi
	print_result
    fi

    if true; then
	print_title "create lambda functions"
	create_lambda_functions
	print_result
    fi
}


init
