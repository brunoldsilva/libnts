# Internet Protocol Plugin

This plugin aims to provide Internet Protocol communication to the Network Testing Suite.

## Internet Protocol Version 4

An IPv4 packet is an internet-layer protocol data unit. Its structure is as follows:

    0                 1                 2                 3                 4 bytes
    +-----------------+-----------------+-----------------+-----------------+
    | Version and IHL |  DSCP and ECN   |           Total Length            |
    +-----------------+-----------------+-----------------+-----------------+
    |          Identification           |    Flags and Fragment Offset      |
    +-----------------+-----------------+-----------------+-----------------+
    |  Time To Live   |    Protocol     |          Header Checksum          |
    +-----------------+-----------------+-----------------+-----------------+
    |                           Source IP Address                           |
    +-----------------+-----------------+-----------------+-----------------+
    |                        Destination IP Address                         |
    +-----------------+-----------------+-----------------+-----------------+
    |                                Options                                |
    +-----------------+-----------------+-----------------+-----------------+

Version and IHL (1 byte): The Version is a 4-bit field that identifies the packet as IPv4 or IPv6. The 4-bit Internet Header Length (IHL) contains the number of 32-bit words in the header including options. 

DSCP and ECN (1 byte): The Differentiated Services Code Point (DSCP) is a 6-bit field that is used to specify differentiated services per RFC 2474. The 2-bit Explicit Congestion Notification (ECN) allows end-to-end notification of network congestion without dropping packets.

Total Length (2 bytes): This field defines the entire packet size in bytes including header and data.

Identification (2 bytes): Primarily used for uniquely identifying the group of fragments of a single packet.

Flags and Fragment Offset (2 bytes): The 3-bit Flags field is used to control or identify packets as Don't Fragment (DF) or More Fragments (MF). The 13-bit Fragment Offset field specifies the offset of a particular fragment relative to the beginning of the original un-fragmented packet, in bytes.

Time To Live (1 byte): This field is used to limit the lifetime of the packet to prevent network failure in the event of a routing loop.

Protocol (1 byte): This field specifies the protocol of the encapsulated data.

Header Checksum (2 bytes): The 16-bit IPv4 header checksum field is used for error-checking of the header. It is the 16 bit one's complement of the one's complement sum of all 16 bit words in the header.

Source Address (4 bytes): This field is the IPv4 address of the sender of the packet.

Destination Address (4 bytes): This field is the IPv4 address of the receiver of the packet.

## Implementation

| Class              | Description                                       |
|------              |------------                                       |
| Ipv4DataUnit       | Internet Protocol as a serializable data unit.    |
| IpPayloadProtocols | Enumeration of the most common payload protocols. |

## Examples

### Basic IPv4 Operation

```cpp
// #include <ipv4.hpp>

// Create a packet using environment params and set the protocol to UDP.
ip::Ipv4DataUnit packet = ip::Ipv4DataUnit::create().setProtocol((uint8_t)ip::IpPayloadProtocols::UDP);

// Recompute the checksum.
packet.computeChecksum();

// Serialize the packet.
os << packet;
```
