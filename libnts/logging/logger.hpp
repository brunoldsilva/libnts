#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace nts {

/// Severity of the message sent to the log.
enum class LogSeverity
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

/// A literal representation of the severity level.
std::string severityToString(const LogSeverity severity);

/// Message to be passed to the log.
class LogMessage
{
public:
    /// Constructor.
    LogMessage();

    /// Constructor.
    LogMessage(LogSeverity severity, std::string category, std::string message);

    /// Destructor.
    ~LogMessage() = default;

    /// Severity of the message.
    LogSeverity getSeverity() const;

    /// Category of the message.
    void getCategory(std::string& outCategory) const;

    /// The message to be written to the log.
    void getMessage(std::string& outMessage) const;

    /// Time when the message was created.
    std::chrono::steady_clock::time_point getTimestamp() const;

    /// Severity of the message.
    void setSeverity(const LogSeverity severity);

    /// Category of the message.
    void setCategory(const std::string category);

    /// The message to be written to the log.
    void setMessage(const std::string message);

private:
    /// Severity of the message.
    LogSeverity severity{ LogSeverity::Info };

    /// Category of the message.
    std::string category;

    /// The user provided message to be written to the log.
    std::string message;

    /// Time when the message was created.
    std::chrono::steady_clock::time_point timestamp;
};

/// Interface for objects that wish to handle log messages.
class Logger
{
public:
    /// Write the message to the log.
    virtual void log(LogMessage message) = 0;
};

} // namespace nts
