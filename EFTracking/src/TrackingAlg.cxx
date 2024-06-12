//
// Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration
//

// Local include(s).
#include "TrackingAlg.h"

// traccc include(s).
#include <traccc/io/read_digitization_config.hpp>
#include <traccc/io/read_geometry.hpp>
#include <traccc/io/utils.hpp>

// Detray include(s).
#include <detray/io/frontend/detector_reader.hpp>

DECLARE_COMPONENT(EFTracking::TrackingAlg)

namespace EFTracking
{

   StatusCode TrackingAlg::initialize()
   {
      // Read in the geometry.
      auto [surface_transforms, barcode_map] = traccc::io::read_geometry(
          m_detectorFile, traccc::data_format::json);

      // Set up the detector reader configuration.
      detray::io::detector_reader_config cfg;
      cfg.add_file(traccc::io::get_absolute_path(m_detectorFile));

      // Read the detector.
      auto det = detray::io::read_detector<host_detector_type>(m_resource, cfg);
      m_hostDetector = std::move(det.first);

      // Copy it to the device.
      m_deviceDetector = detray::get_buffer(detray::get_data(m_hostDetector),
                                            m_cuda_device_resource, m_cuda_copy);
      m_cuda_stream.synchronize();

      // Read the digitization configuration file
      m_digitizationConfig = traccc::io::read_digitization_config(m_digitizationFile);

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

   StatusCode TrackingAlg::execute(const EventContext & /*ctx*/) const
   {

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace EFTracking
