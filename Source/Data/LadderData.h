/*
  ==============================================================================

    LadderData.h
    Created: 2 Jun 2024 3:25:28am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LadderData : public juce::dsp::LadderFilter<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void updateParameters(bool ladderEnable, int ladderMode, float ladderCutoff, float ladderResonance, float ladderDrive);
private:

};