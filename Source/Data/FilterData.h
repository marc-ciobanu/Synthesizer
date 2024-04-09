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
    void updateParameters(const int filterType, const float cutoff, const float resonance, const float modulator=1.0f);
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};