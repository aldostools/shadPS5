# SPDX-FileCopyrightText: Copyright 2025 shadPS5 Emulator Project
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(shadPS5)

add_subdirectory(externals)
include_directories(src)

set(COMMON src/core/common/types.h
)

add_executable(shadPS5 ${COMMON} main.cpp "src/core/loader/param_json_parser.h")

target_link_libraries(shadPS5 PRIVATE nlohmann_json::nlohmann_json)

if (WIN32)
    target_sources(shadPS5 PRIVATE src/shadPS5.rc)
endif()