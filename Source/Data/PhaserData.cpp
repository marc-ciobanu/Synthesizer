/*
  ==============================================================================

    PhaserData.cpp
    Created: 30 May 2024 3:32:58pm
    Author:  admin

  ==============================================================================
*/

#include "PhaserData.h"

void PhaserData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void PhaserData::updateParameters(float phaserRate, float phaserDepth, float phaserCentre, float phaserFeedback, float phaserMix)
{
    setRate(phaserRate);
    setDepth(phaserDepth);
    setCentreFrequency(phaserCentre);
    setFeedback(phaserFeedback);
    setMix(phaserMix);
}