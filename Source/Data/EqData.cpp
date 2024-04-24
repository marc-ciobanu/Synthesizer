
/*
  ==============================================================================

    EqData.cpp
    Created: 13 Apr 2024 11:37:45am
    Author:  admin

  ==============================================================================
*/


#include "EqData.h"

EqData::EqData()
{
}

EqData::~EqData()
{
}

void EqData::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;

    spec.numChannels = 1;

    spec.sampleRate = sampleRate;

    leftChain.prepare(spec);
    rightChain.prepare(spec);
}

void EqData::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftChain.process(leftContext);
    rightChain.process(rightContext);
}

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts)
{
    ChainSettings settings;

    settings.lowCutFreq = apvts.getRawParameterValue("LOWCUTFREQ")->load();
    settings.highCutFreq = apvts.getRawParameterValue("HIGHCUTFREQ")->load();
    settings.peakFreq = apvts.getRawParameterValue("PEAKFREQ")->load();
    settings.peakGainInDecibels = apvts.getRawParameterValue("PEAKGAIN")->load();
    settings.peakQuality = apvts.getRawParameterValue("PEAKQUALITY")->load();
    settings.lowCutSlope = static_cast<Slope>(apvts.getRawParameterValue("LOWCUTSLOPE")->load());
    settings.highCutSlope = static_cast<Slope>(apvts.getRawParameterValue("HIGHCUTSLOPE")->load());


    return settings;
}

void EqData::updateCoefficients(Coefficients& old, const Coefficients& replacements)
{
    *old = *replacements;
}

template<int Index, typename ChainType, typename CoefficientType>
void EqData::update(ChainType& chain, const CoefficientType& coefficients)
{
    updateCoefficients(chain.template get<Index>().coefficients, coefficients[Index]);
    chain.template setBypassed<Index>(false);
}

template<typename ChainType, typename CoefficientType>
void EqData::updateCutFilter(ChainType& chain, const CoefficientType& coefficients, const Slope& slope)
{
    chain.template setBypassed<0>(true);
    chain.template setBypassed<1>(true);
    chain.template setBypassed<2>(true);
    chain.template setBypassed<3>(true);

    switch (slope)
    {
    case Slope_48:
    {
        update<3>(chain, coefficients);
    }
    case Slope_36:
    {
        update<2>(chain, coefficients);
    }
    case Slope_24:
    {
        update<1>(chain, coefficients);
    }
    case Slope_12:
    {
        update<0>(chain, coefficients);
    }
    }
}

void EqData::updatePeakFilter(const ChainSettings& chainSettings, double sampleRate)
{
    auto peakCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, chainSettings.peakFreq, chainSettings.peakQuality, juce::Decibels::decibelsToGain(chainSettings.peakGainInDecibels));


    updateCoefficients(leftChain.get<ChainPositions::Peak>().coefficients, peakCoefficients);
    updateCoefficients(rightChain.get<ChainPositions::Peak>().coefficients, peakCoefficients);
}

void EqData::updateLowCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
    auto lowCutCoefficients = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(chainSettings.lowCutFreq, sampleRate, 2 * (chainSettings.lowCutSlope + 1));
    auto& leftLowCut = leftChain.get<ChainPositions::LowCut>();
    auto& rightLowCut = rightChain.get<ChainPositions::LowCut>();

    updateCutFilter(leftLowCut, lowCutCoefficients, chainSettings.lowCutSlope);
    updateCutFilter(rightLowCut, lowCutCoefficients, chainSettings.lowCutSlope);
}

void EqData::updateHighCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
    auto highCutCoefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(chainSettings.highCutFreq, sampleRate, 2 * (chainSettings.highCutSlope + 1));
    auto& leftHighCut = leftChain.get<ChainPositions::HighCut>();
    auto& rightHighCut = rightChain.get<ChainPositions::HighCut>();

    updateCutFilter(leftHighCut, highCutCoefficients, chainSettings.highCutSlope);
    updateCutFilter(rightHighCut, highCutCoefficients, chainSettings.highCutSlope);
}

void EqData::updateFilters(juce::AudioProcessorValueTreeState& apvts, double sampleRate)
{
    auto chainSettings = getChainSettings(apvts);

    updateLowCutFilter(chainSettings, sampleRate);
    updateHighCutFilter(chainSettings, sampleRate);
    updatePeakFilter(chainSettings, sampleRate);
}

