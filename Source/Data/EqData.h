/*
  ==============================================================================

    EqData.h
    Created: 21 Apr 2024 1:14:04pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EqData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
private:
    
};