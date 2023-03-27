/// Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <memory>
#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace nts {

/// @brief An abstract class that provides an interface for accessing configuration
/// parameters.
///
/// @details This class defines virtual methods for getting configuration parameters of
/// different types. Each method takes a unique key string that identifies the parameter
/// to retrieve. If the parameter exists, the method returns an optional that contains
/// the value of the parameter. If the parameter does not exist, the optional is empty.
///
/// This class is meant to be inherited and implemented by concrete configuration classes.
/// The concrete classes are responsible for providing the implementation of the virtual
/// methods.
///
/// @example
/// Configuration* config = new MyConfiguration();
/// bool alive = config->getBool("people.alice.lives").value_or(false);
/// std::int32_t age = config->getInt("people.alice.age").value_or(1);
/// std::string name = config->getString("people.alice.name").value_or("Alice");
class Configuration
{
public:
    /// Destructor.
    virtual ~Configuration() = default;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// bool alive = config->getBool("people.alice.lives").value_or(false);
    virtual boost::optional<bool> getBool(const std::string& key) const = 0;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// std::int32_t age = config->getInt("people.alice.age").value_or(1);
    virtual boost::optional<std::int32_t> getInt(const std::string& key) const = 0;

    /// @brief Get the parameter with the given key, if it exists.
    ///
    /// @param key The unique string that identifies the parameter.
    /// @returns An optional that may contain the parameter.
    ///
    /// @example
    /// string name = config->getString("people.alice.name").value_or("Alice");
    virtual boost::optional<std::string> getString(const std::string& key) const = 0;
};

} // namespace nts
