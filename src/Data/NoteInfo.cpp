#include "Data/NoteInfo.hpp"

std::string SliceDetails::NoteInfo::Round(float val, int precision)
{
	std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << val;
    std::string Out = stream.str();
	return Out;
}

SliceDetails::NoteInfo::NoteInfo(){
    cutAngle = 0;
	cutOffset = 0;
    preswing = 0;
    postswing = 0;
    offset = 0;
    cutCount = 0;
}

void SliceDetails::NoteInfo::addNewNoteData(float pre, float post, float acc, float angle, float off){
    cutAngle += angle;
    cutOffset += off;
    preswing += pre;
    postswing += post;
    offset += acc;
    cutCount += 1;
}

std::string SliceDetails::NoteInfo::getAverageValueStringData(){
    std::string averagePre = Round(preswing/cutCount, 2);
    std::string averagePost = Round(postswing/cutCount, 2);
    std::string averageAcc = Round(offset/cutCount, 2);
    std::string averageScore = Round((preswing + postswing + offset)/cutCount, 2);
    // std::string hoverHintString = "Average Score - " + averageScore + " (" + averagePre + ", " + averagePost + ", " + averageAcc + ")";
    std::string hoverHintString = "<u>Total Score</u>  -  <color=#00B300><color=#05BCFF>" + averageScore + " <color=black>/</color></color> 115</color>\n<u>Pre Swing</u>  -  <color=#00B300><color=#05BCFF>" + averagePre + " <color=black>/</color></color> 70</color>\n<u>Post Swing</u>  -  <color=#00B300><color=#05BCFF>" + averagePost + " <color=black>/</color></color> 30</color>\n<u>Accuracy</u>  -  <color=#00B300><color=#05BCFF>" + averageAcc + " <color=black>/</color></color> 15</color>\n<u>Notes Cut</u>  -  <color=#05BCFF>" + std::to_string(cutCount) + "</color>";
    return hoverHintString;
}