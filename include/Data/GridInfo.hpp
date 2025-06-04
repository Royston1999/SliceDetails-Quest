#pragma once
#include "Data/NoteInfo.hpp"

namespace SliceDetails{
    class GridInfo{
        public:
            NoteInfo* notes[18];
            GridInfo();
            ~GridInfo();
            std::string getAverageValueStringData();
            std::string getAverageScoreString();
            SliceDetails::NoteInfo getCombinedNoteInfo();
    };
}