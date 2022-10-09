/// Copyright Bruno Silva, 2022. All rights reserved.

#include <serializable.hpp>

namespace nts {
namespace srl {

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
