/*
  ==============================================================================

    AdsrData.h
    Created: 1 Apr 2024 2:59:24pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR 
{
public:
    void updateParameters(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};