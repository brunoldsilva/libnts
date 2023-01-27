/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <parser.hpp>

#include <boost/asio.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <data_unit.hpp>
#include <message.hpp>

namespace nts {
namespace tests {

TEST(ParserUnitTests, Accessors)
{
    std::shared_ptr<MessageParser> messageParser = MessageParser::getInstance();
    ASSERT_TRUE(messageParser);

    std::shared_ptr<GenericParser> genericParser = std::make_shared<GenericParser>();
    ASSERT_TRUE(genericParser);

    messageParser->addProtocol(genericParser, "test");

    std::shared_ptr<ProtocolParser> protocolParser = messageParser->getProtocol("qwerty");
    ASSERT_FALSE(protocolParser);

    protocolParser = messageParser->getProtocol("test");
    ASSERT_TRUE(protocolParser);
    ASSERT_EQ(genericParser, protocolParser);

    messageParser->removeProtocol("qwerty");
    protocolParser = messageParser->getProtocol("test");
    ASSERT_TRUE(protocolParser);

    messageParser->removeProtocol("test");
    protocolParser = messageParser->getProtocol("test");
    ASSERT_FALSE(protocolParser);
}

TEST(ParserUnitTests, Parse)
{
    std::shared_ptr<MessageParser> messageParser = MessageParser::getInstance();
    ASSERT_TRUE(messageParser);

    boost::asio::streambuf buffer;
    std::ostream os(&buffer);
    for (int i = 0; i < 10; i++)
    {
        os << i;
    }
    std::istream is(&buffer);

    std::map<std::string, int> context;
    std::vector<std::shared_ptr<ProtocolDataUnit>> message;
    messageParser->parse(is, context, message);
    ASSERT_EQ(message.size(), 1);

    auto genericData = std::dynamic_pointer_cast<GenericDataUnit>(message[0]);
    ASSERT_TRUE(genericData);
    ASSERT_EQ(genericData->getUnitSize(), 10);
}

} // namespace tests
} // namespace nts
