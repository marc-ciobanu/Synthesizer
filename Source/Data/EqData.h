/*
  ==============================================================================

    EqData.h
    Created: 13 Apr 2024 11:37:45am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utility.h"


struct ChainSettings
{
    float peakFreq{ 0 }, peakGainInDecibels{ 0 }, peakQuality{ 0 };
    float lowCutFreq{ 0 }, highCutFreq{ 0 };
    Slope lowCutSlope{ Slope::Slope_12 }, highCutSlope{ Slope::Slope_12 };
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

class EqData
{
public:
    EqData();
    ~EqData();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    //void updateFilters(juce::AudioProcessorValueTreeState& apvts, double sampleRate);
    void updatePeakFilter(double sampleRate, float peakFreq, float peakQuality, float peakGainInDecibels);
    void updateLowCutFilter(double sampleRate, float lowCutFreq, Slope lowCutSlope);
    void updateHighCutFilter(double sampleRate, float highCutFreq, Slope highCutSlope);
    

private:
    using Filter = juce::dsp::IIR::Filter<float>;
    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;
    using Coefficients = Filter::CoefficientsPtr;

    MonoChain leftChain, rightChain;

    enum ChainPositions
    {
        LowCut,
        Peak,
        HighCut
    };

    void updateCoefficients(Coefficients& old, const Coefficients& replacements);

    template<int Index, typename ChainType, typename CoefficientType>
    void update(ChainType& chain, const CoefficientType& coefficients);

    template<typename ChainType, typename CoefficientType>
    void updateCutFilter(ChainType& chain, const CoefficientType& coefficients, const Slope& slope);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqData)
};
