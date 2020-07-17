/*
 * MTRenderContext.mm
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2019 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "MTRenderContext.h"
#include "MTTypes.h"
#include "../TextureUtils.h"
#include <LLGL/Platform/NativeHandle.h>

#import <QuartzCore/CAMetalLayer.h>


namespace LLGL
{


MTRenderContext::MTRenderContext(
    id<MTLDevice>                   device,
    RenderContextDescriptor         desc,
    const std::shared_ptr<Surface>& surface)
:
    renderPass_ { desc }
{
    /* Create surface */
    SetOrCreateSurface(surface, desc.videoMode, nullptr);
    desc.videoMode = GetVideoMode();

    NativeHandle nativeHandle = {};
    GetSurface().GetNativeHandle(&nativeHandle, sizeof(nativeHandle));

    /* Create MetalKit view */
    #ifdef LLGL_OS_IOS

    //UIView* view = nativeHandle.view;
    CGRect screenBounds = [UIScreen mainScreen].nativeBounds;

    view_ = [[MTKView alloc] initWithFrame:screenBounds device:device];

    if (NSClassFromString(@"MTKView") != nullptr)
    {
        CALayer* layer = view_.layer;
        if (layer != nullptr && [layer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
        {
            metalLayer_ = reinterpret_cast<CAMetalLayer*>(layer);
        }
    }

    #else

    NSWindow* wnd = nativeHandle.window;

    view_ = [[MTKView alloc] initWithFrame:wnd.frame device:device];

    [wnd setContentView:view_];
    [wnd.contentViewController setView:view_];

    #endif // /LLGL_OS_IOS

    // Currently drawing happens outside of the usual MTKView
    // drawing machinery so we have no use for it's internal
    // timer.
    view_.paused = YES;

    /* Initialize color and depth buffer */
    //MTLPixelFormat colorFmt = metalLayer_.pixelFormat;
    view_.autoResizeDrawable        = NO;
    view_.colorPixelFormat          = renderPass_.GetColorAttachments()[0].pixelFormat;
    view_.depthStencilPixelFormat   = renderPass_.GetDepthStencilFormat();
    view_.sampleCount               = renderPass_.GetSampleCount();

    if (desc.vsync.enabled)
        view_.preferredFramesPerSecond = static_cast<NSInteger>(desc.vsync.refreshRate);

    OnSetVideoMode(desc.videoMode);
}

void MTRenderContext::Present()
{
    [view_ draw];
}

std::uint32_t MTRenderContext::GetSamples() const
{
    return static_cast<std::uint32_t>(renderPass_.GetSampleCount());
}

Format MTRenderContext::GetColorFormat() const
{
    return MTTypes::ToFormat(view_.colorPixelFormat);
}

Format MTRenderContext::GetDepthStencilFormat() const
{
    return MTTypes::ToFormat(view_.depthStencilPixelFormat);
}

const RenderPass* MTRenderContext::GetRenderPass() const
{
    return (&renderPass_);
}


/*
 * ======= Private: =======
 */

bool MTRenderContext::OnSetVideoMode(const VideoModeDescriptor& videoModeDesc)
{
    CGFloat scale = videoModeDesc.resolution.width / view_.bounds.size.width;
    if (scale != view_.layer.contentsScale)
        view_.layer.contentsScale = scale;

    CGSize drawableSize;
    drawableSize.width = videoModeDesc.resolution.width;
    drawableSize.height = videoModeDesc.resolution.height;
    if (!CGSizeEqualToSize(drawableSize, view_.drawableSize))
        view_.drawableSize = drawableSize;

    // Force the view to advance to the next drawable
    [view_ draw];

    return true;
}

bool MTRenderContext::OnSetVsync(const VsyncDescriptor& vsyncDesc)
{
    return false; //todo
}


} // /namespace LLGL



// ================================================================================
