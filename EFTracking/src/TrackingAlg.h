//
// Copyright (C) 2023-2024 CERN for the benefit of the ATLAS collaboration
//
#ifndef EFTRACKING_TRACKINGALG_H
#define EFTRACKING_TRACKINGALG_H

// Athena/Gaudi includes.
#include "AthenaBaseComps/AthReentrantAlgorithm.h"

// Acts R&D include(s).
#include <vecmem/memory/host_memory_resource.hpp>
#include <vecmem/memory/cuda/device_memory_resource.hpp>
#include <vecmem/memory/cuda/host_memory_resource.hpp>
#include <vecmem/utils/cuda/copy.hpp>
#include <detray/core/detector.hpp>
#include <traccc/clusterization/clusterization_algorithm.hpp>
#include <traccc/cuda/clusterization/clusterization_algorithm.hpp>
#include <traccc/io/digitization_config.hpp>

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
      /// @name Configuration options.
      /// @{

      /// The configuration options for the detector.
      Gaudi::Property<std::string> m_detectorFile{
          this, "DetectorFile", "geometries/odd/odd-detray_geometry_detray.json",
          "The detector file to use"};
      /// The detector digitization configuration file.
      Gaudi::Property<std::string> m_digitizationFile{
          this, "DigitizationFile", "geometries/odd/odd-digi-geometric-config.json",
          "The digitization configuration file to use"};

      /// @}

      /// @name Acts R&D objects.
      /// @{

      /// Detector type used in host code
      using host_detector_type = detray::detector<detray::default_metadata,
                                                  detray::host_container_types>;
      /// Detector type used in device code
      using device_detector_type =
          detray::detector<detray::default_metadata,
                           detray::device_container_types>;

      /// Host memory resource to be used by the clusterization "algorithm"
      vecmem::host_memory_resource m_resource;
      /// The clusterization "algorithm"
      traccc::host::clusterization_algorithm m_alg{m_resource};

      /// CUDA stream to execute asynchronous clusterization on
      traccc::cuda::stream m_cuda_stream;
      /// CUDA pinned host memory resource
      vecmem::cuda::host_memory_resource m_cuda_host_resource;
      /// CUDA device memory resource
      vecmem::cuda::device_memory_resource m_cuda_device_resource;
      /// CUDA copy helper object
      vecmem::cuda::copy m_cuda_copy;

      /// Host detector object
      host_detector_type m_hostDetector{m_resource};
      /// Device detector buffer
      host_detector_type::buffer_type m_deviceDetector;

      /// Digitization configuration for the detector
      traccc::digitization_config m_digitizationConfig;

      /// The CUDA asynchronous clusterization "algorithm"
      traccc::cuda::clusterization_algorithm
          m_cuda_clusterization{{m_cuda_device_resource, &m_cuda_host_resource},
                                m_cuda_copy,
                                m_cuda_stream,
                                1024};

      /// @}

   }; // class TrackingAlg

} // namespace EFTracking

#endif // EFTRACKING_TRACKINGALG_H
