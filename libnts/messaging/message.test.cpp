/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <algorithm>
#include <gtest/gtest.h>

#include <libnts/messaging/message.hpp>

#include <libnts/serialization/serial.hpp>
#include <libnts/ethernet/ethernet.hpp>
#include <libnts/icmp/icmp.hpp>
#include <libnts/ipv4/ipv4.hpp>

namespace nts {
namespace tests {

TEST(MessageUnitTests, DataUnits)
{
    // Create the necessary data units to form an ICMP echo request message.
    auto frame = std::make_shared<eth::EthernetDataUnit>();
    frame->setEtherType((uint16_t)eth::EtherType::IPv4);

    auto tag = eth::VlanTag();
    frame->addVlanTag(tag);

    auto packet = std::make_shared<ip::Ipv4DataUnit>();
    packet->setProtocol((uint8_t)ip::IpPayloadProtocols::ICMP).setTotalLength(38);

    auto message = std::make_shared<icmp::IcmpDataUnit>();
    message->setType((uint8_t)icmp::IcmpMessageType::EchoRequest).setCode((uint8_t)icmp::IcmpMessageCode::EchoRequest);

    auto payload = std::make_shared<GenericDataUnit>(GenericDataUnit().setData({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    // Create an ICMP echo request from the individual data units.
    Message echoRequest = Message().addDataUnit(frame).addDataUnit(packet).addDataUnit(message).addDataUnit(payload);

    // Get a list of the message protocols.
    std::vector<std::string> messageProtocols;
    echoRequest.getProtocolTags(messageProtocols);
    ASSERT_EQ(messageProtocols.size(), 4);

    // Check if the message contains the correct protocols.
    ASSERT_NE(std::find(messageProtocols.begin(), messageProtocols.end(), "icmp"), messageProtocols.end());
    ASSERT_EQ(std::find(messageProtocols.begin(), messageProtocols.end(), "dhcp"), messageProtocols.end());
    ASSERT_TRUE(echoRequest.hasProtocol("ipv4"));
    ASSERT_FALSE(echoRequest.hasProtocol("tcp"));

    auto echoRequestFrame = echoRequest.getDataUnit("ethernet");
    ASSERT_EQ(echoRequestFrame, frame);

    std::vector<std::shared_ptr<ProtocolDataUnit>> echoRequestUnits;
    echoRequest.getDataUnits(echoRequestUnits);
    ASSERT_EQ(echoRequestUnits.size(), 4);

    const bool doesMessageContainGenericPayload = std::find_if(echoRequestUnits.begin(), echoRequestUnits.end(), [](const std::shared_ptr<ProtocolDataUnit> unit) {
        return unit->getProtocolTag() == "generic";
    }) != echoRequestUnits.end();
    ASSERT_TRUE(doesMessageContainGenericPayload);
}

} // namespace tests
} // namespace nts
