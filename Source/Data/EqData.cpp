/*
  ==============================================================================

    EqData.cpp
    Created: 21 Apr 2024 1:14:04pm
    Author:  admin

  ==============================================================================
*/

#include "EqData.h"

void EqData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;

    spec.maximumBlockSize = samplesPerBlock;

    spec.numChannels = numChannels;

    prepare()
}