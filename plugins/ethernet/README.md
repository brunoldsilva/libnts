# Ethernet Plugin

This plugin aims to provide Ethernet protocol communication to the Network Testing Suite.

## Ethernet II

An Ethernet frame is a data-link layer protocol data unit. Its structure is as follows:

     1  2  3  4  5  6  1  2  3  4  5  6  1  2  1              n  bytes
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+
    |   Destination   |     Source      | Type|     Payload     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+

Destination (6 bytes): Hardware/MAC address of the target host.

Source (6 bytes): Hardware/MAC address of the source host.

EtherType or Length (2 bytes): Specifies the protocol of the payload, in the case of the value being greater than 1500, or the length of the payload, in the case of the value being lower than or equal to 1500.

## IEEE 802.1Q - Virtual Local Area Network Tags

The IEEE 802.1Q standard defines a system of VLAN tagging for Ethernet frames. The structure of a VLAN tag is as follows:

    0        8        16       24       32 bits
    +--------+--------+--------+--------+
    |      TPID       |       TCI       |
    +--------+--------+--------+--------+

Tag Protocol Identifier (2 bytes): Is set to a value of 0x8100 to identify the frame as a tagged frame. This field is located at the same position as the EtherType field.

Tag Control Information (2 bytes): Is composed of the Priority Code Point (3 bits), the Drop Eligible Indicator (1 bit) and the VLAN Identifier (12 bits).

An Ethernet frame can have up to two VLAN tags and they are placed between the Source Hardware Address and the EtherType fields, like so:

     1  2  3  4  5  6  1  2  3  4  5  6  1  2  3  4  1  2  3  4  1  2  1              n  bytes
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+
    |   Destination   |     Source      |    Tag    |    Tag    | Type|     Payload     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+

## Implementation

| Class             | Description                                       |
|------             |------------                                       |
| EthernetDataUnit  | Ethernet protocol as a serializable data unit.    |
| EtherType         | Enumeration of the most common payload protocols. |
| VlanTag           | IEEE 802.1Q Virtual LAN tag.                      |
