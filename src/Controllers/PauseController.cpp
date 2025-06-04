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
    }

    void PauseController::Initialize()
    {
        getLogger().debug("Initialising Pause Controller");
        gamePause->___didPauseEvent += DelegateW{&PauseController::OnPause, this};
        gamePause->___willResumeEvent += DelegateW{&PauseController::OnUnPause, this};
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
        gamePause->___didPauseEvent -= DelegateW{&PauseController::OnPause, this};
        gamePause->___willResumeEvent -= DelegateW{&PauseController::OnUnPause, this};
    }
}