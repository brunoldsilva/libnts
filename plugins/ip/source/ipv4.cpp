/// Copyright Bruno Silva, 2022. All rights reserved.

#include <ipv4.hpp>

#include <arpa/inet.h>
#include <sstream>

#include <environment.hpp>

namespace ip {

Ipv4DataUnit::Ipv4DataUnit()
{
    setSourceAddress("0.0.0.0");
    setDestinationAddress("0.0.0.0");
    computeChecksum();
}

Ipv4DataUnit Ipv4DataUnit::create()
{
    Ipv4DataUnit packet;
    if (std::shared_ptr<nts::Environment> environment = nts::Environment::getInstance())
    {
        std::string source{ packet.getSourceAddress() };
        environment->getParam("Protocols.Ipv4.Source", source);
        packet.setSourceAddress(source);

        std::string destination{ packet.getDestinationAddress() };
        environment->getParam("Protocols.Ipv4.Destination", destination);
        packet.setDestinationAddress(destination);

        int TimeToLive{ packet.getTTL() };
        environment->getParam("Protocols.Ipv4.TTL", TimeToLive);
        packet.setTTL(TimeToLive);

        packet.computeChecksum();
    }
    return std::move(packet);
}

void Ipv4DataUnit::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&versionAndIhl), 1);
    outStream.write(reinterpret_cast<const char*>(&dscpAndEcn), 1);
    outStream.write(reinterpret_cast<const char*>(&totalLength), 2);
    outStream.write(reinterpret_cast<const char*>(&identification), 2);
    outStream.write(reinterpret_cast<const char*>(&flagsAndOffset), 2);
    outStream.write(reinterpret_cast<const char*>(&timeToLive), 1);
    outStream.write(reinterpret_cast<const char*>(&protocol), 1);
    outStream.write(reinterpret_cast<const char*>(&checksum), 2);
    outStream.write(reinterpret_cast<const char*>(&sourceAddress), 4);
    outStream.write(reinterpret_cast<const char*>(&destinationAddress), 4);
}

void Ipv4DataUnit::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&versionAndIhl), 1);
    inStream.read(reinterpret_cast<char*>(&dscpAndEcn), 1);
    inStream.read(reinterpret_cast<char*>(&totalLength), 2);
    inStream.read(reinterpret_cast<char*>(&identification), 2);
    inStream.read(reinterpret_cast<char*>(&flagsAndOffset), 2);
    inStream.read(reinterpret_cast<char*>(&timeToLive), 1);
    inStream.read(reinterpret_cast<char*>(&protocol), 1);
    inStream.read(reinterpret_cast<char*>(&checksum), 2);
    inStream.read(reinterpret_cast<char*>(&sourceAddress), 4);
    inStream.read(reinterpret_cast<char*>(&destinationAddress), 4);
}

std::string Ipv4DataUnit::toString() const
{
    std::stringstream stream;
    stream << "[IPv4]\n"
           << "\tVersion: " << (int)getVersion() << " IHL: " << (int)getIHL()
           << "\n\tDSCP: " << (int)getDSCP() << " ECN: " << (int)getECN()
           << "\n\tTotal Length: " << getTotalLength()
           << "\n\tIdentification: " << getIdentification()
           << "\n\tFlags: " << (int)getFlags() << " Offset: " << (int)getFragmentOffset()
           << "\n\tTTL: " << (int)getTTL()
           << "\n\tProtocol: 0x" << std::hex << (int)getProtocol()
           << "\n\tChecksum: 0x" << getHeaderChecksum() << std::dec
           << "\n\tSource Address: " << getSourceAddress()
           << "\n\tDestination Address: " << getDestinationAddress()
           << "\n";
    return stream.str();
}

std::string Ipv4DataUnit::getProtocolTag() const
{
    return "ipv4";
}

void Ipv4DataUnit::computeChecksum()
{
    uint16_t sum = getHeaderSum();
    setHeaderChecksum(static_cast<uint16_t>(~sum));
}

