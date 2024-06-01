/*
  ==============================================================================

    LimiterData.cpp
    Created: 31 May 2024 2:44:45pm
    Author:  admin

  ==============================================================================
*/

#include "LimiterData.h"


void LimiterData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void LimiterData::updateParameters(float limiterThreshold, float limiterRelease)
{
    setThreshold(limiterThreshold);
    setRelease(limiterRelease);
}