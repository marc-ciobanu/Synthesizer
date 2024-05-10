// EqData.h

#pragma once

#include <JuceHeader.h>
#include <vector>

class EqData // Change the class name to match the implementation file
{
public:
    void setHighpass(bool highpass);
    void setCutoffFreq(float cutoffFreq);
    void setSampleRate(float sampleRate);

    void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&);

private:
    bool highpass;
    float cutoffFreq;
    float sampleRate;
    std::vector<float> dnBuffer;
};