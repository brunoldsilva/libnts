/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <libnts/messaging/message.hpp>

#include <algorithm>
#include <sstream>

#include <libnts/messaging/parser.hpp>

namespace nts {

void Message::toStream(std::ostream& outStream) const
{
    for (auto unit : dataUnits)
    {
        unit->toStream(outStream);
    }
}

void Message::fromStream(std::istream& inStream)
{
    if (std::shared_ptr<MessageParser> parser = MessageParser::getInstance())
    {
        std::map<std::string, int> context;
        parser->parse(inStream, context, dataUnits);
    }
}

std::string Message::toString() const
{
    std::stringstream stream;
    stream << "[Message]\n\tProtocols:";
    std::vector<std::string> protocols;
    getProtocolTags(protocols);
    for (auto tag : protocols)
    {
        stream << " " << tag;
    }
    stream << "\n\tSize: " << getSize() << " bytes\n";
    return stream.str();
}

std::string Message::toVerboseString() const
{
    std::stringstream stream;
    stream << "[Message]\n";
    for (const auto unit : dataUnits)
    {
        stream << unit->toString();
    }
    return stream.str();
}

std::size_t Message::getSize() const
{
    std::size_t totalSize = 0;
    for (const auto& unit : dataUnits)
    {
        totalSize += unit->getUnitSize();
    }
    return totalSize;
}

Message& Message::addDataUnit(std::shared_ptr<ProtocolDataUnit> data)
{
    dataUnits.push_back(data);
    return *this;
}

Message& Message::removeDataUnit(const std::string protocol)
{
    if (auto unit = getDataUnit(protocol))
    {
        auto removeItr = std::remove(dataUnits.begin(), dataUnits.end(), unit);
        dataUnits.erase(removeItr);
    }
    return *this;
}

void Message::getDataUnits(std::vector<std::shared_ptr<ProtocolDataUnit>>& outUnits)
{
    outUnits = dataUnits;
}

std::shared_ptr<ProtocolDataUnit> Message::getDataUnit(const std::string protocol)
{
    for (auto unit : dataUnits)
    {
        if (unit->getProtocolTag() == protocol)
        {
            return unit;
        }
    }
    return nullptr;
}

void Message::getProtocolTags(std::vector<std::string>& outTags) const
{
    for (auto unit : dataUnits)
    {
        outTags.push_back(unit->getProtocolTag());
    }
}

bool Message::hasProtocol(const std::string protocolTag) const
{
    for (auto unit : dataUnits)
    {
        if (unit->getProtocolTag() == protocolTag)
        {
            return true;
        }
    }
    return false;
}

} // namespace nts
