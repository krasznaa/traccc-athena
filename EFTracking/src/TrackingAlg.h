//
// Copyright (C) 2023 CERN for the benefit of the ATLAS collaboration
//
#ifndef EFTRACKING_TRACKINGALG_H
#define EFTRACKING_TRACKINGALG_H

// Athena/Gaudi includes.
#include "AthenaBaseComps/AthReentrantAlgorithm.h"

// Acts R&D include(s).
#include <vecmem/memory/host_memory_resource.hpp>
#include <traccc/clusterization/clusterization_algorithm.hpp>

namespace EFTracking
{

   class TrackingAlg : public AthReentrantAlgorithm
   {

   public:
      // Inherit the base class's constructor(s).
      using AthReentrantAlgorithm::AthReentrantAlgorithm;

      /// @name Standard Gaudi algorithm methods.
      /// @{

      /// Initialize the algorithm.
      virtual StatusCode initialize() override;
      /// Execute the algorithm.
      virtual StatusCode execute(const EventContext &ctx) const override;

      /// @}

   private:
      /// Host memory resource to be used by the clusterization "algorithm"
      vecmem::host_memory_resource m_resource;
      /// The clusterization "algorithm"
      traccc::clusterization_algorithm m_alg{m_resource};

   }; // class TrackingAlg

} // namespace EFTracking

#endif // EFTRACKING_TRACKINGALG_H
