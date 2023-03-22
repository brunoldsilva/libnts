/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <chrono>
#include <gtest/gtest.h>
#include <thread>

#include <libnts/logging/standard_logger.hpp>

namespace nts {
namespace tests {

TEST(StandardLoggerUnitTests, Log)
{
    using namespace std::chrono_literals;

    // Create a StandardLogger object.
    auto logger = std::make_shared<StandardLogger>();
    ASSERT_TRUE(logger);

    // Log a message for each severity.
    LogMessage line1(LogSeverity::Trace, "StandardLoggerTests", "Thirty days hath September,");
    logger->log(line1);

    // Sleep between logs to check if the output records the time correctly.
    std::this_thread::sleep_for(100ms);

    LogMessage line2(LogSeverity::Debug, "StandardLoggerTests", "April, June, and November;");
    logger->log(line2);

    std::this_thread::sleep_for(100ms);

    LogMessage line3(LogSeverity::Info, "StandardLoggerTests", "February has twenty-eight alone.");
    logger->log(line3);

    std::this_thread::sleep_for(100ms);

    LogMessage line4(LogSeverity::Warning, "StandardLoggerTests", "All the rest have thirty-one,");
    logger->log(line4);

    std::this_thread::sleep_for(100ms);

    LogMessage line5(LogSeverity::Error, "StandardLoggerTests", "Excepting leap-year—that's the time");
    logger->log(line5);

    std::this_thread::sleep_for(100ms);

    LogMessage line6(LogSeverity::Fatal, "StandardLoggerTests", "When February's days are twenty-nine.");
    logger->log(line6);
}

} // namespace tests
} // namespace nts
