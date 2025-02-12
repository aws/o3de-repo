/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 */

#pragma once

#include <AssetBuilderSDK/AssetBuilderBusses.h>
#include <AssetBuilderSDK/AssetBuilderSDK.h>

namespace Umbra
{
    class UmbraSceneAsset;

    //! Loads umbra scene, computes visibility data, then stores the results in an asset
    class UmbraSceneAssetBuilder : public AssetBuilderSDK::AssetBuilderCommandBus::Handler
    {
    public:
        AZ_TYPE_INFO(UmbraSceneAssetBuilder, "{DC189D82-F7F0-4E5C-8B90-AF4555459869}");

        UmbraSceneAssetBuilder() = default;
        ~UmbraSceneAssetBuilder();

        // Asset Builder Callback Functions
        void CreateJobs(const AssetBuilderSDK::CreateJobsRequest& request, AssetBuilderSDK::CreateJobsResponse& response);
        void ProcessJob(const AssetBuilderSDK::ProcessJobRequest& request, AssetBuilderSDK::ProcessJobResponse& response);

        // AssetBuilderSDK::AssetBuilderCommandBus overrides...
        void ShutDown() override;

        void RegisterBuilder();

        bool m_isShuttingDown = false;
    };

} // namespace Umbra