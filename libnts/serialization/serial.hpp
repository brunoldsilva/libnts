/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <memory>
#include <vector>

namespace nts {

/// Maximum transmission unit size.
constexpr uint16_t MTU_SIZE{ 1500 };

/// Send and receive data from the network.
class Serial
{
public:
    /// @brief Constructor.
    Serial() = default;

    /// @brief Deconstructor.
    ~Serial() = default;

    /// @brief Send data through the serial.
    virtual std::size_t send(std::vector<uint8_t>& inData) = 0;

    /// @brief Receive data from the network.
    ///
    /// @param outData Must be non-empty (size > 0).
    virtual std::size_t receive(std::vector<uint8_t>& outData) = 0;
};

} // namespace nts
