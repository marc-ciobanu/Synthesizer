/*
  ==============================================================================

    PannerData.h
    Created: 11 Jun 2024 8:35:05pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class PannerData: public juce::dsp::Panner<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void updateParameters(int rule, float pan);
private:


};