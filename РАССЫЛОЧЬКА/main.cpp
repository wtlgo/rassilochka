#include <iostream>
#include <string>
#include <random>

#include <wtlgo/Network.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "config.hpp"

int main(int argc, const char * argv[]) {
    using namespace wtlgo;

    const std::string vk_api = "https://api.vk.com/method/";

    auto chat = json::parse(network.request(vk_api + "messages.getChat", {
        {"access_token", access_token}, 
        {"v", v}, 
        {"chat_id", std::to_string(chat_id)}
    }));

    std::vector<int> users = chat["response"]["users"];

    std::mt19937 engine((std::random_device())());
    std::uniform_int_distribution<int64_t> random_id(0, std::numeric_limits<int64_t>::max());

    for(auto user : users) {
        if(user < 0) continue;

        network.request(vk_api + "messages.send", {
            {"access_token", access_token}, 
            {"v", v}, 
            {"user_id", std::to_string(user)},
            {"message", message},
            {"random_id", std::to_string(random_id(engine))}
        });
    }
    
    return 0;
}
