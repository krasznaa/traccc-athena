# Copyright (C) 2023 CERN for the benefit of the ATLAS collaboration

# Set the package name.
atlas_subdir( EFTracking )

# Build a component library with an example algorithm that uses traccc.
atlas_add_component( EFTracking
   src/*.h src/*.cxx
   DEFINITIONS ALGEBRA_PLUGINS_INCLUDE_ARRAY
   LINK_LIBRARIES vecmem::core traccc::core GaudiKernel AthenaBaseComps )
