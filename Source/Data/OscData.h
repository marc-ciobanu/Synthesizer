/*
  ==============================================================================

    OscData.h
    Created: 1 Apr 2024 11:40:51pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int waveType);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock);
    void setFmParams(const float depth, const float freq);
private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) { return std::sin(x); } };
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMidiNote{ 0 };
};
