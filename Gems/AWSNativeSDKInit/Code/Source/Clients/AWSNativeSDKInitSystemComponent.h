
#pragma once

#include <AzCore/Component/Component.h>
#include <AWSNativeSDKInit/AWSNativeSDKInitBus.h>

#include "AWSMemoryInterface.h"

#include <AzCore/Module/Environment.h>

#if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
    #include <AzCore/PlatformIncl.h>
    // The AWS Native SDK AWSAllocator triggers a warning due to accessing members of std::allocator directly.
    // AWSAllocator.h(70): warning C4996: 'std::allocator<T>::pointer': warning STL4010: Various members of std::allocator are deprecated in C++17.
    // Use std::allocator_traits instead of accessing these members directly.
    // You can define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING or _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS to acknowledge that you have received this warning.
    AZ_PUSH_DISABLE_WARNING(4251 4996, "-Wunknown-warning-option")
    #include <aws/core/Aws.h>
    AZ_POP_DISABLE_WARNING
#endif

namespace AWSNativeSDKInit
{
    class AWSNativeSDKInitSystemComponent
        : public AZ::Component
        , protected AWSNativeSDKInitRequestBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(AWSNativeSDKInitSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        AWSNativeSDKInitSystemComponent();
        ~AWSNativeSDKInitSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // AWSNativeSDKInitRequestBus interface implementation
        void InitAwsApi() override;
        bool IsInitialized() override;
        void Shutdown() override;
        bool PreventAwsEC2MetadataCalls(bool force = false) override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

    private:

        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            AWSNativeSDKInit::MemoryManager m_memoryManager;
            AZ::EnvironmentVariable<Aws::SDKOptions> m_awsSDKOptions;
        #endif

		bool m_initialized = false;
    };

} // namespace AWSNativeSDKInit
