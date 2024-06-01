/*
  ==============================================================================

    LimiterData.h
    Created: 31 May 2024 2:44:45pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LimiterData : public juce::dsp::Limiter<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void updateParameters(float limiterThreshold, float limiterRelease);
    juce::dsp::Limiter<float> limiter;
private:

};