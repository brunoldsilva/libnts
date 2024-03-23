#include <gtest/gtest.h>

#include <libnts/config/json_configuration.hpp>

namespace nts {
namespace tests {

namespace JsonConfigTests {

/// The name of the file to load during testing.
const std::string filename{ "json_config_tests.json" };

/// The key to the boolean parameter.
const std::string boolParamKey{ "JsonConfigTests.bool" };

/// The key to the integer parameter.
const std::string intParamKey{ "JsonConfigTests.integer" };

/// The key to the string parameter.
const std::string stringParamKey{ "JsonConfigTests.string" };

/// The expected value of the boolean parameter.
const bool boolParamValue{ true };

/// The expected value of the boolean parameter.
const std::int32_t intParamValue{ 42 };

/// The expected value of the boolean parameter.
const std::string stringParamValue{ "banana" };

} // namespace JsonConfigTests

TEST(JsonConfigurationUnitTests, Constructor)
{
    std::shared_ptr<JsonConfiguration> configuration;

    ASSERT_NO_THROW(configuration = std::make_shared<JsonConfiguration>(JsonConfigTests::filename));

    ASSERT_TRUE(configuration);
}

TEST(JsonConfigurationUnitTests, Accessors)
{
    auto configuration = std::make_shared<JsonConfiguration>(JsonConfigTests::filename);
    ASSERT_TRUE(configuration);

    boost::optional<bool> boolParam = configuration->getBool(JsonConfigTests::boolParamKey);
    ASSERT_TRUE(boolParam.has_value());
    ASSERT_EQ(boolParam.value(), JsonConfigTests::boolParamValue);

    boost::optional<std::int32_t> intParam = configuration->getInt(JsonConfigTests::intParamKey);
    ASSERT_TRUE(intParam.has_value());
    ASSERT_EQ(intParam.value(), JsonConfigTests::intParamValue);

    boost::optional<std::string> stringParam = configuration->getString(JsonConfigTests::stringParamKey);
    ASSERT_TRUE(stringParam.has_value());
    ASSERT_EQ(stringParam.value(), JsonConfigTests::stringParamValue);
}

} // namespace tests
} // namespace nts
