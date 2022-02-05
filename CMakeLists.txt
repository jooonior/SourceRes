cmake_minimum_required(VERSION 3.10)

project(SourceRes VERSION 2.0)

# Add code.
set(SOURCE
	src/SourceRes.cpp
)
set(HEADERS
	src/SourceRes.h
)

# Include Source SDK.
include_directories(${HL2SDK}/common)
include_directories(${HL2SDK}/public)
include_directories(${HL2SDK}/public/tier0)
include_directories(${HL2SDK}/public/tier1)
include_directories(${HL2SDK}/game/client)
include_directories(${HL2SDK}/game/shared)

# Build with static runtime.
# https://stackoverflow.com/questions/1618927/cmake-microsoft-visual-studio-and-monolithic-runtimes/1618985#1618985
if(MSVC)
	foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
		string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
	endforeach()
endif()

# Create the plugin.
add_library(SourceRes SHARED
	${SOURCE}
	${HEADERS})

# Link SDK libraries.
target_link_libraries(SourceRes ${HL2SDK}/lib/public/tier0.lib)
target_link_libraries(SourceRes ${HL2SDK}/lib/public/tier1.lib)

# Copy built binary to mod directory.
add_custom_command(
	TARGET SourceRes
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SourceRes>
		"${PROJECT_SOURCE_DIR}/mod/addons"
)