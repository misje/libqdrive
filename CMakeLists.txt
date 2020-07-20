cmake_minimum_required(VERSION 3.1.0)

project(qdrive LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTOMOC ON)

add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Wunreachable-code
	-Wcast-align
	-Wcast-qual
	-Wdisabled-optimization
	-Wformat=2
	-Werror=format-security
	-Winit-self
	-Wmissing-declarations
	-Wmissing-include-dirs
	-Wredundant-decls
	-Wold-style-cast
	-Woverloaded-virtual
	-Wshadow
	-Wsign-conversion
	-Wstrict-overflow=5
	-Wswitch-default
	-Wundef
	-Wno-unused
	-Wno-variadic-macros
	-Wswitch-enum
	-fstack-protector-strong
	-D_FORTIFY_SOURCE=2
	-Werror
	)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(
		-fmax-errors=5
		-Wlogical-op
		-Wnoexcept
		-Wstrict-null-sentinel
		-Wimplicit-fallthrough=3
		-foptimize-strlen
		-Wno-psabi
		)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(
		# Clang doesn't like qCDebug():
		-Wno-gnu-zero-variadic-macro-arguments
		)
endif()

find_package(
	Qt5
	REQUIRED
	COMPONENTS
		Core
		DBus
	CONFIG
	)

add_library(${PROJECT_NAME} STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/AvailableSpace.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/BlockDevice.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/DBusObject.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/Drive.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/FileSystem.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/Monitor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/Partition.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/QDrive.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive/Version.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/src/AvailableSpace.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/BlockDevice.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/DBusObject.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Drive.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/FileSystem.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Monitor.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Partition.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/QDrive.cpp"
	)
target_include_directories(${PROJECT_NAME}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/qdrive"
	)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Qt5::Core
		Qt5::DBus
	)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_link_libraries(${PROJECT_NAME} PRIVATE stdc++)
endif()
