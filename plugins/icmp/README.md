# ICMP Plugin

This plugin aims to provide Internet Control Message Protocol communication to the Network Testing Suite.

## Internet Control Message Protocol

The ICMP protocol is a supporting protocol in the Internet protocol suite. An ICMP packet is a network-layer data unit and its structure is as follows:

    0                 1                 2                 3                 4 bytes
    +-----------------+-----------------+-----------------+-----------------+
    |      Type       |      Code       |             Checksum              |
    +-----------------+-----------------+-----------------+-----------------+
    |                             Rest of Header                            |
    +-----------------+-----------------+-----------------+-----------------+

Type (1 byte): The Type is an 8-bit field that identifies the control message. Together with the Code field it indicates the type of information that the message contains.

Code (1 byte): The Code is an 8-bit field that provides additional context about the type of control message.

Checksum (2 bytes): The 16-bit Checksum field is used for error-checking of the header. It is the 16 bit one's complement of the one's complement sum of all 16 bit words in the header and data.

Rest of Header (4-bytes): The contents of this field vary based on the Type and Code.

### Echo Message

    0                 1                 2                 3                 4 bytes
    +-----------------+-----------------+-----------------+-----------------+
    |      Type       |      Code       |             Checksum              |
    +-----------------+-----------------+-----------------+-----------------+
    |            Identifier             |          Sequence Number          |
    +-----------------+-----------------+-----------------+-----------------+

The echo message is used to test the connectivity between two hosts. Upon receiving an echo request message, the host should send an echo reply back to the source host with the same payload, identifier and sequence number.

## Implementation

| Class               | Description                        |
| ------------------- | ---------------------------------- |
| IcmpDataUnit        | ICMP as a serializable data unit.  |
| IcmpMessageType     | Enumeration of ICMP message types. |
| IcmpMessageCode\_\* | Enumeration of ICMP message codes. |
| IcmpParser          | Extracts ICMP payload from steams. |
