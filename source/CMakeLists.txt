# Copyright Bruno Silva, 2022-2023. All rights reserved.

# Get all source files in the current directory.
set(SOURCES
    data_unit.cpp
    environment.cpp
    json_environment.cpp
    json_environment.hpp
    message.cpp
    parser.cpp
    raw_session.cpp
    raw_session.hpp
    serializable.cpp
    session.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})
