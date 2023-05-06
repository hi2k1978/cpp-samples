#!/usr/bin/env bash

# retval=

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
    declare -n retval=$1
    # declare -n rc=$2
    local result_json


    # convert iam-role to arn
    local cmd="aws iam get-role --role-name ${rc_lambda_iam_role["role_name"]}"
    echo $cmd
    case $is_execute in
	true)
	    result_json=$(eval $cmd)
	    if [ $? -ne 0 ]; then return 1; fi
	    retval["arn"]=$(echo $result_json | jq '.Role.Arn')
	    ;;
	*)
	    retval["arn"]="__lambda_iam_role__"
	    ;;
    esac
    echo "lambda-iam-role: " ${retval["arn"]} 
    return 0
}

function create_lambda_iam_roles() {
    local cmd
    # create iam-role to use in lambda functions
    cmd="aws iam create-role
    	     --role-name ${rc_lambda_iam_role["role_name"]} 
	     --assume-role-policy-document file://${rc_lambda_iam_role["policy_json"]}"
    echo $cmd
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    # attach role with role-policy used in lambda
    cmd="aws iam attach-role-policy
    	     --role-name ${rc_lambda_iam_role["role_name"]}
    	     --policy-arn ${rc_lambda_iam_role["policy_arn"]}"
    echo $cmd
    if ${is_execute}; then eval $cmd; fi
    if [ $? -ne 0 ]; then return 1; fi

    return 0
}
	      
function create_lambda_functions() {

    declare -A _lambda_iam_role

    local -r lambda_functions=( ${rc_lambda_function["lambda_functions"]} )

    # convert iam-role to arn
    get_lambda_iam_role _lambda_iam_role # rc_iam_role
    if [ $? -ne 0 ]; then return 1; fi

    # creacte lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/${lambda_function}/build/${rc_lambda_function["handler"]}.zip
	local cmd="aws lambda create-function
	       --function-name ${lambda_function}
	       --role ${_lambda_iam_role["arn"]} 
	       --runtime ${rc_lambda_function["runtime"]}
	       --timeout ${rc_lambda_function["timeout"]}
	       --memory-size ${rc_lambda_function["memory-size"]}
	       --handler ${rc_lambda_function["handler"]}
	       --zip-file fileb://${zip_file}"
	#      --code S3Bucket=bucket-name,S3Key=zip-file-object-key
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


function deploy_lambda_functions() {

    local -r lambda_functions=( ${rc_lambda_function["lambda_functions"]} )

    # update lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./build/src/${lambda_function}/handler.zip
	local cmd="aws lambda  update-function-code
	      	       --function-name ${lambda_function}
		       --zip-file fileb://${zip_file}"

	echo $cmd
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
}

function delete_lambda_functions() {

    local -r lambda_functions=( ${rc_lambda_function["lambda_functions"]} )

    # update lambda-functions
    for lambda_function in ${lambda_functions[@]}; do
	local zip_file=./src/${lambda_function}/build/handler.zip
	local cmd="aws lambda delete-function
	      	       --function-name ${lambda_function}"
	echo $cmd
	if ${is_execute}; then eval $cmd; fi
	if [ $? -ne 0 ]; then return 1; fi
    done

    return 0
}
