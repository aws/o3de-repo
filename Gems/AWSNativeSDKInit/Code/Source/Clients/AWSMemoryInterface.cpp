/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


#include "AWSMemoryInterface.h"

namespace AWSNativeSDKInit
{
#if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
    AZ_CHILD_ALLOCATOR_WITH_NAME(AWSNativeSDKAllocator, "AWSNativeSDKAllocator", "{8B4DA42F-2507-4A5B-B13C-4B2A72BC161E}", AZ::SystemAllocator);
    const char* MemoryManager::AWS_API_ALLOC_TAG = "AwsApi";

    void MemoryManager::Begin() 
    {
    }

    void MemoryManager::End() 
    {
    }

    void* MemoryManager::AllocateMemory(std::size_t blockSize, std::size_t alignment, const char* /*allocationTag*/) 
    {
        return AZ::AllocatorInstance<AWSNativeSDKAllocator>::Get().allocate(blockSize, alignment);
    }

    void MemoryManager::FreeMemory(void* memoryPtr) 
    {
        AZ::AllocatorInstance<AWSNativeSDKAllocator>::Get().deallocate(memoryPtr);
    }
#endif
}
