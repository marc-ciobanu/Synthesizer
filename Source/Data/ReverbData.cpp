/*
  ==============================================================================

    ReverbData.cpp
    Created: 12 Apr 2024 3:36:58pm
    Author:  admin

  ==============================================================================
*/

#include "ReverbData.h"

void ReverbData::prepareToPlay(double sampleRate)
{
    setSampleRate(sampleRate);
}

void ReverbData::updateParameters(float roomSize, float reverbDamping, float wetLevel, float dryLevel, float reverbWidth)
{
    reverbParameters.roomSize = roomSize;
    reverbParameters.damping = reverbDamping;
    reverbParameters.wetLevel = wetLevel;
    reverbParameters.dryLevel = dryLevel;
    reverbParameters.width = reverbWidth;

    setParameters(reverbParameters);
}

void ReverbData::process(juce::AudioBuffer<float>& buffer, int numSamples) {
    processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), numSamples);
}