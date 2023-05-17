/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/logging/standard_logger.hpp>

#include <cstdio>
#include <iostream>
#include <fmt/core.h>
#include <fmt/chrono.h>

namespace nts {

void StandardLogger::log(LogMessage message)
{
    std::string log;
    message.getMessage(log);
    std::cout << getLogPrefix(message) << log << getLogSuffix(message) << std::endl;
}

std::string StandardLogger::getLogPrefix(const LogMessage& message) const
{
    using namespace std::chrono;

    std::time_t systemTime = system_clock::to_time_t(system_clock::now());
    std::tm* localTime = std::localtime(&systemTime);

    long ms = duration_cast<milliseconds>(message.getTimestamp().time_since_epoch()).count() % (1000);

    std::string timeLiteral = fmt::format("{:%Y-%m-%d %H:%M:%S}.{:0>3}", *localTime, ms);

    std::string category{ "" };
    message.getCategory(category);

    std::string severity = severityToString(message.getSeverity());

    return fmt::format("{} {:^7} {}: ", timeLiteral, severity, category);
}

std::string StandardLogger::getLogSuffix(const LogMessage& message) const
{
    return "";
}

} // namespace nts
