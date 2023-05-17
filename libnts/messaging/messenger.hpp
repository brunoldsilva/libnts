/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <future>
#include <memory>
#include <vector>

namespace nts {

/// Forward declarations.
class Operation;

class Messenger
{
public:
    /// Constructor.
    Messenger() = default;

    /// Destructor.
    ~Messenger() = default;

    void push(std::shared_ptr<Operation> operation);

    bool run();

private:
    std::future<bool> runConcurrently(std::shared_ptr<Operation> operation);

    std::vector<std::shared_ptr<Operation>> operations;
};

} // namespace nts
