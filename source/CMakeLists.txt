# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(SOURCES
    data_unit.cpp
    raw_session.cpp
    raw_session.hpp
    serializable.cpp
    session.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})
