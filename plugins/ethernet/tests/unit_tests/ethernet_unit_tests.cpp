/// Copyright Bruno Silva, 2022. All rights reserved.

#include <boost/asio.hpp>
#include <iostream>
#include <gtest/gtest.h>

#include <ethernet.hpp>
#include <session.hpp>

namespace eth {
namespace tests {

const std::string emptyAddress{ "0:0:0:0:0:0" };
const std::string destinationAddress{ "0:15:5d:f6:7c:15" };
const std::string sourceAddress{ "0:15:5d:3a:eb:87" };
const uint16_t etherType{ (uint16_t)EtherType::IPv4 };
const uint16_t length{ 0xbeef };

TEST(EthernetUnitTests, Accessors)
{
    EthernetDataUnit frame;
    EXPECT_EQ(frame.getDestinationAddress(), emptyAddress);
    EXPECT_EQ(frame.getSourceAddress(), emptyAddress);
    EXPECT_EQ(frame.getEtherType(), 0);
    EXPECT_EQ(frame.getLength(), 0);

    frame.setDestinationAddress(destinationAddress);
    EXPECT_EQ(frame.getDestinationAddress(), destinationAddress);

    frame.setSourceAddress(sourceAddress);
    EXPECT_EQ(frame.getSourceAddress(), sourceAddress);

    frame.setEtherType(etherType);
    EXPECT_EQ(frame.getEtherType(), etherType);

    frame.setLength(length);
    EXPECT_EQ(frame.getLength(), length);
}

TEST(EthernetUnitTests, Serialization)
{
    // Create a frame.
    EthernetDataUnit frameA;
    frameA.setDestinationAddress(destinationAddress);
    frameA.setSourceAddress(sourceAddress);
    frameA.setEtherType(etherType);

    // Serialize the frame.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << frameA;

    // Deserialize the frame.
    std::istream is(&buffer);
    EthernetDataUnit frameB;
    is >> frameB;

    // Compare both frames.
    EXPECT_EQ(frameA.getDestinationAddress(), frameB.getDestinationAddress());
    EXPECT_EQ(frameA.getSourceAddress(), frameB.getSourceAddress());
    EXPECT_EQ(frameA.getEtherType(), frameB.getEtherType());
}

TEST(EthernetUnitTests, Session)
{
    // Create a session.
    std::shared_ptr<nts::ss::Session> session = nts::ss::Session::create();
    ASSERT_TRUE(session);

    // Create an empty Ethernet frame.
    EthernetDataUnit frame;
    frame.setDestinationAddress(destinationAddress);
    frame.setSourceAddress(sourceAddress);
    frame.setEtherType(etherType);

    // Send the frame.
    const std::size_t sendSize = session->send(frame);
    std::cout << "Bytes sent: " << sendSize << std::endl;
    ASSERT_GT(sendSize, 0);
}

} // namespace tests
} // namespace eth
