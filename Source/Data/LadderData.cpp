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

void LadderData::updateParameters(bool ladderEnable, int ladderMode, float ladderCutoff, float ladderResonance, float ladderDrive)
{
    setEnabled(ladderEnable);
    setCutoffFrequencyHz(ladderCutoff);
    setResonance(ladderResonance);
    setDrive(ladderDrive);

    switch (ladderMode)
    {
    case 0:
        setMode(juce::dsp::LadderFilterMode::LPF12);
        break;

    case 1:
        setMode(juce::dsp::LadderFilterMode::HPF12);
        break;

    case 2:
        setMode(juce::dsp::LadderFilterMode::BPF12);
        break;

    case 3:
        setMode(juce::dsp::LadderFilterMode::LPF24);
        break;

    case 4:
        setMode(juce::dsp::LadderFilterMode::HPF24);
        break;

    case 5:
        setMode(juce::dsp::LadderFilterMode::BPF24);
        break;
    }

}