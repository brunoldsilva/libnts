/// Copyright Bruno Silva, 2022-2023. All rights reserved.

#include <iostream>
#include <net/ethernet.h>
#include <netpacket/packet.h>

#include <libnts/ethernet/raw_session.hpp>

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

std::size_t RawSession::send(Serializable& inData)
{
    // The buffer will hold the data to send.
    boost::asio::streambuf buffer;
    std::ostream os(&buffer);

    // Add the contents of the message to the buffer.
    inData.toStream(os);

    // Send the data through the socket.
    const std::size_t bytes = socket.send(buffer.data());
    return bytes;
}

std::size_t RawSession::receive(std::vector<uint8_t>& outData)
{
    // Read data from the socket.
    const std::size_t bytes = socket.receive(boost::asio::buffer(outData));
    return bytes;
}

std::size_t RawSession::receive(Serializable& outData)
{
    // The buffer will hold the data.
    boost::asio::streambuf buffer;

    // Read data from the socket into the buffer.
    const std::size_t bytes = socket.receive(buffer.prepare(MTU_SIZE));

    // Get the message from the buffer.
    std::istream is(&buffer);
    outData.fromStream(is);

    return bytes;
}

} // namespace ss
} // namespace nts
