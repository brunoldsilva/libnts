/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <chrono>
#include <gtest/gtest.h>

#include <libnts/logging/log.hpp>
#include <libnts/messaging/messenger.hpp>
#include <libnts/operation/operation.test.hpp>

namespace nts {
namespace tests {

namespace MessengerTests {

using namespace std::chrono_literals;

constexpr std::chrono::milliseconds operationDuration = 10ms;
constexpr std::chrono::milliseconds errorMargin = 2ms;

const std::map<std::vector<std::size_t>, std::chrono::milliseconds> durationTable{
    { { 0, 0, 0 }, 3 * operationDuration },
    { { 0, 0, 1 }, 3 * operationDuration },
    { { 0, 0, 2 }, 3 * operationDuration },
    { { 0, 1, 0 }, 3 * operationDuration },
    { { 0, 1, 1 }, 2 * operationDuration },
    { { 0, 1, 2 }, 2 * operationDuration },
    { { 0, 2, 0 }, 2 * operationDuration },
    { { 0, 2, 1 }, 2 * operationDuration },
    { { 0, 2, 2 }, 2 * operationDuration },
    { { 1, 0, 0 }, 3 * operationDuration },
    { { 1, 0, 1 }, 3 * operationDuration },
    { { 1, 0, 2 }, 3 * operationDuration },
    { { 1, 1, 0 }, 2 * operationDuration },
    { { 1, 1, 1 }, 1 * operationDuration },
    { { 1, 1, 2 }, 1 * operationDuration },
    { { 1, 2, 0 }, 2 * operationDuration },
    { { 1, 2, 1 }, 1 * operationDuration },
    { { 1, 2, 2 }, 1 * operationDuration },
    { { 2, 0, 0 }, 2 * operationDuration },
    { { 2, 0, 1 }, 2 * operationDuration },
    { { 2, 0, 2 }, 2 * operationDuration },
    { { 2, 1, 0 }, 2 * operationDuration },
    { { 2, 1, 1 }, 1 * operationDuration },
    { { 2, 1, 2 }, 1 * operationDuration },
    { { 2, 2, 0 }, 1 * operationDuration },
    { { 2, 2, 1 }, 1 * operationDuration },
    { { 2, 2, 2 }, 1 * operationDuration },
};

} // namespace MessengerTests

TEST(MessengerUnitTests, ExecutionCombinations)
{
    using namespace std::chrono_literals;
    using namespace std::chrono;

    INFO("MessengerTests", "[0] Sequential [1] Asynchronous [2] Parallel")
    INFO("MessengerTests", "Individual operation duration: {}ms. Error margin: {}ms", MessengerTests::operationDuration.count(), MessengerTests::errorMargin.count())

    std::vector<ExecutionMethod> methods = { ExecutionMethod::Sequential, ExecutionMethod::Asynchronous, ExecutionMethod::Parallel };

    // Run a 3-operation messenger with every possible combination of execution methods.
    for (size_t i = 0; i < methods.size(); i++)
    {
        for (size_t j = 0; j < methods.size(); j++)
        {
            for (size_t k = 0; k < methods.size(); k++)
            {
                INFO("MessengerTests", "Operations: [{}][{}][{}]", i, j, k)
                auto operation1 = std::make_shared<FakeOperation>(MessengerTests::operationDuration, true);
                operation1->setExecutionMethod(methods[i]);
                auto operation2 = std::make_shared<FakeOperation>(MessengerTests::operationDuration, true);
                operation2->setExecutionMethod(methods[j]);
                auto operation3 = std::make_shared<FakeOperation>(MessengerTests::operationDuration, true);
                operation3->setExecutionMethod(methods[k]);

                auto messenger = std::make_shared<Messenger>();
                messenger->push(operation1);
                messenger->push(operation2);
                messenger->push(operation3);

                auto start = steady_clock::now();
                ASSERT_TRUE(messenger->run());
                auto end = steady_clock::now();

                auto actualDuration = duration_cast<milliseconds>(end - start);
                auto expectedDuration = MessengerTests::durationTable.at({ i, j, k });
                INFO("MessengerTests", "Duration: {}ms", actualDuration.count())
                ASSERT_NEAR(actualDuration.count(), expectedDuration.count(), MessengerTests::errorMargin.count());
            }
        }
    }
}

TEST(MessengerUnitTests, OperationRun)
{
    using namespace std::chrono_literals;

    auto operation = std::make_shared<FakeOperation>(100ms, true);
    operation->setCount(5);
    operation->setTimeout(510ms);

    INFO("MessengerTests", "Starting operation.");
    EXPECT_TRUE(operation->run());
    INFO("MessengerTests", "Finished operation.");
}

} // namespace tests
} // namespace nts
