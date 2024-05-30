/*
  ==============================================================================

    ChorusData.cpp
    Created: 13 Apr 2024 11:37:45am
    Author:  admin

  ==============================================================================
*/

#include "ChorusData.h"

void ChorusData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void ChorusData::updateParameteres(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix)
{
    setRate(chorusRate);
    setDepth(chorusDepth);
    setCentreDelay(chorusCentreDelay);
    setFeedback(chorusFeedback);
    setMix(chorusMix);
}