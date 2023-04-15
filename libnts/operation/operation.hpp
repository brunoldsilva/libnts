/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

namespace nts {

/// @brief An enumeration of the possible states of execution that an Operation can have.
enum class OperationState
{
    Waiting, /// The operation is yet to run.
    Running, /// The operation is running.
    Done,    /// The operation ran successfully.
    Failed   /// The operation failed to run.
};

/// @brief An enumeration of the methods of execution of an Operation.
enum class ExecutionMethod
{
    Sequential,   /// Runs alone or with parallel operations.
    Asynchronous, /// Runs with async or parallel operations.
    Parallel      /// Runs with any operation.
};

/// @brief An abstract class that provides methods for running a task and specifying how it
/// should be executed in relation to other tasks.
///
/// @details Concrete implementations need to override the 'run' method with their
/// implementation and update the operation state as the task is executed. The execution method
/// property provides a way of organizing groups of tasks that require complex sequencing in
/// their order of execution.
class Operation
{
public:
    /// Destructor.
    virtual ~Operation() = default;

    /// @brief Execute the operation.
    ///
    /// @details This method is meant to be implemented by concrete Operation classes.
    ///
    /// @returns True if the run was successful.
    virtual bool run() = 0;

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

protected:
    /// @brief Set the current state of execution of the Operation.
    ///
    /// @param state The new state of the operation.
    void setState(const OperationState& state);

private:
    /// @brief The current state of execution of the Operation.
    ///
    /// @details Concrete Operation classes are responsible for keeping this
    /// value updated as the Operation is executed.
    OperationState currentState{ OperationState::Waiting };

    /// @brief The operation's preferred method of execution in relation to
    /// other operations.
    ExecutionMethod executionMethod{ ExecutionMethod::Sequential };
};

} // namespace nts
