/// Copyright Bruno Silva. 2022. All rights reserved.

#include <data_unit.hpp>

#include <boost/asio.hpp>

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
