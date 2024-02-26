#include "Controllers/PauseController.hpp"
#include "SliceDetailsConfig.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, PauseController);

using namespace GlobalNamespace;
using namespace DelegateUtils;
using namespace System;

namespace SliceDetails
{
    void PauseController::ctor(SliceDetailsFloatingScreen* sliceDetails, IGamePause* gamePause)
    {
        this->sliceDetails = sliceDetails;
        this->gamePause = reinterpret_cast<GamePause*>(gamePause);
        this->onPause = {&PauseController::OnPause, this};
        this->onUnPause = {&PauseController::OnUnPause, this};
    }

    void PauseController::Initialize()
    {
        getLogger().debug("Initialising Pause Controller");
        gamePause->didPauseEvent += onPause;
        gamePause->willResumeEvent += onUnPause;
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
        getLogger().debug("Disposing Pause Controller");
        sliceDetails->OnUnPause();
        gamePause->didPauseEvent -= onPause;
        gamePause->willResumeEvent -= onUnPause;
    }
}