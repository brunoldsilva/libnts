/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <boost/endian/arithmetic.hpp>

#include <data_unit.hpp>

namespace eth {

/// Identifies the protocol of the payload.
enum class EtherType : uint16_t
{
    IPv4 = 0x0800,
    ARP = 0x0806,
    RARP = 0x8035,
    VLAN = 0x8100,
    IPv6 = 0x86DD,
};

/// Data Unit class for the Ethernet II protocol.
class EthernetDataUnit : public nts::ProtocolDataUnit
{
public:
    /// Constructor.
    EthernetDataUnit();

    /// Deconstructor.
    ~EthernetDataUnit() = default;

    /// Writes the ethernet frame to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the ethernet frame from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Destination MAC address.
    std::string getDestinationAddress() const;

    /// Source MAC address.
    std::string getSourceAddress() const;

    /// Protocol of the payload.
    uint16_t getEtherType() const;

    /// Length of the payload.
    uint16_t getLength() const;

    /// Destination MAC address.
    EthernetDataUnit& setDestinationAddress(const std::string address);

    /// Source MAC address.
    EthernetDataUnit& setSourceAddress(const std::string address);

    /// Protocol of the payload.
    EthernetDataUnit& setEtherType(const uint16_t type);

    /// Length of the payload.
    EthernetDataUnit& setLength(const uint16_t length);

private:
    std::vector<boost::endian::big_uint8_t> destinationAddress{ 6, 0 };

    std::vector<boost::endian::big_uint8_t> sourceAddress{ 6, 0 };

    boost::endian::big_uint16_t etherTypeOrLength{ 0 };
};

} // namespace eth
