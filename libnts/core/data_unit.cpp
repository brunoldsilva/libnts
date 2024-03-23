#include <libnts/core/data_unit.hpp>

#include <boost/asio.hpp>
#include <sstream>

namespace nts {

void GenericDataUnit::toStream(std::ostream& outStream) const
{
    for (const uint8_t& byte : data)
    {
        outStream.write(reinterpret_cast<const char*>(&byte), 1);
    }
}

void GenericDataUnit::fromStream(std::istream& inStream)
{
    data.clear();
    char byte;
    for (int i = 0; i < 1500; i++)
    {
        inStream.read(&byte, 1);
        if (inStream.fail())
        {
            break;
        }
        data.push_back(byte);
    }
}

std::string GenericDataUnit::toString() const
{
    std::stringstream stream;
    stream << "[GenericDataUnit]\n\t" << std::hex;
    for (const auto& byte : data)
    {
        stream << "0x" << (int)byte << " ";
    }
    stream << std::dec << "\n";
    return stream.str();
}

std::string GenericDataUnit::getProtocolTag() const
{
    return "generic";
}

std::size_t GenericDataUnit::getUnitSize() const
{
    return data.size();
}

std::vector<uint8_t>& GenericDataUnit::getData()
{
    return data;
}

GenericDataUnit& GenericDataUnit::setData(const std::vector<uint8_t>& inData)
{
    data = inData;
    return *this;
}

} // namespace nts
