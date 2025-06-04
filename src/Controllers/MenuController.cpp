#include "Controllers/MenuController.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, MenuController);

using namespace GlobalNamespace;
using namespace DelegateUtils;

namespace SliceDetails
{
    void MenuController::ctor(SliceDetailsFloatingScreen* sliceDetails, ResultsViewController* results, MultiplayerResultsViewController* multiResults)
    {
        this->sliceDetails = sliceDetails;
        this->results = results;
        this->multiResults = multiResults;
    }

    void MenuController::Initialize()
    {
        getLogger().debug("Initialising Menu Controller");
        results->___didActivateEvent += DelegateW{&MenuController::OnResultsActivate, this};
        results->___didDeactivateEvent += DelegateW{&MenuController::OnResultsDeactivate, this};
        multiResults->___didActivateEvent += DelegateW{&MenuController::OnResultsActivate, this};
        multiResults->___didDeactivateEvent += DelegateW{&MenuController::OnResultsDeactivate, this};
    }

    void MenuController::OnResultsActivate(bool one, bool two, bool three)
    {
        sliceDetails->OnResultsScreenActivate();
    }

    void MenuController::OnResultsDeactivate(bool one, bool two)
    {
        sliceDetails->OnResultsScreenDeactivate();
    }

    void MenuController::Dispose()
    {
        getLogger().debug("Disposing Menu Controller");
        results->___didActivateEvent -= DelegateW{&MenuController::OnResultsActivate, this};
        results->___didDeactivateEvent -= DelegateW{&MenuController::OnResultsDeactivate, this};
        multiResults->___didActivateEvent -= DelegateW{&MenuController::OnResultsActivate, this};
        multiResults->___didDeactivateEvent -= DelegateW{&MenuController::OnResultsDeactivate, this};
    }
}