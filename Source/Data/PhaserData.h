/*
  ==============================================================================

    PhaserData.h
    Created: 30 May 2024 3:32:58pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PhaserData : public juce::dsp::Phaser<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void updateParameters(float phaserRate, float phaserDepth, float phaserCentre, float phaserFeedback, float phaserMix);
private:

};
