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
    void updateParameters(bool enable, juce::dsp::LadderFilterMode mode, float ladderCutoff, float ladderResonance, float ladderDrive);
private:

};