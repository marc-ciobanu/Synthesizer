/*
  ==============================================================================

    ReverbData.h
    Created: 12 Apr 2024 3:36:58pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReverbData : public juce::Reverb
{
public:
    void prepareToPlay(double sampleRate);
    void updateParameters(float roomSize, float reverbDamping, float wetLevel, float dryLevel);
    void process(juce::AudioBuffer<float>& buffer, int numSamples);
private:
    juce::Reverb::Parameters reverbParameters;
};