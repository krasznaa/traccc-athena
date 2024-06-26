# Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration

# Set up the project.
cmake_minimum_required(VERSION 3.20)
project(traccc_athena VERSION 0.1.0 LANGUAGES CXX)

# Use C++17 with CUDA. Athena by default still uses C++14. But traccc needs
# C++17.
set(CMAKE_CUDA_STANDARD 17 CACHE STRING "CUDA C++ standard")

# Find the base release.
find_package(Athena 25.0.9 REQUIRED)

# Set up CTest.
atlas_ctest_setup()

# Disable the undefined behaviour sanitier (in debug builds). It does not work
# correctly with vecmem.
string(REPLACE "-fsanitize=undefined" ""
   CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# Set up the analysis project from the repository.
atlas_project(USE Athena ${Athena_VERSION})

# Generate an environment setup script. This call makes sure that whatever
# "external" we use in this analysis project, is set up correctly in the
# runtime environment.
lcg_generate_env(SH_FILE "${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh")
install(FILES "${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh"
   DESTINATION .)

# Set up CPack. This is necessary to be able to build TGZ files correctly from
# the compiled code. Making it possible to use the code on the grid.
atlas_cpack_setup()
