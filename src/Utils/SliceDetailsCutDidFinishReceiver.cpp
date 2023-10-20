#include "Utils/SliceDetailsCutFinishReceiver.hpp"

DEFINE_TYPE(SliceDetails, SliceDetailsCutDidFinishReceiver);

using namespace GlobalNamespace;

namespace SliceDetails
{
    SliceDetailsCutDidFinishReceiver* SliceDetailsCutDidFinishReceiver::NewInstance(std::function<void(CutScoreBuffer*)> callback)
    {
        auto instance = SliceDetailsCutDidFinishReceiver::New_ctor();
        instance->callback = callback;
        return instance;
    }

    void SliceDetailsCutDidFinishReceiver::HandleCutScoreBufferDidFinish(CutScoreBuffer* cutScoreBuffer)
    {
        callback(cutScoreBuffer);
        cutScoreBuffer->UnregisterDidFinishReceiver(this->i_IReceiver());
    }

    ICutScoreBufferDidFinishReceiver* SliceDetailsCutDidFinishReceiver::i_IReceiver() { return reinterpret_cast<ICutScoreBufferDidFinishReceiver*>(this); }
}