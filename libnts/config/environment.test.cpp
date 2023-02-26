/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <gtest/gtest.h>

#include <libnts/config/environment.hpp>

namespace nts {
namespace tests {

TEST(DISABLED_EnvironmentUnitTests, Accessors)
{
    std::shared_ptr<nts::Environment> environment = nts::Environment::getInstance();
    ASSERT_TRUE(environment);

    std::string stringParam;
    EXPECT_TRUE(environment->getParam("EnvironmentUnitTests.string", stringParam));
    EXPECT_EQ(stringParam, "banana");

    int integerParam;
    EXPECT_TRUE(environment->getParam("EnvironmentUnitTests.integer", integerParam));
    EXPECT_EQ(integerParam, 42);
}

} // namespace tests
} // namespace nts
