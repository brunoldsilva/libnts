/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <boost/endian/arithmetic.hpp>

#include <libnts/core/data_unit.hpp>
#include <libnts/messaging/parser.hpp>

namespace nts {

// Forward declaration.
class Configuration;

} // namespace nts

namespace icmp {

/// Control message types.
enum class IcmpMessageType : uint8_t
{
    EchoReply = 0,
    DestinationUnreachable = 3,
    RedirectMessage = 5,
    EchoRequest = 8,
    RouterAdvertisement = 9,
    RouterSolicitation = 10,
    TimeExceeded = 11,
    BadParameter = 12,
    Timestamp = 13,
    TimestampReply = 14,
    ExtendedEchoRequest = 42,
    ExtendedEchoReply = 43
};

/// Control message sub-types.
enum class IcmpMessageCode : uint8_t
{
    EchoReply = 0,
    EchoRequest = 0,
    RouterAdvertisement = 0,
    RouterSolicitation = 0,
    TTLExpiredInTransit = 0,
    FragmentReassemblyTimeExceeded = 1,
    PointerIndicatesError = 0,
    MissingOption = 1,
    BadLength = 2,
    Timestamp = 0,
    TimestampReply = 0,
    RequestExtendedEcho = 0
};

/// Control message sub-types for the Unreachable message type.
enum class IcmpMessageCode_Unreachable : uint8_t
{
    DestinationNetwork = 0,
    DestinationHost = 1,
    DestinationProtocol = 2,
    DestinationPort = 3,
    FragmentationRequired = 4,
    SourceRouteFailed = 5,
    DestinationNetworkUnkown = 6,
    DestinationHostUnkown = 7,
    SourceHostIsolated = 8,
    NetworkProhibited = 9,
    HostProhibited = 10,
    NetworkToS = 11,
    HostToS = 12,
    CommunicationProhibited = 13,
    HostPrecedenceViolation = 14,
    PrecedenceCutoff = 15
};

/// Control message sub-types for the Redirect message type.
enum class IcmpMessageCode_Redirect : uint8_t
{
    Network = 0,
    Host = 1,
    ToSAndNetwork = 2,
    ToSAndHost = 3
};

/// Control message sub-types for the Extended Reply message type.
enum class IcmpMessageCode_ExtendedReply : uint8_t
{
    NoReply = 0,
    MalformedQuery = 1,
    NoSuchInterface = 2,
    NoSuchTableEntry = 3,
    MultipleInterfacesSatisfyQuery = 4
};

/// Data unit for the ICMP protocol.
class IcmpDataUnit : public nts::ProtocolDataUnit
{
public:
    /// Constructor.
    IcmpDataUnit() = default;

    /// Destructor.
    ~IcmpDataUnit() = default;

    /// Configure the packet with data from the Configuration object.
    IcmpDataUnit& configure(std::shared_ptr<nts::Configuration> config);

    /// Writes the packet to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the packet from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Representation of the message in a console friendly format.
    virtual std::string toString() const;

    /// Unique tag that represents this protocol.
    virtual std::string getProtocolTag() const;

    /// Size of the data unit in bytes.
    virtual std::size_t getUnitSize() const;

    /// Update the checksum field with the correct checksum.
    void computeChecksum();

    /// Verify the integrity of the header with the checksum.
    bool isChecksumValid() const;

    /// Identifies the type of control message.
    uint8_t getType() const;

    /// Identifies the sub-type of control message.
    uint8_t getCode() const;

    /// 16-bit one's complement sum of all 16 bit words in the header and data.
    uint16_t getChecksum() const;

    /// Address of an alternative route. Used in redirect messages.
    std::string getIpAddress() const;

    /// Used to match requests with replies.
    uint16_t getIdentifier() const;

    /// Used to match requests with replies.
    uint16_t getSequenceNumber() const;

    /// MTU of the next hop network in case of a 'datagram is too big' error.
    uint16_t getNextHopMtu() const;

    /// Identifies the type of control message.
    IcmpDataUnit& setType(const uint8_t type);

    /// Identifies the sub-type of control message.
    IcmpDataUnit& setCode(const uint8_t code);

    /// 16-bit one's complement sum of all 16 bit words in the header and data.
    IcmpDataUnit& setChecksum(const uint16_t checksum);

    /// Address of an alternative route. Used in redirect messages.
    IcmpDataUnit& setIpAddress(const std::string address);

    /// Used to match requests with replies.
    IcmpDataUnit& setIdentifier(const uint16_t identifier);

    /// Used to match requests with replies.
    IcmpDataUnit& setSequenceNumber(const uint16_t number);

    /// MTU of the next hop network in case of a 'datagram is too big' error.
    IcmpDataUnit& setNextHopMtu(const uint16_t mtu);

private:
    boost::endian::big_uint8_t type{ (uint8_t)IcmpMessageType::EchoRequest };

    boost::endian::big_uint8_t code{ (uint8_t)IcmpMessageCode::EchoRequest };

    boost::endian::big_uint16_t checksum{ 0 };

    boost::endian::big_uint32_t restOfHeader{ 0 };
};

/// Parser for the ICMP protocol.
class IcmpParser : public nts::ProtocolParser
{
public:
    /// Constructor.
    IcmpParser() = default;

    /// Destructor.
    ~IcmpParser() = default;

    /// Whether the previous protocol is IPv4 and IPv4.Protocol is ICMP.
    virtual bool canParse(const std::map<std::string, int>& inContext) const;

    /// Parse an ICMP payload from the stream.
    virtual std::shared_ptr<nts::ProtocolDataUnit> parse(std::istream& inStream, std::map<std::string, int>& outContext) const;
};

} // namespace icmp
