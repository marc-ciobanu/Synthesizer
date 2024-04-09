/*
  ==============================================================================

    FilterData.cpp
    Created: 8 Apr 2024 10:29:47am
    Author:  admin

  ==============================================================================
*/

#include "FilterData.h"


void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });
}
void FilterData::updateParameters(const int filterType, const float cutoff, const float resonance, const float modulator)
{
    switch (filterType)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    default:
        break;
    }

    float modFrequency = cutoff * modulator;

    // fmax/fmin alege valoarea mai mica/mare din cele doua
    modFrequency = std::fmax(modFrequency, 20.0f);
    modFrequency = std::fmax(modFrequency, 20000.0f);

    filter.setCutoffFrequency(modFrequency);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}