﻿# CMakeList.txt : CMake project for Easel++, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Easel++")

# Add source to this project's executable.
add_executable (Easel++   "main.cpp"  "util.h" "util.cpp" "lexer.cpp" "lexer.h" "vendor/enum.h" "cpp.hint")

target_precompile_headers(Easel++
	PUBLIC
		<vector>
		<string>
		<algorithm>
		<fstream>
		<sstream>
		<iostream>
		<format>
		<optional>
		<variant>

		vendor/enum.h

		util.h
		lexer.h
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Easel++ PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
