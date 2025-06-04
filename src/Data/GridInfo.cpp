#include "Data/GridInfo.hpp"
#include <span>

SliceDetails::GridInfo::GridInfo(){
    for (int i = 0; i < 18; i++) {
        notes[i] = new NoteInfo(); 
    }
}

SliceDetails::GridInfo::~GridInfo(){
    for (int i = 0; i < 18; i++) {
        delete notes[i];
    }
}

SliceDetails::NoteInfo SliceDetails::GridInfo::getCombinedNoteInfo(){
    SliceDetails::NoteInfo holyNote;
    for (auto& note : notes) holyNote += *note;
    return holyNote;
}

std::string SliceDetails::GridInfo::getAverageValueStringData(){
    return getCombinedNoteInfo().getAverageValueStringData();
}

std::string SliceDetails::GridInfo::getAverageScoreString(){
    return getCombinedNoteInfo().getAverageScoreString();
}