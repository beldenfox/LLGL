/*
 * CsRenderSystem.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#pragma once

#include <vcclr.h>
#include <vector>
#include <LLGL/RenderSystem.h>
#include "CsRenderSystemFlags.h"
#include "CsRenderContext.h"
#include "CsRenderContextFlags.h"
#include "CsCommandQueue.h"
#include "CsShader.h"
#include "CsShaderProgram.h"
#include "CsGraphicsPipelineFlags.h"

#using <System.dll>
#using <System.Core.dll>
#using <System.Runtime.InteropServices.dll>


using namespace System;
using namespace System::Runtime::InteropServices;


namespace LHermanns
{

namespace LLGL
{


public ref class RenderSystem
{

    public:

        /* ----- Common ----- */

        ~RenderSystem();

        static Collections::Generic::List<String^>^ FindModules();

        static RenderSystem^ Load(String^ moduleName);

        static void Unload(RenderSystem^ renderSystem);

        property int ID
        {
            int get();
        }

        property String^ Name
        {
            String^ get();
        }

        property RendererInfo^ Info
        {
            RendererInfo^ get();
        }

        #if 0

        property RenderingCapabilities^ RenderingCaps
        {
            RenderingCapabilities^ get();
        }

        property RenderSystemConfiguration^ Configuration
        {
            RenderSystemConfiguration^ get();
            void set(RenderSystemConfiguration^ config);
        }

        #endif

        /* ----- Render Context ----- */

        RenderContext^ CreateRenderContext(RenderContextDescriptor^ desc);

        //RenderContext^ CreateRenderContext(RenderContextDescriptor^ desc, Surface^ surface);

        void Release(RenderContext^ renderContext);

        /* ----- Command queues ----- */

        property CommandQueue^ CommandQueue
        {
            LHermanns::LLGL::CommandQueue^ get();
        }

        /* ----- Command buffers ----- */

        CommandBuffer^ CreateCommandBuffer();

        #if 0
        CommandBufferExt^ CreateCommandBufferExt();
        #endif

        void Release(CommandBuffer^ commandBuffer);

        #if 0

        /* ----- Buffers ------ */

        Buffer^ CreateBuffer(BufferDescriptor^ desc);
        Buffer^ CreateBuffer(BufferDescriptor^ desc, array<System::Byte>^ initialData);

        BufferArray^ CreateBufferArray(array<Buffer^>^ bufferArray);

        void Release(Buffer^ buffer);

        void Release(BufferArray^ bufferArray);

        void WriteBuffer(Buffer^ buffer, array<System::Byte>^ data, System::UIntPtr dataSize, System::UIntPtr offset);

        //void* MapBuffer(Buffer^ buffer, CPUAccess access);

        //void UnmapBuffer(Buffer^ buffer);

        /* ----- Textures ----- */

        Texture^ CreateTexture(TextureDescriptor^ textureDesc);
        Texture^ CreateTexture(TextureDescriptor^ textureDesc, SrcImageDescriptor^ imageDesc);

        void Release(Texture^ texture);

        void WriteTexture(Texture^ texture, SubTextureDescriptor^ subTextureDesc, SrcImageDescriptor^ imageDesc);
        void ReadTexture(Texture^ texture, unsigned int mipLevel, DstImageDescriptor^ imageDesc);

        void GenerateMips(Texture^ texture);
        void GenerateMips(Texture^ texture, unsigned int baseMipLevel, unsigned int numMipLevels, unsigned int baseArrayLayer, unsigned int numArrayLayers);

        /* ----- Samplers ---- */

        Sampler^ CreateSampler(SamplerDescriptor^ desc);

        void Release(Sampler^ sampler);

        /* ----- Resource Heaps ----- */

        ResourceHeap^ CreateResourceHeap(ResourceHeapDescriptor^ desc);

        void Release(ResourceHeap^ resourceHeap);

        /* ----- Render Targets ----- */

        RenderTarget^ CreateRenderTarget(RenderTargetDescriptor^ desc);

        void Release(RenderTarget^ renderTarget);
        #endif

        /* ----- Shader ----- */

        Shader^ CreateShader(ShaderDescriptor^ desc);

        ShaderProgram^ CreateShaderProgram(ShaderProgramDescriptor^ desc);

        void Release(Shader^ shader);

        void Release(ShaderProgram^ shaderProgram);

        #if 0
        /* ----- Pipeline Layouts ----- */

        PipelineLayout^ CreatePipelineLayout(PipelineLayoutDescriptor^ desc);

        void Release(PipelineLayout^ pipelineLayout);
        #endif

        /* ----- Pipeline States ----- */

        GraphicsPipeline^ CreateGraphicsPipeline(GraphicsPipelineDescriptor^ desc);

        #if 0
        ComputePipeline^ CreateComputePipeline(ComputePipelineDescriptor^ desc);
        #endif

        void Release(GraphicsPipeline^ graphicsPipeline);

        #if 0
        void Release(ComputePipeline^ computePipeline);
        #endif

        #if 0
        /* ----- Queries ----- */

        Query^ CreateQuery(QueryDescriptor^ desc);

        void Release(Query^ query);

        #endif

        /* ----- Fences ----- */

        Fence^ CreateFence();

        void Release(Fence^ fence);

    private:

        RenderSystem(std::unique_ptr<::LLGL::RenderSystem>&& native);

    private:

        ::LLGL::RenderSystem* native_ = nullptr;

        LHermanns::LLGL::CommandQueue^ commandQueue_;

};


} // /namespace LLGL

} // /namespace LHermanns



// ================================================================================