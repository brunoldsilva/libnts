/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#pragma once

#include <memory>
#include <vector>

#include <libnts/operation/operation.hpp>

namespace nts {

/// Forward declarations.
class Message;
class Serial;

using Messages = std::vector<std::shared_ptr<Message>>;

/// @brief Operation that reads messages from a serial.
class ReadOperation : public Operation
{
public:
    /// @brief Constructor.
    ReadOperation(std::shared_ptr<Serial> session, std::shared_ptr<Messages> messages);

    /// @brief Destructor.
    ~ReadOperation() = default;

    /// @brief Container used to store the read messages.
    std::shared_ptr<Messages> getMessages() const;

    /// @brief Serial from which to read messages.
    std::shared_ptr<Serial> getSerial() const;

    /// @brief Container used to store the read messages.
    void setMessages(std::shared_ptr<Messages> messages);

    /// @brief Serial from which to read messages.
    void setSerial(std::shared_ptr<Serial> serial);

protected:
    /// @brief Reads a message from the serial.
    virtual bool execute(const std::size_t iteration) override;

private:
    /// @brief Container used to store the read messages.
    std::shared_ptr<Messages> messages;

    /// @brief Serial from which to read messages.
    std::shared_ptr<Serial> serial;
};

} // namespace nts
