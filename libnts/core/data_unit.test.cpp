/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <boost/asio.hpp>
#include <gtest/gtest.h>

#include <libnts/core/data_unit.hpp>

namespace nts {
namespace tests {

std::vector<uint8_t> data{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

TEST(DataUnitUnitTests, Accessors)
{
    GenericDataUnit unit;
    unit.setData(data);
    EXPECT_EQ(unit.getData(), data);
}

TEST(DataUnitUnitTests, Serialization)
{
    // Create a data unit.
    GenericDataUnit unitA;
    unitA.setData(data);

    // Serialize the data.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << unitA;

    // Deserialize the data.
    std::istream is(&buffer);
    GenericDataUnit unitB;
    is >> unitB;

    // Compare both unit's data.
    EXPECT_EQ(unitA.getData().size(), data.size());
    EXPECT_EQ(unitA.getData(), unitB.getData());
}

} // namespace tests
} // namespace nts
