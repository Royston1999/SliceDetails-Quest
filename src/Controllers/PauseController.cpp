#include "Controllers/PauseController.hpp"
#include "EasyDelegate.hpp"
#include "System/Action.hpp"
#include "SliceDetailsConfig.hpp"

DEFINE_TYPE(SliceDetails, PauseController);

using namespace GlobalNamespace;
using namespace EasyDelegate;
using namespace System;

namespace SliceDetails
{
    void PauseController::ctor(SliceDetailsFloatingScreen* sliceDetails, IGamePause* gamePause)
    {
        this->sliceDetails = sliceDetails;
        this->gamePause = gamePause;
    }

    void PauseController::Initialize()
    {
        gamePause->add_didPauseEvent(MakeDelegate<Action*>(&PauseController::OnPause, this));
        gamePause->add_willResumeEvent(MakeDelegate<Action*>(&PauseController::OnUnPause, this));
    }

    void PauseController::OnPause()
    {
        sliceDetails->OnPause();
    }

    void PauseController::OnUnPause()
    {
        sliceDetails->OnUnPause();
    }

    void PauseController::Dispose()
    {
        sliceDetails->OnUnPause();
    }
}