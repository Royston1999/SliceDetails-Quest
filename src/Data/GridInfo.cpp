#include "Data/GridInfo.hpp"

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

std::string SliceDetails::GridInfo::getAverageValueStringData(){
    std::string averagePre = Round(preswing/cutCount, 2);
    std::string averagePost = Round(postswing/cutCount, 2);
    std::string averageAcc = Round(offset/cutCount, 2);
    std::string averageScore = Round((preswing + postswing + offset)/cutCount, 2);
    std::string hoverHintString = "Average Score - " + averageScore + " (" + averagePre + ", " + averagePost + ", " + averageAcc + ")";
    return hoverHintString;
}

std::string SliceDetails::GridInfo::getAverageScoreString(){
    std::string averageScore = Round((preswing + postswing + offset)/cutCount, 2);
    return averageScore;
}