/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <boost/property_tree/ptree.hpp>

#include <environment.hpp>

namespace nts {

/// Environment object that reads parameters from a json file.
class JsonEnvironment : public nts::Environment
{
public:
    /// Constructor.
    JsonEnvironment() = default;

    /// Deconstructor.
    ~JsonEnvironment() = default;

    /// Open the configuration file that contains the parameters.
    void openConfigFile(const std::string fileName);

    /// Try to get the value of the parameter as an int.
    virtual bool getParam(const std::string param, int& outParam);

    /// Try to get the value of the parameter as a string.
    virtual bool getParam(const std::string param, std::string& outParam);

private:
    boost::property_tree::ptree tree;
};

} // namespace nts
