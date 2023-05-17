/// Copyright (C) 2023 Bruno Silva - All Rights Reserved.

#include <libnts/operation/read_operation.hpp>

#include <boost/asio.hpp>

#include <libnts/messaging/message.hpp>
#include <libnts/serialization/serial.hpp>

namespace nts {

ReadOperation::ReadOperation(std::shared_ptr<Serial> session, std::shared_ptr<Messages> messages)
{
}

std::shared_ptr<Messages> ReadOperation::getMessages() const
{
    return messages;
}

std::shared_ptr<Serial> ReadOperation::getSerial() const
{
    return serial;
}

void ReadOperation::setMessages(std::shared_ptr<Messages> messages)
{
    this->messages = messages;
}

void ReadOperation::setSerial(std::shared_ptr<Serial> serial)
{
    this->serial = serial;
}

bool ReadOperation::execute(const std::size_t iteration)
{
    if (!serial)
    {
        return false;
    }
    return false;
}

} // namespace nts
