#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "HMUI/ModalView.hpp"
#include "Utils/HandleHighlighter.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, ModalCloseHandler, UnityEngine::MonoBehaviour) {

    DECLARE_INSTANCE_METHOD(void, FixedUpdate);
    DECLARE_INSTANCE_METHOD(void, OnEnable);

    public:
    static ModalCloseHandler* AddModalCloser(HMUI::ModalView* modal, HandleHighlighter* highlighter, SliceDetailsFloatingScreen* screen);
    private:
    SliceDetailsFloatingScreen* sliceDetails;
    HandleHighlighter* high;
    bool justEnabled;
};