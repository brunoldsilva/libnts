#pragma once

#include <libnts/config/configuration.hpp>

namespace nts {

/// @brief A concrete implementation of Configuration that abstracts multiple
/// configurations into a single object.
///
/// @details This class provides a method for composing multiple configurations into a
/// single Configuration object. Configurations added in this way will be kept in an
/// ordered container and will be referenced when calling the interface's getter methods.
/// The order in which configurations are pushed is important since parameters from newer
/// configurations will supersede matching parameters from older ones.
///
/// @example
/// auto composite = new CompositeConfiguration();
///
/// auto config1 = new MyConfiguration();
/// config1->setInt("people.alice.age", 0)
/// composite->push(config1);
///
/// auto config2 = new MyConfiguration();
/// config2->setInt("people.alice.age", 1)
/// composite->push(config2);
///
/// std::int32_t age = composite->getInt("people.alice.age");
/// assert(age == 1);
class CompositeConfiguration : public Configuration
{
public:
    /// Constructor.
    CompositeConfiguration() = default;

    /// Destructor.
    ~CompositeConfiguration() = default;

    /// @brief Adds the given configuration to the collection of configurations.
    ///
    /// @details The order in which configurations are pushed is important. If multiple
    /// configurations have the same parameter then only the parameter from the most
    /// recently pushed configuration will be used.
    ///
    /// @param configuration A pointer to the Configuration object.
    ///
    /// @example
    /// auto composite = new CompositeConfiguration();
    /// auto config1 = new MyConfiguration();
    /// composite->push(config1);
    /// auto config2 = new MyConfiguration();
    /// composite->push(config2);
    void push(std::shared_ptr<const Configuration> configuration);

    /// @brief Get the parameter with the given key, if it exists in any configuration.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// bool alive = config->getBool("people.alice.lives").value_or(false);
    virtual boost::optional<bool> getBool(const std::string& key) const override;

    /// @brief Get the parameter with the given key, if it exists in any configuration.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// std::int32_t age = config->getInt("people.alice.age").value_or(1);
    virtual boost::optional<std::int32_t> getInt(const std::string& key) const override;

    /// @brief Get the parameter with the given key, if it exists in any configuration.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// string name = config->getString("people.alice.name").value_or("Alice");
    virtual boost::optional<std::string> getString(const std::string& key) const override;

private:
    /// Container that holds configurations.
    std::vector<std::shared_ptr<const Configuration>> configurations;
};

} // namespace nts
