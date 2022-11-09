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
const std::string sourceAddress{ "0:15:5d:3a:ea:bd" };
const uint16_t etherType{ (uint16_t)EtherType::IPv4 };
const uint16_t length{ 0xbeef };

TEST(EthernetUnitTests, Accessors)
{
    EthernetDataUnit frame;
    EXPECT_EQ(frame.getDestinationAddress(), emptyAddress);
    EXPECT_EQ(frame.getSourceAddress(), emptyAddress);
    EXPECT_EQ(frame.getEtherType(), 0);
    EXPECT_EQ(frame.getLength(), 0);

    std::vector<VlanTag> tags;
    frame.getVlanTags(tags);
    EXPECT_EQ(tags.size(), 0);

    frame.setDestinationAddress(destinationAddress);
    EXPECT_EQ(frame.getDestinationAddress(), destinationAddress);

    frame.setSourceAddress(sourceAddress);
    EXPECT_EQ(frame.getSourceAddress(), sourceAddress);

    frame.setEtherType(etherType);
    EXPECT_EQ(frame.getEtherType(), etherType);

    frame.setLength(length);
    EXPECT_EQ(frame.getLength(), length);

    VlanTag tagA = VlanTag().setVID(0xfff);
    VlanTag tagB = VlanTag().setVID(0x111);
    frame.addVlanTag(tagA);
    frame.addVlanTag(tagB);

    frame.getVlanTags(tags);
    EXPECT_EQ(tags.size(), 2);
    EXPECT_EQ(tagA.getVID(), tags[0].getVID());

    frame.removeVlanTag(0xfff);

    frame.getVlanTags(tags);
    EXPECT_EQ(tags.size(), 1);

    frame.clearVlanTags();

    frame.getVlanTags(tags);
    EXPECT_EQ(tags.size(), 0);
}

TEST(EthernetUnitTests, Serialization)
{
    // Create a VLAN tag.
    VlanTag tag = VlanTag().setVID(0xfff);

    // Create a frame.
    EthernetDataUnit frameA = EthernetDataUnit().setDestinationAddress(destinationAddress).setSourceAddress(sourceAddress).addVlanTag(tag).setEtherType(etherType);

    // Serialize the frame.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << frameA;

    // Deserialize the frame.
    std::istream is(&buffer);
    EthernetDataUnit frameB;
    is >> frameB;

    // Compare both frames.
    EXPECT_EQ(frameA.getDestinationAddress(), destinationAddress);
    EXPECT_EQ(frameA.getSourceAddress(), sourceAddress);
    EXPECT_EQ(frameA.getEtherType(), etherType);

    // And their tags.
    std::vector<VlanTag> tags;
    frameB.getVlanTags(tags);
    ASSERT_GT(tags.size(), 0);
    EXPECT_EQ(tags[0].getVID(), 0xfff);
}

TEST(VlanTagUnitTests, Accessors)
{
    VlanTag tag;
    EXPECT_EQ(tag.getProtocolIdentifier(), (uint16_t)EtherType::VLAN);
    EXPECT_EQ(tag.getControlInformation(), 0);
    EXPECT_EQ(tag.getPCP(), 0);
    EXPECT_EQ(tag.getDEI(), 0);
    EXPECT_EQ(tag.getVID(), 0);

    tag.setProtocolIdentifier((uint16_t)EtherType::IPv4);
    EXPECT_EQ(tag.getProtocolIdentifier(), (uint16_t)EtherType::IPv4);

    tag.setPCP(2);
    EXPECT_EQ(tag.getPCP(), 2);

    tag.setDEI(1);
    EXPECT_EQ(tag.getDEI(), 1);

    tag.setVID(0xfff);
    EXPECT_EQ(tag.getVID(), 0xfff);
}

TEST(VlanTagUnitTests, Serialization)
{
    // Create a tag.
    VlanTag tagA;
    tagA.setProtocolIdentifier((uint16_t)EtherType::IPv4).setPCP(2).setDEI(1).setVID(3);

    // Serialize the tag.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    os << tagA;

    std::istream is(&buffer);
    VlanTag tagB;

    // Tags assume that the protocol identifier has already been removed before deserializing.
    boost::endian::big_int16_t protocolIdentifier{ 0 };
    is.read(reinterpret_cast<char*>(&protocolIdentifier), 2);

    // Deserialize the tag.
    is >> tagB;

    // Compare both tags.
    EXPECT_EQ(tagA.getProtocolIdentifier(), protocolIdentifier);
    EXPECT_EQ(tagA.getPCP(), tagB.getPCP());
    EXPECT_EQ(tagA.getDEI(), tagB.getDEI());
    EXPECT_EQ(tagA.getVID(), tagB.getVID());
}

} // namespace tests
} // namespace eth
