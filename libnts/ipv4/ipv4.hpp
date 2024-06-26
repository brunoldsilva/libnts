#include <boost/endian/arithmetic.hpp>

#include <libnts/core/data_unit.hpp>
#include <libnts/messaging/parser.hpp>

namespace nts {

// Forward declaration.
class Configuration;

} // namespace nts

namespace ip {

/// Identifier of the encapsulated protocol.
enum class IpPayloadProtocols : uint8_t
{
    ICMP = 0x01,
    IGMP = 0x02,
    TCP = 0x06,
    UDP = 0x11,
};

/// Data unit for the IPv4 protocol.
class Ipv4DataUnit : public nts::ProtocolDataUnit
{
public:
    /// Constructor.
    Ipv4DataUnit();

    /// Destructor.
    ~Ipv4DataUnit() = default;

    /// Configure the packet with data from the Configuration object.
    Ipv4DataUnit& configure(std::shared_ptr<nts::Configuration> config);

    /// Writes the packet to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the packet from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Representation of the packet in a console friendly format.
    virtual std::string toString() const;

    /// Unique tag that represents this protocol.
    virtual std::string getProtocolTag() const;

    /// Size of the data unit in bytes.
    virtual std::size_t getUnitSize() const;

    /// Update the checksum field with the correct checksum.
    void computeChecksum();

    /// Verify the integrity of the header with the checksum.
    bool isChecksumValid() const;

    /// Header protocol version.
    uint8_t getVersion() const;

    /// Internet Header Length (IHL) specifies the number of 32-bit words in the header.
    uint8_t getIHL() const;

    /// Differentiated Services Code Point (DSCP) is used to classify network traffic.
    uint8_t getDSCP() const;

    /// Explicit Congestion Notification (ECN) allows notification of congestion without
    /// dropping packets.
    uint8_t getECN() const;

    /// Size of the entire packet in bytes, including header and data.
    uint16_t getTotalLength() const;

    /// Identifier for grouping fragments of a single IP packet.
    uint16_t getIdentification() const;

    /// A 3-bit field of Reserved, Don't Fragment (DF) and More Fragments (MF) flags.
    uint8_t getFlags() const;

    /// Specifies the offset of the current fragment relative to the beginning of the original
    /// packet in units of eight-byte blocks.
    uint16_t getFragmentOffset() const;

    /// Limits the lifetime of the packet.
    uint8_t getTTL() const;

    /// Protocol of the payload.
    uint8_t getProtocol() const;

    /// 16-bit one's complement sum of all 16 bit words in the header.
    uint16_t getHeaderChecksum() const;

    /// IPv4 address of the sender.
    std::string getSourceAddress() const;

    /// IPv4 address of the recipient.
    std::string getDestinationAddress() const;

    /// Header protocol version.
    Ipv4DataUnit& setVersion(const uint8_t version);

    /// Internet Header Length (IHL) specifies the number of 32-bit words in the header.
    Ipv4DataUnit& setIHL(const uint8_t ihl);

    /// Differentiated Services Code Point (DSCP) is used to classify network traffic.
    Ipv4DataUnit& setDSCP(const uint8_t dscp);

    /// Explicit Congestion Notification (ECN) allows notification of congestion without
    /// dropping packets.
    Ipv4DataUnit& setECN(const uint8_t ecn);

    /// Size of the entire packet in bytes, including header and data.
    Ipv4DataUnit& setTotalLength(const uint16_t length);

    /// Identifier for grouping fragments of a single IP packet.
    Ipv4DataUnit& setIdentification(const uint16_t id);

    /// A 3-bit field of Reserved, Don't Fragment (DF) and More Fragments (MF) flags.
    Ipv4DataUnit& setFlags(const uint8_t flags);

    /// Specifies the offset of the current fragment relative to the beginning of the original
    /// packet in units of eight-byte blocks.
    Ipv4DataUnit& setFragmentOffset(const uint16_t offset);

    /// Limits the lifetime of the packet.
    Ipv4DataUnit& setTTL(const uint8_t ttl);

    /// Protocol of the payload.
    Ipv4DataUnit& setProtocol(const uint8_t protocol);

    /// 16-bit one's complement sum of all 16 bit words in the header.
    Ipv4DataUnit& setHeaderChecksum(const uint16_t checksum);

    /// IPv4 address of the sender.
    Ipv4DataUnit& setSourceAddress(const std::string source);

    /// IPv4 address of the recipient.
    Ipv4DataUnit& setDestinationAddress(const std::string destination);

protected:
    // Sum of all 16-bit words in the header, excluding the checksum.
    uint16_t getHeaderSum() const;

private:
    boost::endian::big_uint8_t versionAndIhl{ 0x45 };

    boost::endian::big_uint8_t dscpAndEcn{ 0 };

    boost::endian::big_uint16_t totalLength{ 0x14 };

    boost::endian::big_uint16_t identification{ 0 };

    boost::endian::big_uint16_t flagsAndOffset{ 0 };

    boost::endian::big_uint8_t timeToLive{ 0x40 };

    boost::endian::big_uint8_t protocol{ (uint8_t)IpPayloadProtocols::UDP };

    boost::endian::big_int16_t checksum{ 0 };

    boost::endian::big_uint32_t sourceAddress{ 0 };

    boost::endian::big_uint32_t destinationAddress{ 0 };
};

/// Parser for the IPv4 protocol.
class Ipv4Parser : public nts::ProtocolParser
{
public:
    /// Constructor.
    Ipv4Parser() = default;

    /// Destructor.
    ~Ipv4Parser() = default;

    /// Whether the previous protocol is Ethernet and the EtherType is IPv4.
    virtual bool canParse(const std::map<std::string, int>& inContext) const;

    /// Parse an IPv4 packet from the stream.
    virtual std::shared_ptr<nts::ProtocolDataUnit> parse(std::istream& inStream, std::map<std::string, int>& outContext) const;
};

} // namespace ip
