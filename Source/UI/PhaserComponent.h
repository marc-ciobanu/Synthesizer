/*
  ==============================================================================

    PhaserComponent.h
    Created: 4 Jun 2024 2:15:00pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PhaserComponent : public juce::Component
{
public:
    PhaserComponent(juce::AudioProcessorValueTreeState& apvts);
    ~PhaserComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider phaserRateSlider;
    juce::Slider phaserDepthSlider;
    juce::Slider phaserCentreDelaySlider;
    juce::Slider phaserFeedbackSlider;
    juce::Slider phaserMixSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserCentreDelayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserMixAttachment;

    juce::Label phaserRateLabel{ "Phaser Rate", "Rate" };
    juce::Label phaserDepthLabel{ "Phaser Depth", "Depth" };
    juce::Label phaserCentreDelayLabel{ "Phaser Centre Delay", "Centre" };
    juce::Label phaserFeedbackLabel{ "Phaser Feedback", "Feedback" };
    juce::Label phaserMixLabel{ "Phaser Mix", "Mix" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaserComponent)
};
