#pragma once
#include "Data/NoteInfo.hpp"

namespace SliceDetails{
    class GridInfo{
        public:
            float preswing;
            float postswing;
            float offset;
            int cutCount;
            NoteInfo* notes[18];
            GridInfo();
            ~GridInfo();
            std::string getAverageValueStringData();
            std::string getAverageScoreString();
            std::string Round(float value, int precision);
            void addNewGridPosData(float pre, float post, float acc);

    };
}