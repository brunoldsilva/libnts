/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <boost/asio.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <libnts/icmp/icmp.hpp>

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

TEST(IcmpParserUnitTests, CanParse)
{
    IcmpParser parser = IcmpParser();

    std::map<std::string, int> context;
    ASSERT_FALSE(parser.canParse(context));

    context["ipv4"] = 1;
    context["protocol"] = 0x01;
    ASSERT_TRUE(parser.canParse(context));
}

TEST(IcmpParserUnitTests, Parse)
{
    IcmpDataUnit payloadA = IcmpDataUnit().setIdentifier(0x01);
    IcmpDataUnit payloadB = IcmpDataUnit().setIdentifier(0x02);

    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    std::istream is(&buffer);
    os << payloadA;
    os << payloadB;

    IcmpParser parser = IcmpParser();
    std::map<std::string, int> context;

    context["ipv4"] = 1;
    context["protocol"] = 0x01;
    auto payloadC = std::dynamic_pointer_cast<IcmpDataUnit>(parser.parse(is, context));
    ASSERT_TRUE(payloadC);
    ASSERT_EQ(payloadC->getIdentifier(), 0x01);
    ASSERT_EQ(context.at("icmp"), 1);

    context.clear();
    context["ipv4"] = 1;
    context["protocol"] = 0x01;
    auto payloadD = std::dynamic_pointer_cast<IcmpDataUnit>(parser.parse(is, context));
    ASSERT_TRUE(payloadD);
    ASSERT_EQ(payloadD->getIdentifier(), 0x02);
    ASSERT_EQ(context.at("icmp"), 1);
}

} // namespace tests
} // namespace icmp
