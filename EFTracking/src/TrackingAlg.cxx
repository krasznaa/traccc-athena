//
// Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration
//

// Local include(s).
#include "TrackingAlg.h"

// traccc include(s).
#include <traccc/io/read_detector.hpp>
#include <traccc/io/read_detector_description.hpp>

DECLARE_COMPONENT(EFTracking::TrackingAlg)

namespace EFTracking
{

   StatusCode TrackingAlg::initialize()
   {
      // Read the detector description and geometry into host containers.
      traccc::io::read_detector_description(m_hostDD, m_detectorFile, m_digitizationFile,
                                            traccc::data_format::json,
                                            traccc::data_format::json);
      traccc::io::read_detector(m_hostDetector, m_host_resource, m_detectorFile);

      // Copy the detector description and geometry to the device.
      m_deviceDD = {static_cast<traccc::silicon_detector_description::buffer::size_type>(
                        m_hostDD.size()),
                    m_cuda_device_resource};
      m_cuda_copy(vecmem::get_data(m_hostDD), m_deviceDD)->ignore();

      m_deviceDetector = detray::get_buffer(detray::get_data(m_hostDetector),
                                            m_cuda_device_resource, m_cuda_copy);
      m_cuda_stream.synchronize();

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

   StatusCode TrackingAlg::execute(const EventContext & /*ctx*/) const
   {

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace EFTracking
