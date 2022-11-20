/// Copyright Bruno Silva, 2022. All rights reserved.

#include <ethernet.hpp>

#include <algorithm>
#include <netinet/ether.h>
#include <sstream>

#include <environment.hpp>

namespace eth {

VlanTag VlanTag::create()
{
    VlanTag tag;
    std::shared_ptr<nts::Environment> environment = nts::Environment::getInstance();
    if (environment)
    {
        int id{ tag.getVID() };
        environment->getParam("Protocols.Ethernet.VLAN", id);
        tag.setVID(id);
    }
    return std::move(tag);
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
    controlInformation = (controlInformation & 0x01FF) | (pcp << 13);
    return *this;
}

VlanTag& VlanTag::setDEI(const uint8_t dei)
{
    controlInformation = (controlInformation & 0x0EFF) | (dei << 12);
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

EthernetDataUnit EthernetDataUnit::create()
{
    EthernetDataUnit frame;
    std::shared_ptr<nts::Environment> environment = nts::Environment::getInstance();
    if (environment)
    {
        std::string destination{ frame.getDestinationAddress() };
        environment->getParam("Protocols.Ethernet.Destination", destination);
        frame.setDestinationAddress(destination);

        std::string source{ frame.getSourceAddress() };
        environment->getParam("Protocols.Ethernet.Source", source);
        frame.setSourceAddress(source);
    }
    return std::move(frame);
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
    return (vlanTags.size() == 0) ? "ethernet" : "ethernet vlan";
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

} // namespace eth
