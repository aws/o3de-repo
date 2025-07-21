
#include "AWSNativeSDKInitSystemComponent.h"


#include <AzCore/Serialization/SerializeContext.h>



#include <AzCore/Module/Environment.h>
#include <AzCore/Utils/Utils.h>

#if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
#include "AWSLogSystemInterface.h"
#include <aws/core/Aws.h>
#include <aws/core/platform/Environment.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#endif

namespace AWSNativeSDKInit
{
    AZ_COMPONENT_IMPL(AWSNativeSDKInitSystemComponent, "AWSNativeSDKInitSystemComponent",
        "{5F8F93E5-8E6E-4579-8EA5-0815EEE168D1}");

    static constexpr char AWS_EC2_METADATA_DISABLED[] = "AWS_EC2_METADATA_DISABLED";

    namespace Platform
    {
        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            void CustomizeSDKOptions(Aws::SDKOptions& options);
            void CustomizeShutdown();
            void CopyCaCertBundle();
        #endif
    } // namespace Platform

    void AWSNativeSDKInitSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<AWSNativeSDKInitSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void AWSNativeSDKInitSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("AWSNativeSDKInitService"));
    }

    void AWSNativeSDKInitSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("AWSNativeSDKInitService"));
    }

    void AWSNativeSDKInitSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void AWSNativeSDKInitSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    AWSNativeSDKInitSystemComponent::AWSNativeSDKInitSystemComponent()
    {
        if (AWSNativeSDKInitInterface::Get() == nullptr)
        {
            AWSNativeSDKInitInterface::Register(this);
        }
    }

    AWSNativeSDKInitSystemComponent::~AWSNativeSDKInitSystemComponent()
    {
        if (AWSNativeSDKInitInterface::Get() == this)
        {
            AWSNativeSDKInitInterface::Unregister(this);
        }
    }

    void AWSNativeSDKInitSystemComponent::Init()
    {
    }

    void AWSNativeSDKInitSystemComponent::Activate()
    {
        AWSNativeSDKInitRequestBus::Handler::BusConnect();
    }

    void AWSNativeSDKInitSystemComponent::Deactivate()
    {
        AWSNativeSDKInitRequestBus::Handler::BusDisconnect();
    }

    void AWSNativeSDKInitSystemComponent::InitAwsApi()
    {
        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            Aws::Utils::Logging::LogLevel logLevel;
            #if defined(AZ_DEBUG_BUILD) || defined(AZ_PROFILE_BUILD)
                logLevel = Aws::Utils::Logging::LogLevel::Warn;
            #else
                logLevel = Aws::Utils::Logging::LogLevel::Error;
            #endif

            m_awsSDKOptions.Get().loggingOptions.logLevel = logLevel;
            m_awsSDKOptions.Get().loggingOptions.logger_create_fn = [logLevel]()
                {
                    return Aws::MakeShared<AWSLogSystemInterface>("AWS", logLevel);
                };

            m_awsSDKOptions.Get().memoryManagementOptions.memoryManager = &m_memoryManager;
            Platform::CustomizeSDKOptions(m_awsSDKOptions.Get());
            Aws::InitAPI(m_awsSDKOptions.Get());
        #endif // #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)

        Platform::CopyCaCertBundle();
        m_initialized = true;
    }

    bool AWSNativeSDKInitSystemComponent::IsInitialized()
    {
        return m_initialized;
    }

    void AWSNativeSDKInitSystemComponent::Shutdown()
    {
        m_initialized = false;
        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            Aws::ShutdownAPI(m_awsSDKOptions.Get());
            Platform::CustomizeShutdown();
        #endif
    }

    bool AWSNativeSDKInitSystemComponent::PreventAwsEC2MetadataCalls(bool force)
    {
        bool prevented = false;
        #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
            // Helper function to prevent calls to the Amazon EC2 instance metadata service (IMDS), unless environment var has been
            // configured. AWS C++ SDK may reach out to EC2 IMDS for region, config or credentials, but unless code is running on EC2
            // compute such calls will fail and waste network resources. Note: AWS C++ SDK explicitly only checks if lower case version of
            // AWS_EC2_METADATA_DISABLED == "true", otherwise it will enable the EC2 metadata service calls.
            const auto ec2MetadataEnvVar = Aws::Environment::GetEnv(AWS_EC2_METADATA_DISABLED);
            if (ec2MetadataEnvVar.empty() || force)
            {
                prevented = true;
                AZ::Utils::SetEnv(AWS_EC2_METADATA_DISABLED, "true", true);
            }
            else if (Aws::Utils::StringUtils::ToLower(ec2MetadataEnvVar.c_str()) == "true")
            {
                prevented = true;
            }

        #endif // #if defined(PLATFORM_SUPPORTS_AWS_NATIVE_SDK)
        
        return prevented;
    }
} // namespace AWSNativeSDKInit