bool Ipv4DataUnit::isChecksumValid() const
{
    uint16_t sum = getHeaderSum();
    return (sum + getHeaderChecksum()) == 0xFFFF;
}

uint8_t Ipv4DataUnit::getVersion() const
{
    return (versionAndIhl >> 4);
}

uint8_t Ipv4DataUnit::getIHL() const
{
    return (versionAndIhl & 0x0F);
}

uint8_t Ipv4DataUnit::getDSCP() const
{
    return (dscpAndEcn >> 2);
}

uint8_t Ipv4DataUnit::getECN() const
{
    return (dscpAndEcn & 0x03);
}

uint16_t Ipv4DataUnit::getTotalLength() const
{
    return totalLength;
}

uint16_t Ipv4DataUnit::getIdentification() const
{
    return identification;
}

uint8_t Ipv4DataUnit::getFlags() const
{
    return (flagsAndOffset >> 13);
}

uint16_t Ipv4DataUnit::getFragmentOffset() const
{
    return (flagsAndOffset & 0x1FFF);
}

uint8_t Ipv4DataUnit::getTTL() const
{
    return timeToLive;
}

uint8_t Ipv4DataUnit::getProtocol() const
{
    return protocol;
}

uint16_t Ipv4DataUnit::getHeaderChecksum() const
{
    return checksum;
}

std::string Ipv4DataUnit::getSourceAddress() const
{
    char string[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, reinterpret_cast<const in_addr*>(&sourceAddress), string, INET_ADDRSTRLEN);
    return string;
}

std::string Ipv4DataUnit::getDestinationAddress() const
{
    char string[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, reinterpret_cast<const in_addr*>(&destinationAddress), string, INET_ADDRSTRLEN);
    return string;
}

Ipv4DataUnit& Ipv4DataUnit::setVersion(const uint8_t version)
{
    versionAndIhl = (versionAndIhl & 0x0F) | (version << 4);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setIHL(const uint8_t ihl)
{
    versionAndIhl = (versionAndIhl & 0xF0) | (ihl & 0x0F);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setDSCP(const uint8_t dscp)
{
    dscpAndEcn = (dscpAndEcn & 0x03) | (dscp << 2);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setECN(const uint8_t ecn)
{
    dscpAndEcn = (dscpAndEcn & 0xFC) | (ecn & 0x03);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setTotalLength(const uint16_t length)
{
    totalLength = length;
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setIdentification(const uint16_t id)
{
    identification = id;
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setFlags(const uint8_t flags)
{
    flagsAndOffset = (flagsAndOffset & 0x1FFF) | (flags << 13);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setFragmentOffset(const uint16_t offset)
{
    flagsAndOffset = (flagsAndOffset & 0xE000) | (offset & 0x1FFF);
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setTTL(const uint8_t ttl)
{
    timeToLive = ttl;
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setProtocol(const uint8_t protocol)
{
    this->protocol = protocol;
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setHeaderChecksum(const uint16_t checksum)
{
    this->checksum = checksum;
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setSourceAddress(const std::string source)
{
    inet_pton(AF_INET, source.c_str(), reinterpret_cast<in_addr*>(&sourceAddress));
    return *this;
}

Ipv4DataUnit& Ipv4DataUnit::setDestinationAddress(const std::string destination)
{
    inet_pton(AF_INET, destination.c_str(), reinterpret_cast<in_addr*>(&destinationAddress));
    return *this;
}

uint16_t Ipv4DataUnit::getHeaderSum() const
{
    // Add up every 16-bit word in the header, excluding the checksum field.
    uint32_t sum = (versionAndIhl << 4) + dscpAndEcn
        + totalLength + identification + flagsAndOffset
        + (timeToLive << 4) + protocol
        + (sourceAddress >> 12) + (sourceAddress & 0xFFFF)
        + (destinationAddress >> 12) + (destinationAddress & 0xFFFF);

    // Carry over.
    while (sum > 0xFFFF)
    {
        sum = (sum >> 4) + (sum & 0xFF);
    }

    return static_cast<uint16_t>(sum);
}

} // namespace ip
