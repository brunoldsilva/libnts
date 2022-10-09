/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <memory>
#include <vector>

#include <serializable.hpp>

namespace nts {
namespace ss {

/// Maximum transmission unit size.
constexpr uint16_t MTU_SIZE{ 1500 };

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

    /// Send object to the network.
    virtual std::size_t send(srl::Serializable& inData) = 0;

    /// Receive data from the network.
    /// @param outData Must be non-empty (size > 0).
    virtual std::size_t receive(std::vector<uint8_t>& outData) = 0;

    /// Receive object from the network.
    virtual std::size_t receive(srl::Serializable& outData) = 0;
};

} // namespace ss
} // namespace nts
