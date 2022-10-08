/// Copyright Bruno Silva, 2022. All rights reserved.

#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <iostream>

#include "raw_session.hpp"

namespace nts {
namespace ss {

RawSession::RawSession()
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

std::size_t RawSession::send(std::vector<uint8_t>& inData)
{
    // Send the data through the socket.
    const std::size_t bytes = socket.send(boost::asio::buffer(inData));
    return bytes;
}

std::size_t RawSession::receive(std::vector<uint8_t>& outData)
{
    // Read data from the socket.
    const std::size_t bytes = socket.receive(boost::asio::buffer(outData));
    return bytes;
}

} // namespace ss
} // namespace nts
