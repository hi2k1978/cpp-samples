#!/usr/bin/env bash
# base_endpoint="https://b89c1ptd5h.execute-api.ap-northeast-1.amazonaws.com/default"
base_endpoint="https://b89c1ptd5h.execute-api.ap-northeast-1.amazonaws.com/default"
endpoint="${base_endpoint}/apigw?name=Bradley&city=Chicago"
echo "endpoint: ${endpoint}"
echo
sleep 1

curl -v -X POST \
  ${endpoint} \
  -H 'content-type: application/json' \
  -H 'day: Sunday' \
  -d '{ "time": "evening" }'
echo
echo


