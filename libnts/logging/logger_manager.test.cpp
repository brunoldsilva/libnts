#include <algorithm>
#include <gtest/gtest.h>

#include <libnts/logging/logger_manager.hpp>

namespace nts {
namespace tests {

namespace logger_manager {

class TestLogger : public Logger
{
public:
    virtual void log(LogMessage message){};
};

} // namespace logger_manager

TEST(LoggerManagerUnitTests, Instance)
{
    std::shared_ptr<LoggerManager> manager = LoggerManager::getInstance();
    ASSERT_TRUE(manager);
}

TEST(LoggerManagerUnitTests, Accessors)
{
    // Create a logger manager.
    auto manager = std::make_shared<LoggerManager>();
    ASSERT_TRUE(manager);

    // The manager should only have the default logger.
    std::vector<std::shared_ptr<Logger>> loggers;
    manager->getLoggers(loggers);
    EXPECT_EQ(loggers.size(), 1);

    // Create a test logger.
    auto logger = std::make_shared<logger_manager::TestLogger>();
    ASSERT_TRUE(logger);

    // Add the logger to the manager.
    manager->addLogger(logger);

    // The manager should have two loggers.
    manager->getLoggers(loggers);
    EXPECT_EQ(loggers.size(), 2);

    // The logger should match the added logger.
    auto result = std::find_if(loggers.begin(), loggers.end(), [logger](const std::shared_ptr<Logger> other) {
        return logger == other;
    });
    ASSERT_NE(result, loggers.end());
}

} // namespace tests
} // namespace nts
