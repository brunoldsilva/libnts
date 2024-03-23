#pragma once

#include <fmt/core.h>

#include <libnts/logging/logger.hpp>
#include <libnts/logging/logger_manager.hpp>

namespace nts {

/// Convenience macro for writing a message to the log.
#define LOG(severity, category, message, ...)                                              \
    if (std::shared_ptr<LoggerManager> manager = LoggerManager::getInstance())             \
    {                                                                                      \
        manager->log(LogMessage(severity, category, fmt::format(message, ##__VA_ARGS__))); \
    }

/// Convenience macro for writing a trace-severity message to the log.
#define TRACE(category, format, ...) LOG(LogSeverity::Trace, category, format, ##__VA_ARGS__)

/// Convenience macro for writing a debug-severity message to the log.
#define DEBUG(category, format, ...) LOG(LogSeverity::Debug, category, format, ##__VA_ARGS__)

/// Convenience macro for writing a info-severity message to the log.
#define INFO(category, format, ...) LOG(LogSeverity::Info, category, format, ##__VA_ARGS__)

/// Convenience macro for writing a warning-severity message to the log.
#define WARN(category, format, ...) LOG(LogSeverity::Warning, category, format, ##__VA_ARGS__)

/// Convenience macro for writing a error-severity message to the log.
#define ERROR(category, format, ...) LOG(LogSeverity::Error, category, format, ##__VA_ARGS__)

/// Convenience macro for writing a fatal-severity message to the log.
#define FATAL(category, format, ...) LOG(LogSeverity::Fatal, category, format, ##__VA_ARGS__)

} // namespace nts
