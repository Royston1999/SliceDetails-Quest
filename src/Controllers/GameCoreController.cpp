#include "Controllers/GameCoreController.hpp"
#include "GlobalNamespace/ScoringElement.hpp"
#include "System/Action_1.hpp"
#include "GlobalNamespace/GoodCutScoringElement.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "main.hpp"
// #include "GlobalNamespace/BeatmapObjectManager_NoteWasCutDelegate.hpp"

DEFINE_TYPE(SliceDetails, GameCoreController);

using namespace GlobalNamespace;
using namespace DelegateUtils;
using namespace System;
using namespace UnityEngine;

namespace SliceDetails
{
    void GameCoreController::ctor(SliceDetailsFloatingScreen* sliceDetails, IScoreController* controller, ColorScheme* colorScheme)
    {
        this->sliceDetails = sliceDetails;
        this->scoreController = reinterpret_cast<ScoreController*>(controller);
        this->sliceDetails->leftHand = colorScheme->get_saberAColor();
        this->sliceDetails->rightHand = colorScheme->get_saberBColor();
    }

    void GameCoreController::Initialize()
    {
        getLogger().debug("Initialising GameCore Controller");
        sliceDetails->InitialiseUI();
        sliceDetails->ClearNoteData();

        scoreController->___scoringForNoteFinishedEvent += DelegateW{&GameCoreController::OnScoreFinish, this};
    }

    void GameCoreController::OnScoreFinish(GlobalNamespace::ScoringElement* scoringElement)
    {
        std::optional<GoodCutScoringElement*> goodCut = il2cpp_utils::try_cast<GoodCutScoringElement>(scoringElement);
        if (!goodCut.has_value()) return;
        HandleSwingFinish((*goodCut)->____cutScoreBuffer);
    }

    inline int GetNotePosIndex(NoteData* noteData)
    {
        int notePosIndex;
        switch (noteData->get_cutDirection()){
            case NoteCutDirection::UpLeft:
                notePosIndex = 0; break;
            case NoteCutDirection::Up:
                notePosIndex = 1; break;
            case NoteCutDirection::UpRight:
                notePosIndex = 2; break;
            case NoteCutDirection::Left:
                notePosIndex = 3; break;
            case NoteCutDirection::Any:
                notePosIndex = 4; break;
            case NoteCutDirection::Right:
                notePosIndex = 5; break;
            case NoteCutDirection::DownLeft:
                notePosIndex = 6; break;
            case NoteCutDirection::Down:
                notePosIndex = 7; break;
            case NoteCutDirection::DownRight:
                notePosIndex = 8; break;
            case NoteCutDirection::None:
                notePosIndex = -1; break;
        }
        if (notePosIndex == -1) return -1;
        if (noteData->get_colorType() == ColorType::ColorB) notePosIndex += 9;
        return notePosIndex;
    }

    inline int GetNoteGridIndex(NoteData* noteData)
    {
        return (2 - (int)noteData->get_noteLineLayer()) * 4 + noteData->get_lineIndex();
    }

    void GameCoreController::HandleSwingFinish(CutScoreBuffer* self)
    {
        NoteData* noteData = self->get_noteCutInfo().noteData;
        NoteCutInfo& noteCutInfo = self->____noteCutInfo;
        if (noteData->get_gameplayType() == NoteData::GameplayType::BurstSliderElement) return;
        if (noteData->get_colorType() == ColorType::None || !noteCutInfo.get_allIsOK()) return;

        int yPos = (int)noteData->get_noteLineLayer();
        int xPos = noteData->get_lineIndex();
        if (xPos >= 4 || yPos >= 3 || xPos < 0 || yPos < 0) return;

        int noteGridIndex = GetNoteGridIndex(noteData);
        int notePosIndex = GetNotePosIndex(noteData);  
        if (notePosIndex == -1) return;

        float cutOffset = noteCutInfo.cutDistanceToCenter;
        if (Vector3::Dot(noteCutInfo.cutNormal, Vector3::op_Subtraction(noteCutInfo.cutPoint, noteCutInfo.notePosition)) > 0.0f) cutOffset = -cutOffset;

        int preSwing = self->get_beforeCutScore();
        int postSwing = noteData->get_gameplayType() == NoteData::GameplayType::BurstSliderHead ? 30 : self->get_afterCutScore();
        int offset = self->get_centerDistanceCutScore();
        float cutAngle = noteCutInfo.cutDirDeviation;

        sliceDetails->gridNotes[noteGridIndex]->notes[notePosIndex]->addNewNoteData(preSwing, postSwing, offset, cutAngle, cutOffset);
    }

    void GameCoreController::Dispose()
    {
        getLogger().debug("Disposing GameCore Controller");
        scoreController->___scoringForNoteFinishedEvent -= DelegateW{&GameCoreController::OnScoreFinish, this};
    }
}