#
# All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
# its licensors.
#

set(PAL_TRAIT_UMBRA_SUPPORTED TRUE)
set(PAL_TRAIT_UMBRA_TEST_SUPPORTED FALSE)
set(PAL_TRAIT_UMBRA_EDITOR_TEST_SUPPORTED FALSE)

set(UMBRA_TARGET "3rdParty::umbra")

set(UMBRA_LIBRARIES_DEBUG
    ${UMBRA_SDK_PATH}/bin/macosx/x86_64/libumbraoptimizer64_d.dylib)
set(UMBRA_LIBRARIES_RELEASE
    ${UMBRA_SDK_PATH}/bin/macosx/x86_64/libumbraoptimizer64.dylib)
set(UMBRA_STATIC_LIBRARIES_DEBUG
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraoptimizer_static64_d.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraobjectgrouper64_d.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraruntime64_d.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbracommon64_d.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbradpvs64_d.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraclusterpvs64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbratestdb64_d.a)
set(UMBRA_STATIC_LIBRARIES_RELEASE
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraoptimizer_static64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraobjectgrouper64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraruntime64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbracommon64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbradpvs64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbraclusterpvs64.a
    ${UMBRA_SDK_PATH}/lib/macosx/x86_64/libumbratestdb64.a)
