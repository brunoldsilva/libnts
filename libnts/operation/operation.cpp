/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/operation/operation.hpp>

#include <thread>

namespace nts {

bool Operation::run()
{
    using namespace std::chrono;
    using namespace std::chrono_literals;

    if (delay > 0ms)
    {
        std::this_thread::sleep_for(delay);
    }
    currentState = OperationState::Running;

    bool success = true;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; success && i < count; i++)
    {
        success = execute(i);
        auto duration = high_resolution_clock::now() - start;

        if (timeout > 0ms && duration_cast<milliseconds>(duration) >= timeout)
        {
            currentState = OperationState::TimeOut;
            return false;
        }

        if (count > 1 && interval > 0ms && i < count - 1)
        {
            std::this_thread::sleep_for(interval);
        }
    }
    currentState = success ? OperationState::Success : OperationState::Failure;
    return success;
}

OperationState nts::Operation::getState() const
{
    return currentState;
}

ExecutionMethod Operation::getExecutionMethod() const
{
    return executionMethod;
}
void Operation::setExecutionMethod(const ExecutionMethod& method)
{
    executionMethod = method;
}

void Operation::setCount(const std::size_t count)
{
    this->count = count;
}

void Operation::setDelay(const std::chrono::milliseconds& delay)
{
    this->delay = delay;
}

void Operation::setInterval(const std::chrono::milliseconds& interval)
{
    this->interval = interval;
}

void Operation::setTimeout(const std::chrono::milliseconds& timeout)
{
    this->timeout = timeout;
}

} // namespace nts
