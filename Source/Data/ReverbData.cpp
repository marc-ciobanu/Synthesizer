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

void ReverbData::updateParameters(float roomSize, float damping, float wetLevel, float dryLevel)
{
    reverbParameters.roomSize = roomSize;
    reverbParameters.damping = damping;
    reverbParameters.wetLevel = wetLevel;
    reverbParameters.dryLevel = dryLevel;

    setParameters(reverbParameters);
}