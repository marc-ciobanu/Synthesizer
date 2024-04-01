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
private:

};
