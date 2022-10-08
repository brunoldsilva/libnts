/// Copyright Bruno Silva, 2022. All rights reserved.

#include <gtest/gtest.h>

#include <session.hpp>

namespace nts {
namespace tests {

/// Ping Request to "www.google.com". Must be updated manually.
/// @todo Dynamically create the ping request.
std::vector<uint8_t> pingRequest = { { 0x00, 0x15, 0x5d, 0xf6, 0x7c, 0x15, 0x00, 0x15, 0x5d, 0x3a, 0xe2, 0x9b, 0x08, 0x00, 0x45, 0x00, 0x54, 0x55, 0xc3, 0x40, 0x00, 0x40, 0x01, 0x3a, 0xc4, 0xac, 0x1c, 0x4e, 0x46, 0xd8, 0x3a, 0xd7, 0x84, 0x08, 0x00, 0xa7, 0x07, 0x14, 0xdc, 0x00, 0x01, 0xf1, 0xcd, 0x41, 0x63, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x17, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37 } };

TEST(SessionUnitTests, Create)
{
    // Create a session.
    std::shared_ptr<ss::Session> session = ss::Session::create();
    ASSERT_TRUE(session);
}

TEST(SessionUnitTests, SendVector)
{
    // Create a session to send ping request.
    std::shared_ptr<ss::Session> session = ss::Session::create();
    ASSERT_TRUE(session);

    // Send the request.
    const std::size_t sendSize = session->send(pingRequest);
    std::cout << "Bytes sent: " << sendSize << std::endl;
    ASSERT_EQ(sendSize, pingRequest.size());
}

TEST(DISABLED_SessionUnitTests, ReceiveVector)
{
    // Create a session to send ping request.
    std::shared_ptr<ss::Session> session = ss::Session::create();
    ASSERT_TRUE(session);

    // Send the request.
    const std::size_t sendSize = session->send(pingRequest);
    std::cout << "Bytes sent: " << sendSize << std::endl;
    ASSERT_EQ(sendSize, pingRequest.size());

    // Ping Reply from "www.google.com"
    std::vector<uint8_t> reply(ss::MTU_SIZE, 0);

    // Receive the reply.
    std::size_t receiveSize = session->receive(reply);
    std::cout << "Bytes received: " << receiveSize << std::endl;
    ASSERT_EQ(receiveSize, pingRequest.size());
}

} // namespace tests
} // namespace nts
