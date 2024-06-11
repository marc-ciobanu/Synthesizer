/*
  ==============================================================================

    PannerData.cpp
    Created: 11 Jun 2024 8:35:05pm
    Author:  admin

  ==============================================================================
*/

#include "PannerData.h"

void PannerData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = 2;
    prepare(specs);
}

void PannerData::updateParameters(int rule, float pan)
{
    setPan(pan);
    switch (rule)
    {
    case 0:
        setRule(juce::dsp::PannerRule::linear); 
        break;
    case 1:
        setRule(juce::dsp::PannerRule::balanced); 
        break;
    case 2:
        setRule(juce::dsp::PannerRule::sin3dB); 
        break;
    case 3:
        setRule(juce::dsp::PannerRule::sin4p5dB); 
        break;
    case 4:
        setRule(juce::dsp::PannerRule::sin6dB); 
        break;
    case 5:
        setRule(juce::dsp::PannerRule::squareRoot3dB); 
        break;
    case 6:
        setRule(juce::dsp::PannerRule::squareRoot4p5dB); 
        break;
    }
}