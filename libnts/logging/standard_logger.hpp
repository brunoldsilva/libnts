#pragma once

#include <libnts/logging/logger.hpp>

namespace nts {

/// Writes messages to the standard output.
class StandardLogger : public Logger
{
public:
    /// Constructor.
    StandardLogger() = default;

    /// Destructor.
    ~StandardLogger() = default;

    /// Write the message to the standard output.
    virtual void log(LogMessage message);

protected:
    /// Additional information to put at the beginning of the log.
    virtual std::string getLogPrefix(const LogMessage& message) const;

    /// Additional information to put at the end of the log.
    virtual std::string getLogSuffix(const LogMessage& message) const;
};

} // namespace nts
