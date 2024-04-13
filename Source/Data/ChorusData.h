/*
  ==============================================================================

    ChorusData.h
    Created: 13 Apr 2024 11:37:45am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ChorusData : public juce::dsp::Chorus<float> 
{
public:
    void updateParameteres(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix);
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    //void process(juce::AudioBuffer<float>& buffer);
private:
};