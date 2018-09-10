#pragma once
#include "core/framework/allocator.h"

// Placeholder for an MKL allocators
namespace onnxruntime {
class MKLDNNAllocator : public CPUAllocator {
 public:
  const AllocatorInfo& Info() const override;
};
class MKLDNNCPUAllocator : public CPUAllocator {
 public:
  const AllocatorInfo& Info() const override;
};
}  // namespace onnxruntime
