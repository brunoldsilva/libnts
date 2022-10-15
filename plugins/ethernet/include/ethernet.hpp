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

/// Virtual Local Area Network tag for Ethernet frames.
class VlanTag : public nts::ProtocolDataUnit
{
public:
    /// Constructor.
    VlanTag() = default;

    /// Deconstructor.
    ~VlanTag() = default;

    // Create a VLAN tag from environment parameters.
    static VlanTag create();

    /// Writes the VLAN tag to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the VLAN tag from the stream.
    /// @note Assumes that the protocol identifier was already extracted from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Tagged frame protocol identifier.
    uint16_t getProtocolIdentifier() const;

    /// Composite of the PCP, DEI and VID.
    uint16_t getControlInformation() const;

    /// Priority Code Point. Assigns priority values to different classes of traffic.
    uint8_t getPCP() const;

    /// Drop Eligible Indicator. Indicates frames eligible to be dropped during congestion.
    uint8_t getDEI() const;

    /// VLAN Identifier.
    uint16_t getVID() const;

    /// Tagged frame protocol identifier.
    VlanTag& setProtocolIdentifier(const uint16_t id);

    /// Composite of the PCP, DEI and VID.
    VlanTag& setControlInformation(const uint16_t info);

    /// Priority Code Point. Assigns priority values to different classes of traffic.
    VlanTag& setPCP(const uint8_t pcp);

    /// Drop Eligible Indicator. Indicates frames eligible to be dropped during congestion.
    VlanTag& setDEI(const uint8_t dei);

    /// VLAN Identifier.
    VlanTag& setVID(const uint16_t vid);

private:
    /// Tagged frame protocol identifier.
    boost::endian::big_uint16_t protocolIdentifier{ (uint16_t)EtherType::VLAN };

    /// Composite of the PCP, DEI and VID.
    boost::endian::big_uint16_t controlInformation{ 0 };
};

/// Data Unit class for the Ethernet II protocol.
class EthernetDataUnit : public nts::ProtocolDataUnit
{
public:
    /// Constructor.
    EthernetDataUnit();

    /// Deconstructor.
    ~EthernetDataUnit() = default;

    // Create an Ethernet frame from environment parameters.
    static EthernetDataUnit create();

    /// Writes the ethernet frame to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the ethernet frame from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Destination MAC address.
    std::string getDestinationAddress() const;

    /// Source MAC address.
    std::string getSourceAddress() const;

    /// Virtual LAN tags.
    void getVlanTags(std::vector<VlanTag>& outTags) const;

    /// Protocol of the payload.
    uint16_t getEtherType() const;

    /// Length of the payload.
    uint16_t getLength() const;

    /// Destination MAC address.
    EthernetDataUnit& setDestinationAddress(const std::string address);

    /// Source MAC address.
    EthernetDataUnit& setSourceAddress(const std::string address);

    /// Virtual LAN tags.
    EthernetDataUnit& addVlanTag(const VlanTag& tag);

    /// Virtual LAN tags.
    EthernetDataUnit& removeVlanTag(const uint16_t id);

    /// Virtual LAN tags.
    EthernetDataUnit& clearVlanTags();

    /// Protocol of the payload.
    EthernetDataUnit& setEtherType(const uint16_t type);

    /// Length of the payload.
    EthernetDataUnit& setLength(const uint16_t length);

private:
    std::vector<boost::endian::big_uint8_t> destinationAddress{ 6, 0 };

    std::vector<boost::endian::big_uint8_t> sourceAddress{ 6, 0 };

    std::vector<VlanTag> vlanTags;

    boost::endian::big_uint16_t etherTypeOrLength{ 0 };
};

} // namespace eth
