/*
 * Surface.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2020 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <LLGL/Surface.h>

namespace LLGL
{

Extent2D Surface::GetPreferredResolution() const
{
    return GetContentSize();
}

} // /namespace LLGL



// ================================================================================
