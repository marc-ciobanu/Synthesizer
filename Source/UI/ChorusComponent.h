/*
  ==============================================================================

    ChorusComponent.h
    Created: 13 Apr 2024 11:37:59am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider chorusRateSlider;
    juce::Slider chorusDepthSlider;
    juce::Slider chorusCentreDelaySlider;
    juce::Slider chorusFeedbackSlider;
    juce::Slider chorusMixSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusCentreDelayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusMixAttachment;

    juce::Label chorusRateLabel{ "Chorus Rate", "Rate" };
    juce::Label chorusDepthLabel{ "Chorus Depth", "Depth" };
    juce::Label chorusCentreDelayLabel{ "Chorus Centre Delay", "Centre Delay" };
    juce::Label chorusFeedbackLabel{ "Chorus Feedback", "Feedback" };
    juce::Label chorusMixLabel{ "Chorus Mix", "Mix" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
