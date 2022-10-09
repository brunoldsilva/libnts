/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <ostream>
#include <istream>

namespace nts {
namespace srl {

/// Object that can be written and read from data streams.
class Serializable
{
public:
    /// Constructor.
    Serializable() = default;

    /// Deconstructor.
    ~Serializable() = default;

    /// Writes the object to the stream.
    virtual void toStream(std::ostream& outStream) const = 0;

    /// Reads the object from the stream.
    virtual void fromStream(std::istream& inStream) = 0;

    /// Writes the object to the stream.
    friend std::ostream& operator<<(std::ostream& outStream, const Serializable& other);

    /// Reads the object from the stream.
    friend std::istream& operator>>(std::istream& inStream, Serializable& other);
};

std::ostream& operator<<(std::ostream& outStream, const Serializable& other)
{
    other.toStream(outStream);
    return outStream;
};

std::istream& operator>>(std::istream& inStream, Serializable& other)
{
    other.fromStream(inStream);
    return inStream;
};

} // namespace srl
} // namespace nts
