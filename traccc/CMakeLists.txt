# Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration

# CMake include(s).
cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

# Declare the ATLAS package name.
atlas_subdir( traccc )

# Silence FetchContent warnings with CMake >=3.24.
if( POLICY CMP0135 )
   cmake_policy( SET CMP0135 NEW )
endif()

# Set where to get traccc from.
set( ATLAS_TRACCC_SOURCE
   "URL;https://github.com/acts-project/traccc/archive/refs/tags/v0.10.0.tar.gz;URL_MD5;131399d26e3280c4d7f7ca2995efd256"
   CACHE STRING "Source of the traccc code" )
mark_as_advanced( ATLAS_TRACCC_SOURCE )

# Fetch the traccc code.
FetchContent_Declare( traccc ${ATLAS_TRACCC_SOURCE} )

# Configure the build of traccc.
set( TRACCC_BUILD_TESTING FALSE CACHE BOOL "Build traccc tests" )
set( TRACCC_BUILD_EXAMPLES FALSE CACHE BOOL "Build traccc examples" )
set( TRACCC_USE_SYSTEM_TBB TRUE CACHE BOOL "Use system TBB" )
set( TRACCC_USE_SYSTEM_EIGEN3 TRUE CACHE BOOL "Use system Eigen" )
set( TRACCC_USE_SYSTEM_ACTS TRUE CACHE BOOL "Use system ACTS" )
set( TRACCC_USE_SYSTEM_VECMEM TRUE CACHE BOOL "Use system VecMem" )
set( TRACCC_SETUP_GOOGLETEST FALSE CACHE BOOL "Setup GoogleTest" )
set( ALGEBRA_PLUGINS_USE_SYSTEM_VC TRUE CACHE BOOL "Use system Vc" )
set( DETRAY_USE_SYSTEM_NLOHMANN TRUE CACHE BOOL "Use system nlohmann_json" )

# Configure the build of traccc.
FetchContent_MakeAvailable( traccc )
