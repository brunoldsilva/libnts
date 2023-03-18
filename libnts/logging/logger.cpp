/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/logging/logger.hpp>

#include <cstdarg>
#include <cstdio>
#include <sstream>

namespace nts {

std::string severityToString(const LogSeverity severity)
{
    switch (severity)
    {
        case LogSeverity::Trace:
            return "Trace";
            break;
        case LogSeverity::Debug:
            return "Debug";
            break;
        case LogSeverity::Info:
            return "Info";
            break;
        case LogSeverity::Warning:
            return "Warning";
            break;
        case LogSeverity::Error:
            return "Error";
            break;
        case LogSeverity::Fatal:
            return "Fatal";
            break;
        default:
            return "NotImplemented";
            break;
    }
}

LogMessage::LogMessage()
{
    timestamp = std::chrono::steady_clock::now();
}

LogMessage::LogMessage(LogSeverity severity, std::string category, std::string message)
    : severity(severity), category(category), message(message)
{
    timestamp = std::chrono::steady_clock::now();
}

LogSeverity LogMessage::getSeverity() const
{
    return severity;
}

void LogMessage::getCategory(std::string& outCategory) const
{
    outCategory = category;
}

void LogMessage::getMessage(std::string& outMessage) const
{
    outMessage = message;
}

std::chrono::steady_clock::time_point LogMessage::getTimestamp() const
{
    return timestamp;
}

void LogMessage::setSeverity(const LogSeverity severity)
{
    this->severity = severity;
}

void LogMessage::setCategory(const std::string category)
{
    this->category = category;
}

void LogMessage::setMessage(const std::string message)
{
    this->message = message;
}

} // namespace nts
