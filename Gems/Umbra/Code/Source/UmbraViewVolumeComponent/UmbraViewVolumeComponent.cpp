/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 */

#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <UmbraViewVolumeComponent/UmbraViewVolumeComponent.h>

namespace Umbra
{
    UmbraViewVolumeComponent::UmbraViewVolumeComponent(const UmbraViewVolumeComponentConfig& config)
        : BaseClass(config)
    {
    }

    void UmbraViewVolumeComponent::Reflect(AZ::ReflectContext* context)
    {
        BaseClass::Reflect(context);

        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<UmbraViewVolumeComponent, BaseClass>()
                ->Version(0)
                ;
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->ConstantProperty("UmbraViewVolumeComponentTypeId", BehaviorConstant(AZ::Uuid(UmbraViewVolumeComponentTypeId)))
                ->Attribute(AZ::Script::Attributes::Module, "umbra")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ;
        }
    }
} // namespace Umbra
