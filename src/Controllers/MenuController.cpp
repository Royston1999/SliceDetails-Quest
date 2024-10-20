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

        this->onResultsActivate = {&MenuController::OnResultsActivate, this};
        this->onResultsDeactivate = {&MenuController::OnResultsDeactivate, this};
    }

    void MenuController::Initialize()
    {
        getLogger().debug("Initialising Menu Controller");
        results->___didActivateEvent += onResultsActivate;
        results->___didDeactivateEvent += onResultsDeactivate;
        multiResults->___didActivateEvent += onResultsActivate;
        multiResults->___didDeactivateEvent += onResultsDeactivate;
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
        results->___didActivateEvent -= onResultsActivate;
        results->___didDeactivateEvent -= onResultsDeactivate;
        multiResults->___didActivateEvent -= onResultsActivate;
        multiResults->___didDeactivateEvent -= onResultsDeactivate;
    }
}