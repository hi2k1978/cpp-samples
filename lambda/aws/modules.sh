#!/usr/bin/env bash

retval=

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

function get_lambda_iam_role() {

    declare -n rc=$1

    # set local variables
    local result_json
    
    # convert iam-role to arn
    local cmd="aws iam get-role --role-name ${rc["role_name"]}"
    echo $cmd
    if ${is_execute}; then
	local -r result_json=$(eval $cmd)
	if [ $? -ne 0 ]; then return 1; fi
	retval=$(echo $result_json | jq '.Role.Arn')
    fi
    return 0
}

function create_lambda_iam_roles() {

    declare -n rc=$1
    
    # create iam-role to use in lambda functions
    local -r cmd="aws iam create-role
    	     --role-name ${rc["role_name"]} 
	     --assume-role-policy-document file://${rc["policy_json"]}"
    echo $cmd
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    # attach role with role-policy used in lambda
    local cmd="aws iam attach-role-policy
    	     --role-name ${rc["role_name"]}
    	     --policy-arn ${rc["policy_arn"]}"
    echo $cmd
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    return 0
}
	      
function create_lambda_functions() {

    declare -n rc=$1
    declare -n rc_iam_role=$2
    local -r lambda_functions=( ${rc["lambda_functions"]} )
    local -r lambda_iam_role=${rc_iam_role["role_name"]}
    # convert iam-role to arn
    get_lambda_iam_role rc_iam_role
    if [ $? -ne 0 ]; then return 1; fi
    arn=$retval

    # creacte lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/${lambda_function}/build/${rc["handler"]}.zip
	local cmd="aws lambda create-function
	       --function-name ${lambda_function}
	       --role ${arn} 
	       --runtime ${rc["runtime"]}
	       --timeout ${rc["timeout"]}
	       --memory-size ${rc["memory-size"]}
	       --handler ${rc["handler"]}
	       --zip-file fileb://${zip_file}"
	echo $cmd
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
}
# aws lambda add-permission \
#  --statement-id 133e26af-b50d-5ad7-8c34-558eb69acbbb \
#  --action lambda:InvokeFunction \
#  --function-name "arn:aws:lambda:ap-northeast-1:681609929005:function:apigw" \
#  --principal apigateway.amazonaws.com \
#  --source-arn "arn:aws:execute-api:ap-northeast-1:681609929005:b89c1ptd5h/*/*/apigw"


function update_lambda_functions() {

    declare -n rc=$1
    local -r lambda_functions=( ${rc["lambda_functions"]} )

    # update lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/${lambda_function}/build/handler.zip
	local cmd="aws lambda  update-function-code
	      	       --function-name ${lambda_function}
		       --zip-file fileb://${zip_file}"

	echo $cmd
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
    
}

