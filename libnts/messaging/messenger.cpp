/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/messaging/messenger.hpp>

#include <libnts/operation/operation.hpp>

namespace nts {

void Messenger::push(std::shared_ptr<Operation> operation)
{
    operations.push_back(operation);
}

bool Messenger::run()
{
    bool success = true;
    std::vector<std::future<bool>> asyncOps;
    std::vector<std::future<bool>> parallelOps;
    // Run each operation according to its method of execution.
    for (auto& operation : operations)
    {
        switch (operation->getExecutionMethod())
        {
            case ExecutionMethod::Sequential:
                // Wait for asynchronous operations to complete.
                for (auto& asyncOp : asyncOps)
                {
                    success &= asyncOp.get();
                }
                asyncOps.clear();
                // Run the operation synchronously.
                success &= operation->run();
                break;
            case ExecutionMethod::Asynchronous:
                // Run in a separate thread but keep track of the result.
                asyncOps.push_back(runConcurrently(operation));
                break;
            case ExecutionMethod::Parallel:
                // Run in a separate thread but keep track of the result.
                parallelOps.push_back(runConcurrently(operation));
                break;
            default:
                break;
        }
        if (!success)
        {
            break;
        }
    }
    // Wait for asynchronous operations to complete.
    for (auto& asyncOp : asyncOps)
    {
        success &= asyncOp.get();
    }
    // Wait for parallel operations to complete.
    for (auto& parallelOp : parallelOps)
    {
        success &= parallelOp.get();
    }
    return success;
}

std::future<bool> Messenger::runConcurrently(std::shared_ptr<Operation> operation)
{
    // Create a future to retrieve the result of the operation.
    auto task = std::packaged_task<bool()>([operation] { return operation->run(); });
    std::future<bool> future = task.get_future();

    // Run the operation in a separate thread.
    std::thread thread(std::move(task));
    thread.detach();

    return future;
}

} // namespace nts
