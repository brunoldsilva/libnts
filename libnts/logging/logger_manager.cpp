#include <libnts/logging/logger_manager.hpp>

#include <libnts/logging/standard_logger.hpp>

namespace nts {

LoggerManager::LoggerManager()
{
    auto defaultLogger = std::make_shared<StandardLogger>();
    addLogger(defaultLogger);
}

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
