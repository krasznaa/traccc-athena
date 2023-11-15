//
// Copyright (C) 2023 CERN for the benefit of the ATLAS collaboration
//

// Local include(s).
#include "TrackingAlg.h"

DECLARE_COMPONENT(EFTracking::TrackingAlg)

namespace EFTracking
{

   StatusCode TrackingAlg::initialize()
   {

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

   StatusCode TrackingAlg::execute(const EventContext & /*ctx*/) const
   {

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace EFTracking
