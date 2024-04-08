/*
  ==============================================================================

    FilterData.h
    Created: 8 Apr 2024 10:29:47am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParams(const int filterType, const float frequency, const float resonance);
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};