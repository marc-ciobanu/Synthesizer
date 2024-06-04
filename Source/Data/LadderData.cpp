/*
  ==============================================================================

    LadderData.cpp
    Created: 2 Jun 2024 3:25:28am
    Author:  admin

  ==============================================================================
*/

#include "LadderData.h"

void LadderData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void LadderData::updateParameters(bool enable, juce::dsp::LadderFilterMode mode, float ladderCutoff, float ladderResonance, float ladderDrive)
{
    setEnabled(enable);
    setMode(mode);
    setCutoffFrequencyHz(ladderCutoff);
    setResonance(ladderResonance);
    setDrive(ladderDrive);
}