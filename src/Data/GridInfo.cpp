#include "Data/GridInfo.hpp"
#include <span>

std::string SliceDetails::GridInfo::Round(float val, int precision)
{
	std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << val;
    std::string Out = stream.str();
	return Out;
}

SliceDetails::GridInfo::GridInfo(){
    preswing = 0;
    postswing = 0;
    offset = 0;
    cutCount = 0;
    for (int i = 0; i < 18; i++) {
        notes[i] = new NoteInfo(); 
    }
}

SliceDetails::GridInfo::~GridInfo(){
    for (int i = 0; i < 18; i++) {
        delete notes[i];
    }
}

void SliceDetails::GridInfo::addNewGridPosData(float pre, float post, float acc){
    preswing += pre;
    postswing += post;
    offset += acc;
    cutCount += 1;
}

SliceDetails::NoteInfo getCombinedNoteInfo(const std::span<SliceDetails::NoteInfo*>& noteInfos){
    SliceDetails::NoteInfo holyNote;
    for (auto& note : noteInfos) holyNote.addNewNoteData(note->preswing, note->postswing, note->offset, note->cutAngle, note->cutOffset);
    return holyNote;
}

std::string SliceDetails::GridInfo::getAverageValueStringData(){
    return getCombinedNoteInfo(std::span<NoteInfo*>(notes)).getAverageValueStringData();
    std::string averagePre = Round(preswing/cutCount, 2);
    std::string averagePost = Round(postswing/cutCount, 2);
    std::string averageAcc = Round(offset/cutCount, 2);
    std::string averageScore = Round((preswing + postswing + offset)/cutCount, 2);
    // std::string hoverHintString = "Average Score - " + averageScore + " (" + averagePre + ", " + averagePost + ", " + averageAcc + ")";
    std::string hoverHintString = "<u>Total Score</u>  -  <color=#00B300><color=#05BCFF>" + averageScore + " <color=black>/</color></color> 115</color>\n<u>Pre Swing</u>  -  <color=#00B300><color=#05BCFF>" + averagePre + " <color=black>/</color></color> 70</color>\n<u>Post Swing</u>  -  <color=#00B300><color=#05BCFF>" + averagePost + " <color=black>/</color></color> 30</color>\n<u>Accuracy</u>  -  <color=#00B300><color=#05BCFF>" + averageAcc + " <color=black>/</color></color> 15</color>\n<u>Notes Cut</u>  -  <color=#05BCFF>" + std::to_string(cutCount) + "</color>";
    return hoverHintString;
}

std::string SliceDetails::GridInfo::getAverageScoreString(){
    std::string averageScore = Round((preswing + postswing + offset)/cutCount, 2);
    return averageScore;
}