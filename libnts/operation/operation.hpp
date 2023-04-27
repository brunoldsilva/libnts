/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <chrono>
#include <cstddef>

namespace nts {

/// @brief An enumeration of the possible states that an Operation can have.
enum class OperationState
{
    Waiting, /// The operation is yet to run.
    Running, /// The operation is running.
    Success, /// The operation ran successfully.
    Failure, /// The operation failed during execution.
    TimeOut, /// The operation timed-out during execution.
};

/// @brief An enumeration of the methods of execution of an Operation.
enum class ExecutionMethod
{
    Sequential,   /// Runs alone or with parallel operations.
    Asynchronous, /// Runs with async or parallel operations.
    Parallel      /// Runs with any operation.
};

/// @brief An abstract class that provides methods for running a task and specifying how it
/// should be executed.
///
/// @details Concrete implementations need to override the 'execute' method with their
/// implementation. Users of this class must call the 'run' method to execute the operation.
///
/// Use the 'setCount', 'setDelay', 'setInterval' and 'setTimeout' methods to configure how the
/// operation should run. The executionMethod property serves only as a way to organize
/// operations (it has no internal use).
///
/// @code{.cpp}
/// auto operation = new MyOperation();
/// operation->setInterval(3ms);
/// operation->setCount(100);
/// operation->run();
/// @endcode
class Operation
{
public:
    /// Destructor.
    virtual ~Operation() = default;

    /// @brief Run the operation.
    ///
    /// @returns Whether the run was successful.
    bool run();

    /// @brief Get the current state of execution of the Operation.
    ///
    /// @code{.cpp}
    /// assert(operation->getState() == OperationState::Waiting);
    /// operation->run();
    /// assert(operation->getState() == OperationState::Done);
    /// @endcode
    OperationState getState() const;

    /// @brief Get the operation's preferred method of execution in relation to
    /// other operations.
    ///
    /// @details It is up to the caller of `run()` to ensure that the operation
    /// is executed in the given method.
    ///
    /// @code{.cpp}
    /// if (operation->getExecutionMethod() == ExecutionMethod::Parallel) {
    ///     std::thread op_thread([operation]{ operation->run(); });
    ///     op_thread.detach();
    /// }
    /// @endcode
    ExecutionMethod getExecutionMethod() const;

    /// @brief Set the operation's preferred method of execution in relation to
    /// other operations.
    ///
    /// @details It is up to the caller of `run()` to ensure that the operation
    /// is executed in the given method.
    ///
    /// @param method The method of execution to be used when calling the operation.
    void setExecutionMethod(const ExecutionMethod& method);

    /// @brief Set how many times the operation should execute.
    ///
    /// @param count Number of times the operation should execute.
    void setCount(const std::size_t count);

    /// @brief Set how long to wait before running the operation.
    ///
    /// @param delay Time in ms to wait before the running the operation.
    void setDelay(const std::chrono::milliseconds& delay);

    /// @brief Set how long to wait between each execution of the operation.
    ///
    /// @param interval Time in ms to wait before each execution of the operation.
    void setInterval(const std::chrono::milliseconds& interval);

    /// @brief Set how long the operation can take to run successfully.
    ///
    /// @param timeout Time in ms after which the run will fail.
    void setTimeout(const std::chrono::milliseconds& timeout);

protected:
    /// @brief Execute the operation once.
    ///
    /// @details This method is called from run() any number of times. It is meant to be
    /// implemented by concrete Operation classes.
    ///
    /// @param iteration Current execution iteration. Starts at 0.
    /// @return Whether the execution was successful.
    virtual bool execute(const std::size_t iteration) = 0;

private:
    /// @brief The current state of execution of the Operation.
    ///
    /// @details Concrete Operation classes are responsible for keeping this
    /// value updated as the Operation is executed.
    OperationState currentState{ OperationState::Waiting };

    /// @brief The operation's preferred method of execution in relation to
    /// other operations.
    ExecutionMethod executionMethod{ ExecutionMethod::Sequential };

    /// @brief Number of times the operation should execute.
    std::size_t count{ 1 };

    /// @brief Time in ms to wait before the running the operation.
    std::chrono::milliseconds delay{ 0 };

    /// @brief Time in ms to wait before each execution of the operation.
    std::chrono::milliseconds interval{ 0 };

    /// @brief Time in ms after which the run will fail.
    std::chrono::milliseconds timeout{ 0 };
};

} // namespace nts
