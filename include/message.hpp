/// Copyright Bruno Silva, 2022. All rights reserved.

#pragma once

#include <memory>

#include <data_unit.hpp>
#include <serializable.hpp>

namespace nts {

/// Collection of protocol data units that together represent a message.
class Message : public Serializable
{
public:
    /// Constructor.
    Message() = default;

    /// Deconstructor.
    ~Message() = default;

    /// Writes the message to the stream.
    virtual void toStream(std::ostream& outStream) const;

    /// Reads the message from the stream.
    virtual void fromStream(std::istream& inStream);

    /// Representation of the message in a console friendly format.
    virtual std::string toString() const;

    /// Representation of the message including each individual data unit.
    virtual std::string toVerboseString() const;

    /// Combined size of all data units in the message.
    virtual std::size_t getSize() const;

    /// Adds the data unit to the end of the message.
    Message& addDataUnit(std::shared_ptr<ProtocolDataUnit> data);

    /// Removes a data unit with the given protocol.
    Message& removeDataUnit(const std::string protocol);

    /// All data units contained in the message.
    void getDataUnits(std::vector<std::shared_ptr<ProtocolDataUnit>>& outUnits);

    /// Protocol data unit the the given tag.
    std::shared_ptr<ProtocolDataUnit> getDataUnit(const std::string protocol);

    /// List of protocol contained in the message.
    void getProtocolTags(std::vector<std::string>& outTags) const;

    /// Wether the message contains a protocol with the given tag.
    bool hasProtocol(const std::string protocolTag) const;

private:
    std::vector<std::shared_ptr<ProtocolDataUnit>> dataUnits;
};

} // namespace nts
