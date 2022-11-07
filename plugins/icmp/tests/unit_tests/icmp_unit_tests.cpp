/// Copyright Bruno Silva, 2022. All rights reserved.

#include <boost/asio.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <icmp.hpp>

namespace icmp {
namespace tests {

TEST(IcmpUnitTests, Accessors)
{
    IcmpDataUnit packet;
    EXPECT_EQ(packet.getType(), (uint8_t)IcmpMessageType::EchoRequest);
    EXPECT_EQ(packet.getCode(), (uint8_t)IcmpMessageCode::EchoRequest);
    EXPECT_EQ(packet.getChecksum(), 0);
    EXPECT_EQ(packet.getIpAddress(), "0.0.0.0");
    EXPECT_EQ(packet.getIdentifier(), 0);
    EXPECT_EQ(packet.getSequenceNumber(), 0);
    EXPECT_EQ(packet.getNextHopMtu(), 0);

    packet.setType((uint8_t)IcmpMessageCode::EchoReply).setCode((uint8_t)IcmpMessageCode::EchoReply).setChecksum(0x1234);

    EXPECT_EQ(packet.getType(), (uint8_t)IcmpMessageType::EchoReply);
    EXPECT_EQ(packet.getCode(), (uint8_t)IcmpMessageCode::EchoReply);
    EXPECT_EQ(packet.getChecksum(), 0x1234);

    packet.setIpAddress("1.2.3.4");
    EXPECT_EQ(packet.getIpAddress(), "1.2.3.4");

    packet.setIdentifier(0x1234);
    EXPECT_EQ(packet.getIdentifier(), 0x1234);

    packet.setSequenceNumber(0x4321);
    EXPECT_EQ(packet.getSequenceNumber(), 0x4321);

    packet.setNextHopMtu(0x1111);
    EXPECT_EQ(packet.getNextHopMtu(), 0x1111);
}

TEST(IcmpUnitTests, Serialization)
{
    IcmpDataUnit packetA = IcmpDataUnit().setType((uint8_t)IcmpMessageCode::EchoReply).setCode((uint8_t)IcmpMessageCode::EchoReply).setChecksum(0x1234).setIpAddress("1.2.3.4");

    // Serialize the packet.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << packetA;

    // Deserialize the packet.
    std::istream is(&buffer);
    IcmpDataUnit packetB;
    is >> packetB;

    EXPECT_EQ(packetB.getType(), (uint8_t)IcmpMessageType::EchoReply);
    EXPECT_EQ(packetB.getCode(), (uint8_t)IcmpMessageCode::EchoReply);
    EXPECT_EQ(packetB.getChecksum(), 0x1234);
    EXPECT_EQ(packetB.getIpAddress(), "1.2.3.4");
}

/// @todo: Add unit tests for the checksum.

} // namespace tests
} // namespace icmp
