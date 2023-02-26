/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <libnts/config/environment.hpp>

#include <libnts/config/json_environment.hpp>

namespace nts {

std::shared_ptr<Environment> Environment::environment = nullptr;

std::shared_ptr<Environment> Environment::getInstance()
{
    if (!environment)
    {
        std::shared_ptr<JsonEnvironment> jsonEnvironment = std::make_shared<JsonEnvironment>();
        jsonEnvironment->openConfigFile("config.json");
        environment = std::static_pointer_cast<Environment>(jsonEnvironment);
    }
    return environment;
}

void Environment::setInstance(std::shared_ptr<Environment> instance)
{
    environment = instance;
}

} // namespace nts
