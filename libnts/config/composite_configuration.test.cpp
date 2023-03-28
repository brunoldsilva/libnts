/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <gtest/gtest.h>

#include <libnts/config/composite_configuration.hpp>
#include <libnts/config/configuration.test.hpp>

namespace nts {
namespace tests {

TEST(CompositeConfigurationUnitTests, Push)
{
    // Create a CompositeConfiguration object.
    auto composite = std::make_shared<CompositeConfiguration>();
    ASSERT_TRUE(composite);

    // Create a TestConfiguration and set a parameter.
    auto config = std::make_shared<ConfigurationTests::TestConfiguration>();
    ASSERT_TRUE(config);
    config->boolParams["test"] = true;

    // Add the test config to the composite and check if the parameter can be retrieved.
    composite->push(config);
    ASSERT_EQ(true, composite->getBool("test").value_or(false));
}

TEST(CompositeConfigurationUnitTests, Override)
{
    // Create a CompositeConfiguration object.
    auto composite = std::make_shared<CompositeConfiguration>();
    ASSERT_TRUE(composite);

    // Create a TestConfiguration and set a parameter.
    auto config1 = std::make_shared<ConfigurationTests::TestConfiguration>();
    ASSERT_TRUE(config1);
    config1->boolParams["test"] = true;

    // Add the test config to the composite and check if the parameter can be retrieved.
    composite->push(config1);
    ASSERT_EQ(true, composite->getBool("test").value_or(false));

    // Create another TestConfiguration and set the same parameter but with a
    // different value.
    auto config2 = std::make_shared<ConfigurationTests::TestConfiguration>();
    ASSERT_TRUE(config2);
    config2->boolParams["test"] = false;

    // Add the test config to the composite and check if the parameter was overriden.
    composite->push(config2);
    ASSERT_EQ(false, composite->getBool("test").value_or(true));
}

} // namespace tests
} // namespace nts
