/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <vector>

#include <serializable.hpp>

namespace nts {

/// Base class for Protocol Data Units that can be sent over the network.
class ProtocolDataUnit : public srl::Serializable
{
public:
    /// Constructor.
    ProtocolDataUnit() = default;

    /// Deconstructor.
    ~ProtocolDataUnit() = default;

    /// Writes the object to the stream.
    virtual void toStream(std::ostream& outStream) const = 0;

    /// Reads the object from the stream.
    virtual void fromStream(std::istream& inStream) = 0;
};

/// Holds generic data in a byte array.
class GenericDataUnit : public ProtocolDataUnit
{
public:
    /// Constructor.
    GenericDataUnit() = default;

    /// Deconstructor.
    ~GenericDataUnit() = default;

    /// Writes the object to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the object from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Data stored in this unit.
    std::vector<uint8_t>& getData();

    /// Data stored in this unit.
    GenericDataUnit& setData(const std::vector<uint8_t>& inData);

private:
    /// Generic data.
    std::vector<uint8_t> data;
};

} // namespace nts
