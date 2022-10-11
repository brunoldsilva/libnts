/// Copyright Bruno Silva, 2022. All rights reserved.

#include <ethernet.hpp>

#include <netinet/ether.h>

namespace eth {

void VlanTag::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&protocolIdentifier), 2);
    outStream.write(reinterpret_cast<const char*>(&controlInformation), 2);
}

void VlanTag::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&controlInformation), 2);
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

void EthernetDataUnit::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&destinationAddress[0]), 6);
    outStream.write(reinterpret_cast<const char*>(&sourceAddress[0]), 6);
    outStream.write(reinterpret_cast<const char*>(&etherTypeOrLength), 2);
}

void EthernetDataUnit::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&destinationAddress[0]), 6);
    inStream.read(reinterpret_cast<char*>(&sourceAddress[0]), 6);
    inStream.read(reinterpret_cast<char*>(&etherTypeOrLength), 2);
}

std::string EthernetDataUnit::getDestinationAddress() const
{
    return ether_ntoa(reinterpret_cast<const ether_addr*>(&destinationAddress[0]));
}

std::string EthernetDataUnit::getSourceAddress() const
{
    return ether_ntoa(reinterpret_cast<const ether_addr*>(&sourceAddress[0]));
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
