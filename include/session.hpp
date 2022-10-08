/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <memory>
#include <vector>

namespace nts {
namespace ss {

/// Send and receive data from the network.
class Session
{
public:
    /// Constructor.
    Session() = default;

    /// Deconstructor.
    ~Session() = default;

    /// Create a session object to communicate with the network.
    static std::shared_ptr<Session> create();

    /// Send data to the network.
    virtual std::size_t send(std::vector<uint8_t>& inData) = 0;

    /// Receive data from the network.
    /// @param outData Must be non-empty (size > 0).
    virtual std::size_t receive(std::vector<uint8_t>& outData) = 0;
};

} // namespace ss
} // namespace nts
