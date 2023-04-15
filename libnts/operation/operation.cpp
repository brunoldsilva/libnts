/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/operation/operation.hpp>

namespace nts {

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

void Operation::setState(const OperationState& state)
{
    currentState = state;
}

} // namespace nts
