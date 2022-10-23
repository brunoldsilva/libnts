/// Copyright Bruno Silva, 2022. All rights reserved.

#include <boost/asio.hpp>
#include <iostream>
#include <gtest/gtest.h>

#include <ipv4.hpp>

namespace ip {
namespace tests {

TEST(Ipv4UnitTests, Accessors)
{
    Ipv4DataUnit packet;
    EXPECT_EQ(packet.getVersion(), 4);
    EXPECT_EQ(packet.getIHL(), 5);
    EXPECT_EQ(packet.getDSCP(), 0);
    EXPECT_EQ(packet.getECN(), 0);
    EXPECT_EQ(packet.getTotalLength(), 20);
    EXPECT_EQ(packet.getIdentification(), 0);
    EXPECT_EQ(packet.getFlags(), 0);
    EXPECT_EQ(packet.getFragmentOffset(), 0);
    EXPECT_EQ(packet.getTTL(), 64);
    EXPECT_EQ(packet.getProtocol(), (uint8_t)IpPayloadProtocols::UDP);
    EXPECT_EQ(packet.getSourceAddress(), "0.0.0.0");
    EXPECT_EQ(packet.getDestinationAddress(), "0.0.0.0");

    packet.setVersion(6).setIHL(10).setDSCP(14).setECN(3).setTotalLength(110).setIdentification(0xdead).setFlags(5).setFragmentOffset(18).setTTL(1).setProtocol((uint8_t)IpPayloadProtocols::TCP).setHeaderChecksum(12345).setSourceAddress("1.2.3.4").setDestinationAddress("4.3.2.1");

    EXPECT_EQ(packet.getVersion(), 6);
    EXPECT_EQ(packet.getIHL(), 10);
    EXPECT_EQ(packet.getDSCP(), 14);
    EXPECT_EQ(packet.getECN(), 3);
    EXPECT_EQ(packet.getTotalLength(), 110);
    EXPECT_EQ(packet.getIdentification(), 0xdead);
    EXPECT_EQ(packet.getFlags(), 5);
    EXPECT_EQ(packet.getFragmentOffset(), 18);
    EXPECT_EQ(packet.getTTL(), 1);
    EXPECT_EQ(packet.getProtocol(), (uint8_t)IpPayloadProtocols::TCP);
    EXPECT_EQ(packet.getHeaderChecksum(), 12345);
    EXPECT_EQ(packet.getSourceAddress(), "1.2.3.4");
    EXPECT_EQ(packet.getDestinationAddress(), "4.3.2.1");
}

TEST(Ipv4UnitTests, Serialization)
{
    // Create a packet.
    Ipv4DataUnit packetA = Ipv4DataUnit().setVersion(6).setIHL(10).setDSCP(14).setECN(3).setTotalLength(110).setIdentification(0xdead).setFlags(5).setFragmentOffset(18).setTTL(1).setProtocol((uint8_t)IpPayloadProtocols::TCP).setHeaderChecksum(12345).setSourceAddress("1.2.3.4").setDestinationAddress("4.3.2.1");

    // Serialize the packet.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << packetA;

    // Deserialize the packet.
    std::istream is(&buffer);
    Ipv4DataUnit packetB;
    is >> packetB;

    // Check the values.
    EXPECT_EQ(packetB.getVersion(), 6);
    EXPECT_EQ(packetB.getIHL(), 10);
    EXPECT_EQ(packetB.getDSCP(), 14);
    EXPECT_EQ(packetB.getECN(), 3);
    EXPECT_EQ(packetB.getTotalLength(), 110);
    EXPECT_EQ(packetB.getIdentification(), 0xdead);
    EXPECT_EQ(packetB.getFlags(), 5);
    EXPECT_EQ(packetB.getFragmentOffset(), 18);
    EXPECT_EQ(packetB.getTTL(), 1);
    EXPECT_EQ(packetB.getProtocol(), (uint8_t)IpPayloadProtocols::TCP);
    EXPECT_EQ(packetB.getHeaderChecksum(), 12345);
    EXPECT_EQ(packetB.getSourceAddress(), "1.2.3.4");
    EXPECT_EQ(packetB.getDestinationAddress(), "4.3.2.1");
}

TEST(Ipv4UnitTests, Checksum)
{
    Ipv4DataUnit packet = Ipv4DataUnit().setHeaderChecksum(0x1234);
    EXPECT_FALSE(packet.isChecksumValid());
    packet.computeChecksum();
    EXPECT_TRUE(packet.isChecksumValid());
}

} // namespace tests
} // namespace ip
