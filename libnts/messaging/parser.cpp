/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <libnts/messaging/parser.hpp>

#include <algorithm>

namespace nts {

std::shared_ptr<MessageParser> MessageParser::getInstance()
{
    static std::shared_ptr<MessageParser> messageParser = std::make_shared<MessageParser>();
    return messageParser;
}

void MessageParser::parse(std::istream& inStream, std::map<std::string, int>& inContext, std::vector<std::shared_ptr<ProtocolDataUnit>>& outMessage) const
{
    while (inStream.good() && inStream.peek() >= 0)
    {
        // Look for an appropriate parser for the given context.
        const auto it = std::find_if(parsers.begin(), parsers.end(),
            [&inContext](const std::pair<std::string, std::shared_ptr<ProtocolParser>>& parser) {
                return parser.second->canParse(inContext);
            });

        if (it != parsers.end())
        {
            outMessage.push_back(it->second->parse(inStream, inContext));
        }
        else
        {
            // Use the generic parser to retrieve the remaining data.
            GenericParser generic = GenericParser();
            outMessage.push_back(generic.parse(inStream, inContext));
            break;
        }
    }
}

void MessageParser::addProtocol(std::shared_ptr<ProtocolParser> parser, std::string identifier)
{
    parsers[identifier] = parser;
}

void MessageParser::removeProtocol(std::string identifier)
{
    parsers.erase(identifier);
}

std::shared_ptr<ProtocolParser> MessageParser::getProtocol(std::string identifier) const
{
    if (parsers.find(identifier) != parsers.end())
    {
        return parsers.at(identifier);
    }
    return nullptr;
}

bool GenericParser::canParse(const std::map<std::string, int>& inContext) const
{
    return true;
}

std::shared_ptr<ProtocolDataUnit> GenericParser::parse(std::istream& inStream, std::map<std::string, int>& outContext) const
{
    // Deserialize a generic payload from the stream.
    std::shared_ptr<GenericDataUnit> generic = std::make_shared<GenericDataUnit>();
    generic->fromStream(inStream);

    // Update the context.
    outContext.clear();
    outContext["generic"] = 1;
    outContext["size"] = generic->getData().size();

    return std::move(generic);
}

} // namespace nts
