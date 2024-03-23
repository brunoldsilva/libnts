#include <libnts/core/serializable.hpp>

namespace nts {

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

} // namespace nts
