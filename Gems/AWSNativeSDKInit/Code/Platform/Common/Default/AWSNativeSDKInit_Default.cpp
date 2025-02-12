/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


namespace AWSNativeSDKInit
{
    namespace Platform
    {
        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            void CustomizeSDKOptions(Aws::SDKOptions& options)
            {
                AZ_UNUSED(options);
            }

            void CustomizeShutdown()
            {
            }
        #endif
    }
}
