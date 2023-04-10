/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <chrono>
#include <string>
#include <thread>

#include <libnts/core/operation.hpp>

namespace nts {
namespace tests {

/// @brief A concrete implementation of Operation that is only suitable for testing.
///
/// @details This operation simulates a task that runs for a set duration and then
/// succeeds or fails as specified.
///
/// @code{.cpp}
/// auto operation = new FakeOperation(100ms, true);
/// assert(operation->run() == true);
/// @endcode
class FakeOperation : public Operation
{
public:
    /// @brief Constructor.
    ///
    /// @param duration For how long the operation should run.
    /// @param succeed Whether the operation should succeed.
    FakeOperation(const std::chrono::milliseconds duration, const bool succeed)
    {
        this->duration = duration;
        this->succeed = succeed;
    };

    /// Destructor.
    ~FakeOperation() = default;

    /// @brief Simulate running the operation for a specific duration.
    ///
    /// @return Whether the run was successful.
    virtual bool run() override
    {
        setState(OperationState::Running);
        std::this_thread::sleep_for(duration);
        setState(succeed ? OperationState::Done : OperationState::Failed);
        return succeed;
    };

    /// For how long the operation should run.
    std::chrono::milliseconds duration;

    /// Whether the operation should succeed.
    bool succeed{ true };
};

} // namespace tests
} // namespace nts
