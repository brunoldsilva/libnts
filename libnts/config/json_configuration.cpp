#include <json_configuration.hpp>

#include <boost/property_tree/json_parser.hpp>

namespace nts {

JsonConfiguration::JsonConfiguration(const std::string& filename)
{
    boost::property_tree::read_json(filename, tree);
}

boost::optional<bool> JsonConfiguration::getBool(const std::string& key) const
{
    return tree.get_optional<bool>(key);
}

boost::optional<std::int32_t> JsonConfiguration::getInt(const std::string& key) const
{
    return tree.get_optional<std::int32_t>(key);
}

boost::optional<std::string> JsonConfiguration::getString(const std::string& key) const
{
    return tree.get_optional<std::string>(key);
}

} // namespace nts
