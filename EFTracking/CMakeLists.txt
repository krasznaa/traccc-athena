# Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration

# Set the package name.
atlas_subdir( EFTracking )

# External(s).
find_package( vecmem COMPONENTS CUDA )

# Build a component library with an example algorithm that uses traccc.
atlas_add_component( EFTracking
   src/*.h src/*.cxx
   DEFINITIONS ALGEBRA_PLUGINS_INCLUDE_ARRAY
   LINK_LIBRARIES vecmem::core vecmem::cuda traccc::core traccc::io
                  traccc::device_common traccc::cuda
                  GaudiKernel AthenaBaseComps )
