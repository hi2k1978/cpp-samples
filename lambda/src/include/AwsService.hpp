#ifndef AWS_SERVICE_HPP_
#define AWS_SERVICE_HPP_

namespace AwsService {
    namespace DynamoDB {

        template<typename DynamoDBClient>
        Client<DynamoDBClient>::Client(const Aws::Client::ClientConfiguration &clientConfig) noexcept
                : client(DynamoDBClient(clientConfig)) {}

        template<typename DynamoDBClient>
        auto Client<DynamoDBClient>::get_item(const GetItemRequest& request) -> std::tuple<Result, Item> const {
            const Aws::DynamoDB::Model::GetItemOutcome &outcome = client.GetItem(request);
            if (outcome.IsSuccess()) {
                return {Result(true), outcome.GetResult().GetItem()};
            } else {
                return {Result(false, outcome.GetError().GetMessage()), Item()};
            }
        }

        template<typename DynamoDBClient>
        auto Client<DynamoDBClient>::put_item(const PutItemRequest& request) -> Result const {
            const Aws::DynamoDB::Model::PutItemOutcome outcome = client.PutItem(request);
            if (outcome.IsSuccess()) {
                return Result(true);
            } else {
                return Result(false, outcome.GetError().GetMessage());
            }
        }
    }
}
#endif
