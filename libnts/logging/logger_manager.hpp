/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <libnts/logging/logger.hpp>

namespace nts {

/// Singleton object that manages loggers used by the library.
class LoggerManager : public Logger
{
public:
    /// Constructor.
    LoggerManager();

    /// Destructor.
    ~LoggerManager() = default;

    /// A globally accessible instance of the manager.
    static std::shared_ptr<LoggerManager> getInstance();

    /// Write the messages to all available logs.
    virtual void log(LogMessage message);

    /// Add the logger to the list of available loggers.
    void addLogger(std::shared_ptr<Logger> logger);

    /// Get all available loggers.
    void getLoggers(std::vector<std::shared_ptr<Logger>>& outLoggers);

private:
    /// List of available loggers to which to write messages.
    std::vector<std::shared_ptr<Logger>> loggers;
};

} // namespace nts
