/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <libnts/ethernet/ethernet.hpp>

#include <algorithm>
#include <netinet/ether.h>
#include <sstream>

#include <libnts/config/configuration.hpp>

namespace eth {

VlanTag& VlanTag::configure(std::shared_ptr<nts::Configuration> config)
{
    if (auto id = config->getInt("Protocols.Ethernet.VLAN"))
    {
        setVID(id.value());
    }
    return *this;
}

void VlanTag::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&protocolIdentifier), 2);
    outStream.write(reinterpret_cast<const char*>(&controlInformation), 2);
}

void VlanTag::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&controlInformation), 2);
}

std::string VlanTag::toString() const
{
    std::stringstream stream;
    stream << "[VLAN Tag]\n\t"
           << "PCP: " << (int)getPCP() << " DEI: " << (int)getDEI() << " VID: " << getVID() << "\n";
    return stream.str();
}

std::string VlanTag::getProtocolTag() const
{
    return "vlan";
}

std::size_t VlanTag::getUnitSize() const
{
    return 4;
}

uint16_t VlanTag::getProtocolIdentifier() const
{
    return protocolIdentifier;
}

uint16_t VlanTag::getControlInformation() const
{
    return controlInformation;
}

uint8_t VlanTag::getPCP() const
{
    return (controlInformation >> 13);
}

uint8_t VlanTag::getDEI() const
{
    return ((controlInformation >> 12) & 0x01);
}

uint16_t VlanTag::getVID() const
{
    return (controlInformation & 0x0FFF);
}

VlanTag& VlanTag::setProtocolIdentifier(const uint16_t id)
{
    protocolIdentifier = id;
    return *this;
}

VlanTag& VlanTag::setControlInformation(const uint16_t info)
{
    controlInformation = info;
    return *this;
}

VlanTag& VlanTag::setPCP(const uint8_t pcp)
{
    controlInformation = (controlInformation & 0x1FFF) | (pcp << 13);
    return *this;
}

VlanTag& VlanTag::setDEI(const uint8_t dei)
{
    controlInformation = (controlInformation & 0xEFFF) | (dei << 12);
    return *this;
}

VlanTag& VlanTag::setVID(const uint16_t vid)
{
    controlInformation = (controlInformation & 0xF000) | (vid & 0x0FFF);
    return *this;
}

EthernetDataUnit::EthernetDataUnit()
{
    setDestinationAddress("0:0:0:0:0:0");
    setSourceAddress("0:0:0:0:0:0");
}

EthernetDataUnit& EthernetDataUnit::configure(std::shared_ptr<nts::Configuration> config)
{
    if (auto destination = config->getString("Protocols.Ethernet.Destination"))
    {
        setDestinationAddress(destination.value());
    }
    if (auto source = config->getString("Protocols.Ethernet.Source"))
    {
        setSourceAddress(source.value());
    }
    return *this;
}

void EthernetDataUnit::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&destinationAddress[0]), 6);
    outStream.write(reinterpret_cast<const char*>(&sourceAddress[0]), 6);
    for (const VlanTag& tag : vlanTags)
    {
        tag.toStream(outStream);
    }
    outStream.write(reinterpret_cast<const char*>(&etherTypeOrLength), 2);
}

void EthernetDataUnit::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&destinationAddress[0]), 6);
    inStream.read(reinterpret_cast<char*>(&sourceAddress[0]), 6);
    inStream.read(reinterpret_cast<char*>(&etherTypeOrLength), 2);
    while (getEtherType() == (uint16_t)EtherType::VLAN)
    {
        VlanTag tag;
        tag.fromStream(inStream);
        addVlanTag(tag);
        inStream.read(reinterpret_cast<char*>(&etherTypeOrLength), 2);
    }
}

std::string EthernetDataUnit::toString() const
{
    std::stringstream stream;
    stream << "[Ethernet]"
           << "\n\tDestination: " << getDestinationAddress()
           << "\n\tSource: " << getSourceAddress() << "\n\t"
           << (getLength() <= 1500 ? "Length: 0x" : "EtherType: 0x")
           << std::hex << getLength() << std::dec << "\n";
    std::vector<VlanTag> tags;
    getVlanTags(tags);
    for (const auto& tag : tags)
    {
        stream << tag.toString();
    }
    return stream.str();
}

std::string EthernetDataUnit::getProtocolTag() const
{
    return "ethernet";
}

std::size_t EthernetDataUnit::getUnitSize() const
{
    // Two 6-byte addresses plus a 2-byte EtherType/Length field.
    const std::size_t headerSize = 6 + 6 + 2;

    // Include the VLAN tags in the total size.
    std::size_t totalSize = headerSize;
    for (const auto& tag : vlanTags)
    {
        totalSize += tag.getUnitSize();
    }
    return totalSize;
}

std::string EthernetDataUnit::getDestinationAddress() const
{
    return ether_ntoa(reinterpret_cast<const ether_addr*>(&destinationAddress[0]));
}

std::string EthernetDataUnit::getSourceAddress() const
{
    return ether_ntoa(reinterpret_cast<const ether_addr*>(&sourceAddress[0]));
}

void EthernetDataUnit::getVlanTags(std::vector<VlanTag>& outTags) const
{
    outTags = vlanTags;
}

uint16_t EthernetDataUnit::getEtherType() const
{
    return etherTypeOrLength;
}

uint16_t EthernetDataUnit::getLength() const
{
    return etherTypeOrLength;
}

EthernetDataUnit& EthernetDataUnit::setDestinationAddress(const std::string address)
{
    ether_addr addr = *ether_aton(address.c_str());
    for (int i = 0; i < 6; i++)
    {
        destinationAddress[i] = addr.ether_addr_octet[i];
    }
    return *this;
}

EthernetDataUnit& EthernetDataUnit::setSourceAddress(const std::string address)
{
    ether_addr addr = *ether_aton(address.c_str());
    for (int i = 0; i < 6; i++)
    {
        sourceAddress[i] = addr.ether_addr_octet[i];
    }
    return *this;
}

EthernetDataUnit& EthernetDataUnit::addVlanTag(const VlanTag& tag)
{
    vlanTags.push_back(tag);
    return *this;
}

EthernetDataUnit& EthernetDataUnit::removeVlanTag(const uint16_t id)
{
    // Move all tags with matching IDs to the back of the vector.
    auto back = std::remove_if(vlanTags.begin(), vlanTags.end(),
        [id](const VlanTag& tag) { return tag.getVID() == id; });

    // Remove those tags.
    vlanTags.erase(back, vlanTags.end());
    return *this;
}

EthernetDataUnit& EthernetDataUnit::clearVlanTags()
{
    vlanTags.clear();
    return *this;
}

EthernetDataUnit& EthernetDataUnit::setEtherType(const uint16_t type)
{
    etherTypeOrLength = type;
    return *this;
}

EthernetDataUnit& EthernetDataUnit::setLength(const uint16_t length)
{
    etherTypeOrLength = length;
    return *this;
}

bool EthernetParser::canParse(const std::map<std::string, int>& inContext) const
{
    return inContext.empty();
}

std::shared_ptr<nts::ProtocolDataUnit> EthernetParser::parse(std::istream& inStream, std::map<std::string, int>& outContext) const
{
    // Deserialize a frame from the stream.
    std::shared_ptr<EthernetDataUnit> frame = std::make_shared<EthernetDataUnit>();
    frame->fromStream(inStream);

    // Update the context.
    outContext.clear();
    outContext["ethernet"] = 1;
    outContext["type"] = static_cast<int>(frame->getEtherType());

    return std::move(frame);
}

} // namespace eth
