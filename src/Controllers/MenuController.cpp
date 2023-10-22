#include "Controllers/MenuController.hpp"
#include "EasyDelegate.hpp"
#include "System/Action.hpp"
#include "SliceDetailsConfig.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"
#include "HMUI/ViewController_DidDeactivateDelegate.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, MenuController);

using namespace GlobalNamespace;
using namespace EasyDelegate;
using namespace System;

namespace SliceDetails
{
    void MenuController::ctor(SliceDetailsFloatingScreen* sliceDetails, ResultsViewController* results, MultiplayerResultsViewController* multiResults, GameServerLobbyFlowCoordinator* multiLobby)
    {
        this->sliceDetails = sliceDetails;
        this->results = results;
        this->multiResults = multiResults;
        this->multiLobby = multiLobby;
    }

    void MenuController::Initialize()
    {
        getLogger().debug("Initialising Menu Controller");
        using OnActivate = HMUI::ViewController::DidActivateDelegate;
        using OnDeActivate = HMUI::ViewController::DidDeactivateDelegate;
        results->add_didActivateEvent(MakeDelegate<OnActivate*>(&MenuController::OnResultsActivate, this));
        results->add_didDeactivateEvent(MakeDelegate<OnDeActivate*>(&MenuController::OnResultsDeActivate, this));
        multiResults->add_didActivateEvent(MakeDelegate<OnActivate*>(&MenuController::OnResultsActivate, this));
        multiResults->add_didDeactivateEvent(MakeDelegate<OnDeActivate*>(&MenuController::OnResultsDeActivate, this));
    }

    void MenuController::OnResultsActivate(bool one, bool two, bool three)
    {
        sliceDetails->OnResultsScreenActivate();
    }

    void MenuController::OnResultsDeActivate(bool one, bool two)
    {
        sliceDetails->OnResultsScreenDeactivate();
    }

    void MenuController::Dispose()
    {
        getLogger().debug("Disposing Menu Controller");
    }
}