/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace nts {

/// Singleton object that allows access to external parameters.
class Environment
{
public:
    /// Constructor.
    Environment() = default;

    /// Deconstructor.
    ~Environment() = default;

    /// Object instance to access the parameters.
    static std::shared_ptr<Environment> getInstance();

    /// Try to get the value of the parameter as an integer.
    virtual bool getParam(const std::string param, int& outParam) = 0;

    /// Try to get the value of the parameter as a string.
    virtual bool getParam(const std::string param, std::string& outParam) = 0;

    /// Object instance to access the parameters.
    static void setInstance(std::shared_ptr<Environment> instance);

protected:
    static std::shared_ptr<Environment> environment;
};

} // namespace nts
