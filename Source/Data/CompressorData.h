/*
  ==============================================================================

    CompressorData.h
    Created: 31 May 2024 2:44:33pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CompressorData : public juce::dsp::Compressor<float>
{
public:
    void preprareToPlay(double sampleRate, int samplesPerBlock);
    void updateParameters(float compressorThreshold, float compressorRatio, float compressorAttack, float compressorRelease);
private:

};