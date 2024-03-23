#pragma once

#include <map>

#include <libnts/config/configuration.hpp>

namespace nts {
namespace ConfigurationTests {

/// A concrete implementation of Configuration suitable for testing only.
class TestConfiguration : public Configuration
{
public:
    /// Constructor.
    TestConfiguration() = default;

    /// Destructor.
    ~TestConfiguration() = default;

    /// Get the parameter with the given key, if it exists.
    virtual boost::optional<bool> getBool(const std::string& key) const
    {
        auto value = boolParams.find(key);
        if (value != boolParams.end())
        {
            return boost::optional<bool>((*value).second);
        }
        return boost::none;
    };

    /// Get the parameter with the given key, if it exists.
    virtual boost::optional<std::int32_t> getInt(const std::string& key) const
    {
        auto value = intParams.find(key);
        if (value != intParams.end())
        {
            return boost::optional<std::int32_t>((*value).second);
        }
        return boost::none;
    };

    /// Get the parameter with the given key, if it exists.
    virtual boost::optional<std::string> getString(const std::string& key) const
    {
        auto value = stringParams.find(key);
        if (value != stringParams.end())
        {
            return boost::optional<std::string>((*value).second);
        }
        return boost::none;
    };

    /// Collection of boolean type parameters.
    std::map<std::string, bool> boolParams;

    /// Collection of integer type parameters.
    std::map<std::string, std::int32_t> intParams;

    /// Collection of string type parameters.
    std::map<std::string, std::string> stringParams;
};

} // namespace ConfigurationTests
} // namespace nts
