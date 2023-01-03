#!/usr/bin/env bash

function print_title() {
    echo "#####################################################"
    echo "## " $1
    echo "#####################################################"
}

function print_result() {
    if [ $? -eq 0 ]; then
	echo "[SUCCESS]"
    else
	echo "[FAILED]"
    fi
    echo 
    echo 
}

function get_arn_from_iam_role() {

    # get args
    local role_name=$1

    # set local variables
    local result_json
    
    # convert iam-role to arn
    local cmd="aws iam get-role --role-name ${role_name}"
    echo $cmd 1>&2
    if ${is_execute}; then local result_json=$(eval $cmd); fi
    # local result_json=$(eval $cmd)
    if [ ${#result_json} -eq 0 ]; then return 1; fi
    local arn=$(echo $result_json | jq '.Role.Arn')
    echo $arn
    return 0
}

function create_lambda_iam_roles() {

    # create iam-role to use in lambda functions
    local cmd="aws iam create-role
    	     --role-name ${rc_lambda_iam_role["role_name"]} 
	     --assume-role-policy-document file://${rc_lambda_iam_role["policy_json"]}"
    echo $cmd 1>&2
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    # attach role with role-policy used in lambda
    local cmd="aws iam attach-role-policy
    	     --role-name ${rc_lambda_iam_role["role_name"]}
    	     --policy-arn ${rc_lambda_iam_role["policy_arn"]}"
    echo $cmd 1>&2
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    return 0
}
	      
function create_lambda_functions() {

    # convert iam-role to arn
    local arn=$(get_arn_from_iam_role ${rc_lambda_iam_role["role_name"]})
    if [ ${#arn} -eq 0 ]; then return 1; fi

    # creacte lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/build/${lambda_function}.zip
	local cmd="aws lambda create-function
	       --function-name ${lambda_function}
	       --role ${arn} 
	       --runtime ${rc_lambda_functions["runtime"]}
	       --timeout ${rc_lambda_functions["timeout"]}
	       --memory-size ${rc_lambda_functions["memory-size"]}
	       --handler ${lambda_function}
	       --zip-file fileb://${zip_file}"
	echo $cmd 1>&2
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
}


function update_lambda_functions() {

    # update lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/build/${lambda_function}.zip
	local cmd="aws lambda  update-function-code
	      	       --function-name ${lambda_function}
		       --zip-file fileb://${zip_file}"

	echo $cmd 1>&2
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
    
}
