/// Copyright Bruno Silva, 2022. All rights reserved.

#include <iostream>

#include <session.hpp>
#include "raw_session.hpp"

namespace nts {
namespace ss {

std::shared_ptr<Session> Session::create()
{
    std::shared_ptr<RawSession> rawSession = std::make_shared<RawSession>();
    std::shared_ptr<Session> session = std::static_pointer_cast<Session>(rawSession);
    return session;
}

} // namespace ss
} // namespace nts
