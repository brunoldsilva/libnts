/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <boost/asio.hpp>

#include <session.hpp>

namespace nts {
namespace ss {

typedef boost::asio::generic::raw_protocol raw_protocol_t;
typedef boost::asio::generic::basic_endpoint<raw_protocol_t> raw_endpoint_t;

/// Communicate using raw sockets.
class RawSession : public Session
{
public:
    /// Constructor.
    RawSession();

    /// Deconstructor.
    ~RawSession() = default;

    /// Send data to the network.
    virtual std::size_t send(std::vector<uint8_t>& inData);

    /// Send object to the network.
    virtual std::size_t send(srl::Serializable& inData);

    /// Receive data from the network.
    /// @param outData Must be non-empty (size > 0).
    virtual std::size_t receive(std::vector<uint8_t>& outData);

    /// Receive object from the network.
    virtual std::size_t receive(srl::Serializable& outData);

private:
    /// Manages asynchronous send and receive operations.
    boost::asio::io_context ioContext;

    /// Handles communication with the physical network layer.
    raw_protocol_t::socket socket;
};

} // namespace ss
} // namespace nts
