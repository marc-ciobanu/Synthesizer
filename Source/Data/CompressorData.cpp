/*
  ==============================================================================

    CompressorData.cpp
    Created: 31 May 2024 2:44:33pm
    Author:  admin

  ==============================================================================
*/

#include "CompressorData.h"

void CompressorData::preprareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void CompressorData::updateParameters(float compressorThreshold, float compressorRatio, float compressorAttack, float compressorRelease)
{
    setThreshold(compressorThreshold);
    setRatio(compressorRatio);
    setAttack(compressorAttack);
    setRelease(compressorRelease);
}