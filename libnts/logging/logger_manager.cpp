/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/logging/logger_manager.hpp>

namespace nts {

std::shared_ptr<LoggerManager> LoggerManager::getInstance()
{
    static auto instance = std::make_shared<LoggerManager>();
    return instance;
}

void LoggerManager::log(LogMessage message)
{
    for (const auto& logger : loggers)
    {
        logger->log(message);
    }
}

void LoggerManager::addLogger(std::shared_ptr<Logger> logger)
{
    loggers.push_back(logger);
}

void LoggerManager::getLoggers(std::vector<std::shared_ptr<Logger>>& outLoggers)
{
    outLoggers = loggers;
}

} // namespace nts
