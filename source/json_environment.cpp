/// Copyright Bruno Silva, 2022. All rights reserved.

#include "json_environment.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <iostream>

namespace nts {

void JsonEnvironment::openConfigFile(const std::string fileName)
{
    try
    {
        boost::property_tree::read_json(fileName, tree);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught an exception while parsing the contents of " << fileName << ": "
                  << e.what() << '\n';
    }
}

bool JsonEnvironment::getParam(const std::string param, int& outParam)
{
    boost::optional<int> value = tree.get_optional<int>(param);
    if (value.has_value())
    {
        outParam = value.get();
    }
    return value.has_value();
}

bool JsonEnvironment::getParam(const std::string param, std::string& outParam)
{
    boost::optional<std::string> value = tree.get_optional<std::string>(param);
    if (value.has_value())
    {
        outParam = value.get();
    }
    return value.has_value();
}
} // namespace nts
