/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <chrono>
#include <gtest/gtest.h>

#include <libnts/logging/log.hpp>
#include <libnts/operation/operation.hpp>
#include <libnts/operation/operation.test.hpp>

namespace nts {
namespace tests {

using namespace std::chrono;
using namespace std::chrono_literals;

TEST(OperationUnitTests, Delay)
{
    // Create a simple operation.
    const milliseconds operationDuration{ 5ms };
    auto operation = std::make_shared<FakeOperation>(operationDuration, true);

    // Run the operation without a delay.
    INFO("OperationTests", "Running operation without delay.");
    milliseconds duration = timeOperation(operation);

    // Check the duration for the absence of the delay.
    milliseconds expectedDuration = duration;
    const milliseconds errorMargin{ 1ms };
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());

    // Set a delay the start of the execution.
    const milliseconds operationDelay = 5ms;
    operation->setDelay(operationDelay);

    // Run the operation with a delay.
    INFO("OperationTests", "Running operation with delay.");
    duration = timeOperation(operation);

    // Check the duration for the presence of the delay.
    expectedDuration = operationDuration + operationDelay;
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());

    // Set the operation to repeat after the delay.
    const std::size_t count = 3;
    operation->setCount(count);

    // Run the operation with a delay and repetition.
    INFO("OperationTests", "Running operation with delay and repetition.");
    duration = timeOperation(operation);

    // Check that the operation is only delayed once.
    expectedDuration = (operationDuration * count) + operationDelay;
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());
}

TEST(OperationUnitTests, Count)
{
    // Create a simple operation.
    const milliseconds operationDuration{ 5ms };
    auto operation = std::make_shared<FakeOperation>(operationDuration, true);

    // Run the operation.
    INFO("OperationTests", "Running operation with default count.");
    milliseconds duration = timeOperation(operation);

    // Check that the operation only ran once.
    milliseconds expectedDuration = operationDuration;
    const milliseconds errorMargin{ 1ms };
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());

    // Set the operation to run multiple times.
    const std::size_t operationCount = 3;
    operation->setCount(operationCount);

    // Run the operation.
    INFO("OperationTests", "Running operation with count set to {}.", operationCount);
    duration = timeOperation(operation);

    // Check that operation ran multiple times.
    expectedDuration = operationDuration * operationCount;
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());

    // Set the operation to not run.
    operation->setCount(0);

    // Run the operation.
    INFO("OperationTests", "Running operation with count set to 0.");
    duration = timeOperation(operation);

    // Check that the operation did not run.
    expectedDuration = 0ms;
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());
}

TEST(OperationUnitTests, Interval)
{
    // Create a simple operation.
    const milliseconds operationDuration{ 5ms };
    auto operation = std::make_shared<FakeOperation>(operationDuration, true);

    // Set the operation to run multiple times.
    const std::size_t operationCount = 3;
    operation->setCount(operationCount);

    // Run the operation.
    INFO("OperationTests", "Running operation without intervals.");
    milliseconds duration = timeOperation(operation);

    // Check that the operation ran without intervals.
    milliseconds expectedDuration = operationDuration * operationCount;
    const milliseconds errorMargin{ 1ms };
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());

    // Set an interval between runs.
    const milliseconds interval = 5ms;
    operation->setInterval(interval);

    // Run the operation.
    INFO("OperationTests", "Running operation with intervals.");
    duration = timeOperation(operation);

    // Check for the presence of the intervals.
    expectedDuration = operationDuration * operationCount + interval * (operationCount - 1);
    ASSERT_NEAR(duration.count(), expectedDuration.count(), errorMargin.count());
}

TEST(OperationUnitTests, Timeout)
{
    // Create a simple operation.
    const milliseconds operationDuration{ 10ms };
    auto operation = std::make_shared<FakeOperation>(operationDuration, true);

    // Run the operation.
    INFO("OperationTests", "Running operation without a timeout.");
    milliseconds duration = timeOperation(operation);

    // Check that the operation did not timeout.
    ASSERT_NE(operation->getState(), OperationState::TimeOut);

    // Set a long timeout.
    milliseconds timeout = 15ms;
    operation->setTimeout(timeout);

    // Run the operation.
    INFO("OperationTests", "Running operation with long timeout.");
    duration = timeOperation(operation);

    // Check that the operation did not timeout.
    ASSERT_NE(operation->getState(), OperationState::TimeOut);

    // Set a short timeout.
    timeout = 5ms;
    operation->setTimeout(timeout);

    // Run the operation.
    INFO("OperationTests", "Running operation with short timeout.");
    duration = timeOperation(operation);

    // Check that the operation timed-out.
    ASSERT_EQ(operation->getState(), OperationState::TimeOut);
}

} // namespace tests
} // namespace nts
