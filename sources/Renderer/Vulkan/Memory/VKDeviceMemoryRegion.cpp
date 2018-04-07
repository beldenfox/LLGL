/*
 * VKDeviceMemoryRegion.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "VKDeviceMemoryRegion.h"
#include "VKDeviceMemory.h"
#include "../VKCore.h"


namespace LLGL
{


VKDeviceMemoryRegion::VKDeviceMemoryRegion(VKDeviceMemory* deviceMemory, VkDeviceSize alignedSize, VkDeviceSize alignedOffset, std::uint32_t memoryTypeIndex) :
    deviceMemory_    { deviceMemory    },
    size_            { alignedSize     },
    offset_          { alignedOffset   },
    memoryTypeIndex_ { memoryTypeIndex }
{
}

void VKDeviceMemoryRegion::BindBuffer(VkDevice device, VkBuffer buffer)
{
    vkBindBufferMemory(device, buffer, deviceMemory_->GetVkDeviceMemory(), offset_);
}

bool VKDeviceMemoryRegion::MergeWith(VKDeviceMemoryRegion& other)
{
    if (GetParentChunk() == other.GetParentChunk() && GetMemoryTypeIndex() == other.GetMemoryTypeIndex())
    {
        /* Check if this region is a direct lower part */
        if (GetOffset() + GetSize() == other.GetOffset())
        {
            size_ += other.GetSize();
            return true;
        }

        /* Check if this region is a direct upper part */
        if (other.GetOffset() + other.GetSize() == GetOffset())
        {
            offset_ = other.GetOffset();
            size_ += other.GetSize();
            return true;
        }
    }
    return false;
}


} // /namespace LLGL



// ================================================================================
