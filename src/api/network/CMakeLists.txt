# Copyright (c) 2018 The Open-Transactions developers
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set(cxx-sources
  Dht.cpp
  ZAP.cpp
  ZMQ.cpp
)

file(GLOB cxx-install-headers
     "${CMAKE_CURRENT_SOURCE_DIR}/../../../include/opentxs/api/network/*.hpp"
)

set(cxx-headers
  ${cxx-install-headers}
  ${CMAKE_CURRENT_SOURCE_DIR}/Dht.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ZAP.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ZMQ.hpp
)

set(MODULE_NAME opentxs-api-network)

if(WIN32)
  # suppress warnings about exported internal symbols (global log stream objects)
  add_definitions(-DOTLOG_IMPORT)

  # suppress linker warnings about locallly defined imported symbols
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /ignore:4049 /ignore:4217")

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/windll.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/module.rc
    @ONLY
  )

  # we have an extra Windows-specific file to compile
  add_library(${MODULE_NAME} OBJECT
    ${cxx-sources}
    ${cxx-headers}
    ../../core/util/OTWindowsRegistryTools.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/module.rc
  )
else()
  add_library(${MODULE_NAME} OBJECT
    ${cxx-sources}
    ${cxx-headers}
  )
endif()

install(FILES ${cxx-install-headers}
        DESTINATION include/opentxs/api/network
        COMPONENT dev)

set_property(TARGET ${MODULE_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
set_lib_property(${MODULE_NAME})
