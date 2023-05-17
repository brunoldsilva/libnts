/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <vector>

#include <libnts/serialization/serializable.hpp>

namespace nts {

/// Base class for Protocol Data Units that can be sent over the network.
class ProtocolDataUnit : public Serializable
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

    /// Representation of the object in a console friendly format.
    virtual std::string toString() const = 0;

    /// Unique tag that represents this protocol.
    virtual std::string getProtocolTag() const = 0;

    /// Size of the data unit in bytes.
    virtual std::size_t getUnitSize() const = 0;
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

    /// Representation of the object in a console friendly format.
    virtual std::string toString() const;

    /// Unique tag that represents this protocol.
    virtual std::string getProtocolTag() const;

    /// Size of the data unit in bytes.
    virtual std::size_t getUnitSize() const;

    /// Data stored in this unit.
    std::vector<uint8_t>& getData();

    /// Data stored in this unit.
    GenericDataUnit& setData(const std::vector<uint8_t>& inData);

private:
    /// Generic data.
    std::vector<uint8_t> data;
};

} // namespace nts
