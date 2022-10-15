/// Copyright Bruno Silva, 2022. All rights reserved.

#include <gtest/gtest.h>

#include <environment.hpp>

namespace nts {
namespace tests {

TEST(EnvironmentUnitTests, Accessors)
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
