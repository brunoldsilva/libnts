/// Copyright Bruno Silva, 2022. All rights reserved.

#include <ethernet.hpp>

#include <netinet/ether.h>

namespace eth {

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
