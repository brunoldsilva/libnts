#pragma once

#include <ostream>
#include <istream>

namespace nts {

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

    /// Representation of the object in a console friendly format.
    virtual std::string toString() const = 0;

    /// Writes the object to the stream.
    friend std::ostream& operator<<(std::ostream& outStream, const Serializable& other);

    /// Reads the object from the stream.
    friend std::istream& operator>>(std::istream& inStream, Serializable& other);
};

} // namespace nts
