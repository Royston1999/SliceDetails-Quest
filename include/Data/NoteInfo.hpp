#pragma once
#include <iomanip>
#include <sstream>

namespace SliceDetails{
    class NoteInfo{
        public:
		float cutAngle;
		float cutOffset;
        float preswing;
        float postswing;
        float offset;
        int cutCount;
        NoteInfo();
        void addNewNoteData(float pre, float post, float acc, float angle, float off);
        std::string getAverageValueStringData();
        std::string Round(float value, int precision);
    };
}