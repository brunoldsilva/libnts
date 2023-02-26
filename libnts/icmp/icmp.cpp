/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <libnts/icmp/icmp.hpp>

#include <arpa/inet.h>
#include <sstream>

namespace icmp {

IcmpDataUnit IcmpDataUnit::create()
{
    return IcmpDataUnit();
}

void IcmpDataUnit::toStream(std::ostream& outStream) const
{
    outStream.write(reinterpret_cast<const char*>(&type), 1);
    outStream.write(reinterpret_cast<const char*>(&code), 1);
    outStream.write(reinterpret_cast<const char*>(&checksum), 2);
    outStream.write(reinterpret_cast<const char*>(&restOfHeader), 4);
}

void IcmpDataUnit::fromStream(std::istream& inStream)
{
    inStream.read(reinterpret_cast<char*>(&type), 1);
    inStream.read(reinterpret_cast<char*>(&code), 1);
    inStream.read(reinterpret_cast<char*>(&checksum), 2);
    inStream.read(reinterpret_cast<char*>(&restOfHeader), 4);
}

std::string IcmpDataUnit::toString() const
{
    std::stringstream stream;
    stream << "[ICMP]"
           << "\n\tType: " << (int)getType()
           << "\n\tCode: " << (int)getCode()
           << "\n\tChecksum: 0x" << std::hex << getChecksum() << std::dec
           << "\n";
    return stream.str();
}

std::string IcmpDataUnit::getProtocolTag() const
{
    return "icmp";
}

std::size_t IcmpDataUnit::getUnitSize() const
{
    return 8;
}

void IcmpDataUnit::computeChecksum()
{
    // @todo: The checksum requires access to the payload.
}

bool IcmpDataUnit::isChecksumValid() const
{
    // @todo: The checksum requires access to the payload.
    return true;
}

uint8_t IcmpDataUnit::getType() const
{
    return type;
}

uint8_t IcmpDataUnit::getCode() const
{
    return code;
}

uint16_t IcmpDataUnit::getChecksum() const
{
    return checksum;
}

std::string IcmpDataUnit::getIpAddress() const
{
    char string[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, reinterpret_cast<const in_addr*>(&restOfHeader), string, INET_ADDRSTRLEN);
    return string;
}

uint16_t IcmpDataUnit::getIdentifier() const
{
    return (restOfHeader >> 16);
}

uint16_t IcmpDataUnit::getSequenceNumber() const
{
    return (restOfHeader & 0xFFFF);
}

uint16_t IcmpDataUnit::getNextHopMtu() const
{
    return (restOfHeader & 0xFFFF);
}

IcmpDataUnit& IcmpDataUnit::setType(const uint8_t type)
{
    this->type = type;
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setCode(const uint8_t code)
{
    this->code = code;
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setChecksum(const uint16_t checksum)
{
    this->checksum = checksum;
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setIpAddress(const std::string address)
{
    inet_pton(AF_INET, address.c_str(), reinterpret_cast<in_addr*>(&restOfHeader));
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setIdentifier(const uint16_t identifier)
{
    restOfHeader = (restOfHeader & 0x0000FFFF) | (identifier << 16);
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setSequenceNumber(const uint16_t number)
{
    restOfHeader = (restOfHeader & 0xFFFF0000) | (number);
    return *this;
}

IcmpDataUnit& IcmpDataUnit::setNextHopMtu(const uint16_t mtu)
{
    restOfHeader = (restOfHeader & 0xFFFF0000) | (mtu);
    return *this;
}

bool IcmpParser::canParse(const std::map<std::string, int>& inContext) const
{
    if (inContext.find("ipv4") != inContext.end())
    {
        return inContext.at("protocol") == 0x01;
    }
    return false;
}

std::shared_ptr<nts::ProtocolDataUnit> IcmpParser::parse(std::istream& inStream, std::map<std::string, int>& outContext) const
{
    std::shared_ptr<IcmpDataUnit> payload = std::make_shared<IcmpDataUnit>();
    payload->fromStream(inStream);

    outContext.clear();
    outContext["icmp"] = 1;
    outContext["code"] = static_cast<int>(payload->getCode());
    outContext["type"] = static_cast<int>(payload->getType());

    return std::move(payload);
}

} // namespace icmp
