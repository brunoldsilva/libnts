# Ethernet Plugin

This plugin aims to provide Ethernet protocol communication to the Network Testing Suite.

## Ethernet II

[Wikipedia](https://en.wikipedia.org/wiki/Ethernet_frame)

An Ethernet frame is a data-link layer protocol data unit. Its structure is as follows:

     1  2  3  4  5  6  1  2  3  4  5  6  1  2  1              n  bytes
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+
    |   Destination   |     Source      | Type|     Payload     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+...........+--+

Destination (6 bytes): Hardware/MAC address of the target host.

Source (6 bytes): Hardware/MAC address of the source host.

EtherType or Length (2 bytes): Specifies the protocol of the payload, in the case of the value being greater than 1500, or the length of the payload, in the case of the value being lower than or equal to 1500.

## Implementation

| Class             | Description                                       |
|------             |------------                                       |
| EthernetDataUnit  | Ethernet protocol as a serializable data unit.    |
| EtherType         | Enumeration of the most common payload protocols. |
