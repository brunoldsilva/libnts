#include <libnts/config/composite_configuration.hpp>

#include <algorithm>

namespace nts {

void CompositeConfiguration::push(std::shared_ptr<const Configuration> configuration)
{
    configurations.push_back(configuration);
}

boost::optional<bool> CompositeConfiguration::getBool(const std::string& key) const
{
    for (auto it = configurations.rbegin(); it != configurations.rend(); ++it)
    {
        if (boost::optional<bool> value = (*it)->getBool(key))
        {
            return value;
        }
    }
    return boost::none;
}

boost::optional<std::int32_t> CompositeConfiguration::getInt(const std::string& key) const
{
    for (auto it = configurations.rbegin(); it != configurations.rend(); ++it)
    {
        if (boost::optional<std::int32_t> value = (*it)->getInt(key))
        {
            return value;
        }
    }
    return boost::none;
}

boost::optional<std::string> CompositeConfiguration::getString(const std::string& key) const
{
    for (auto it = configurations.rbegin(); it != configurations.rend(); ++it)
    {
        if (boost::optional<std::string> value = (*it)->getString(key))
        {
            return value;
        }
    }
    return boost::none;
}
} // namespace nts
