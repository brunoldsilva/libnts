/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <gtest/gtest.h>

#include <libnts/logging/log.hpp>
#include <libnts/logging/logger_manager.hpp>
#include <libnts/logging/standard_logger.hpp>

namespace nts {
namespace tests {

TEST(LogUnitTests, Macros)
{
    /// Get the logger manager.
    std::shared_ptr<LoggerManager> manager = LoggerManager::getInstance();
    ASSERT_TRUE(manager);

    // Create a StandardLogger object and add it to the manager.
    auto logger = std::make_shared<StandardLogger>();
    ASSERT_TRUE(logger);
    manager->addLogger(logger);

    // Write a log message using each of the macros.
    TRACE("LogUnitTests", "{} days hath {},", 30, "September");
    DEBUG("LogUnitTests", "{}, {}, and {};", "April", "June", "November");
    INFO("LogUnitTests", "{} has {} alone.", "February", 28);
    WARN("LogUnitTests", "All the rest have {},", 31);
    ERROR("LogUnitTests", "Excepting leap-year—that's the time");
    FATAL("LogUnitTests", "When {}'s days are {}.", "February", 29);
}

} // namespace tests
} // namespace nts
