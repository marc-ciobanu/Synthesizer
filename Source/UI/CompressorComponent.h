/*
  ==============================================================================

    CompressorComponent.h
    Created: 4 Jun 2024 4:15:00pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CompressorComponent : public juce::Component
{
public:
    CompressorComponent(juce::AudioProcessorValueTreeState& apvts);
    ~CompressorComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider compressorThresholdSlider;
    juce::Slider compressorRatioSlider;
    juce::Slider compressorAttackSlider;
    juce::Slider compressorReleaseSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compressorThresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compressorRatioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compressorAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compressorReleaseAttachment;

    juce::Label compressorThresholdLabel{ "Compressor Threshold", "Threshold" };
    juce::Label compressorRatioLabel{ "Compressor Ratio", "Ratio" };
    juce::Label compressorAttackLabel{ "Compressor Attack", "Attack" };
    juce::Label compressorReleaseLabel{ "Compressor Release", "Release" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorComponent)
};
