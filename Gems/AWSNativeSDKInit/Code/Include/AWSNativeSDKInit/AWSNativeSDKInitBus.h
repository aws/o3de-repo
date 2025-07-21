
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace AWSNativeSDKInit
{
    class AWSNativeSDKInitRequests
    {
    public:
        AZ_RTTI(AWSNativeSDKInitRequests, "{0B2F53C0-17D7-4D9F-80E2-F32C9B3E0C59}");
        virtual ~AWSNativeSDKInitRequests() = default;

        //! Call to guarantee that the API is initialized with proper Open 3D Engine settings.
        //! It's fine to call this from every module which needs to use the NativeSDK
        //! Creates a static shared pointer using the AZ EnvironmentVariable system.
        //! This will prevent the AWS SDK from going through the shutdown routine until all references are gone, or
        //! the AZ::EnvironmentVariable system is brought down.
        virtual void InitAwsApi() = 0;

        //! Returns true if the AWS SDK is initialized and ready to be used.
        virtual bool IsInitialized() = 0;

        //! Remove reference, if final reference then shut down SDK.
        virtual void Shutdown() = 0;

        //! Call this after InitAwsApi to prevent any reachout to the Amazon EC2 instance metadata service (IMDS).
        //! Unless you are running on EC2 compute this is recommended, otherwise AWS C++ SDK may try to call IMDS for region, config
        //! or credential information, which will fail on non EC2 compute and waste resources. 
        //! Note: This is a helper function for managing the environment variable, AWS_EC2_METADATA_DISABLED, but impacts just the current application's environment.
        //! @param force If true, always set AWS_EC2_METADATA_DISABLED to true, otherwise only set if environment variable is not set.
        //! @returns True if env var was set or currently prevents calls, False otherwise 
        virtual bool PreventAwsEC2MetadataCalls(bool force = false) = 0;
    };

    class AWSNativeSDKInitBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using AWSNativeSDKInitRequestBus = AZ::EBus<AWSNativeSDKInitRequests, AWSNativeSDKInitBusTraits>;
    using AWSNativeSDKInitInterface = AZ::Interface<AWSNativeSDKInitRequests>;

} // namespace AWSNativeSDKInit
