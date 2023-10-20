#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ModalView.hpp"
#include "UI/GridDotsViewController.hpp"
#include "UI/NoteUI.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/ICutScoreBufferDidFinishReceiver.hpp"
#include "GlobalNamespace/CutScoreBuffer.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, SliceDetailsCutDidFinishReceiver, Il2CppObject, std::vector<Il2CppClass*>({classof(GlobalNamespace::ICutScoreBufferDidFinishReceiver*)}),

    DECLARE_DEFAULT_CTOR();

    DECLARE_OVERRIDE_METHOD(void, HandleCutScoreBufferDidFinish, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::GlobalNamespace::ICutScoreBufferDidFinishReceiver::HandleCutScoreBufferDidFinish>::get(), GlobalNamespace::CutScoreBuffer* cutScoreBuffer);

    public:
    static SliceDetailsCutDidFinishReceiver* NewInstance(std::function<void(GlobalNamespace::CutScoreBuffer*)> callback);
    GlobalNamespace::ICutScoreBufferDidFinishReceiver* i_IReceiver();
    private:
    std::function<void(GlobalNamespace::CutScoreBuffer*)> callback;
)

