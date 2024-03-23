#pragma once

#include <boost/property_tree/ptree.hpp>

#include <libnts/config/configuration.hpp>

namespace nts {

/// @brief A concrete implementation of Configuration that provides access to parameters in
/// JSON configuration files.
///
/// @details This class implements the Configuration interface for getting configuration
/// parameters of different types from JSON files. The constructor takes the filename of
/// the JSON file to use. Nested parameters can be accessed by concatenating multiple
/// keys together, with periods in-between.
///
/// @example
/// auto config = new JsonConfiguration("network_config.json");
/// std::int32_t sourcePort = config->getInt("UDP.Source").value_or(5678);
/// std::int32_t destPort = config->getInt("UDP.Destination").value_or(5678);
class JsonConfiguration : public Configuration
{
public:
    /// @brief Construct a JsonConfiguration from the given file.
    ///
    /// @param filename The name of the json configuration file.
    /// @throws json_parser_error If it fails to open the file.
    JsonConfiguration(const std::string& filename);

    /// Destructor.
    ~JsonConfiguration() = default;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// bool alive = config->getBool("people.alice.lives").value_or(false);
    virtual boost::optional<bool> getBool(const std::string& key) const override;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// std::int32_t age = config->getInt("people.alice.age").value_or(1);
    virtual boost::optional<std::int32_t> getInt(const std::string& key) const override;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// string name = config->getString("people.alice.name").value_or("Alice");
    virtual boost::optional<std::string> getString(const std::string& key) const override;

private:
    /// Enables easy access to the contents of the configuration file.
    boost::property_tree::ptree tree;
};

} // namespace nts
