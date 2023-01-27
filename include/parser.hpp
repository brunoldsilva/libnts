/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#pragma once

#include <map>
#include <memory>
#include <vector>

#include <data_unit.hpp>

namespace nts {

/// Base class for protocol data unit parsers.
class ProtocolParser
{
public:
    /// Constructor.
    ProtocolParser() = default;

    /// Destructor.
    ~ProtocolParser() = default;

    /// Whether this parser can be used in the given context.
    virtual bool canParse(const std::map<std::string, int>& inContext) const = 0;

    /// Parse a single protocol data unit from the stream.
    virtual std::shared_ptr<ProtocolDataUnit> parse(std::istream& inStream, std::map<std::string, int>& outContext) const = 0;
};

/// Singleton class for parsing several protocol data units.
class MessageParser
{
public:
    /// Constructor.
    MessageParser() = default;

    /// Destructor.
    ~MessageParser() = default;

    /// Parser instance used to deserialize messages.
    static std::shared_ptr<MessageParser> getInstance();

    /// Deserialize all known protocols in the stream.
    /// Unrecognized protocols will be converted to a GenericDataUnit.
    void parse(std::istream& inStream, std::map<std::string, int>& inContext, std::vector<std::shared_ptr<ProtocolDataUnit>>& outMessage) const;

    /// Add a parser for a specific protocol.
    void addProtocol(std::shared_ptr<ProtocolParser> parser, std::string identifier);

    /// Remove a specific protocol parser.
    void removeProtocol(std::string identifier);

    /// Protocol parser with the given identifier.
    std::shared_ptr<ProtocolParser> getProtocol(std::string identifier) const;

private:
    std::map<std::string, std::shared_ptr<ProtocolParser>> parsers;
};

/// Generic data unit parser for unspecified protocols.
class GenericParser : public ProtocolParser
{
public:
    /// Constructor.
    GenericParser() = default;

    /// Destructor.
    ~GenericParser() = default;

    /// This parser can always be used, no matter the context.
    virtual bool canParse(const std::map<std::string, int>& inContext) const final;

    /// Extract all available data as a single generic data unit.
    virtual std::shared_ptr<ProtocolDataUnit> parse(std::istream& inStream, std::map<std::string, int>& outContext) const final;
};

} // namespace nts
