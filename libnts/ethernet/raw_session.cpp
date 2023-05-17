/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#include <iostream>
#include <net/ethernet.h>
#include <netpacket/packet.h>

#include <libnts/ethernet/raw_session.hpp>

namespace nts {

RawSerial::RawSerial()
    : socket(ioContext, raw_protocol_t(PF_PACKET, SOCK_RAW))
{
    std::string ifname("eth0");

    sockaddr_ll sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sll_family = PF_PACKET;
    sockaddr.sll_protocol = htons(ETH_P_ALL);
    sockaddr.sll_ifindex = if_nametoindex(ifname.c_str());
    sockaddr.sll_hatype = 1;

    socket.bind(raw_endpoint_t(&sockaddr, sizeof(sockaddr)));
}

std::size_t RawSerial::send(std::vector<uint8_t>& inData)
{
    // Send the data through the socket.
    const std::size_t bytes = socket.send(boost::asio::buffer(inData));
    return bytes;
}

std::size_t RawSerial::receive(std::vector<uint8_t>& outData)
{
    // Read data from the socket.
    const std::size_t bytes = socket.receive(boost::asio::buffer(outData));
    return bytes;
}

} // namespace nts
