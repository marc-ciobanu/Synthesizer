/*
  ==============================================================================

    ReverbComponent.h
    Created: 12 Apr 2024 3:37:15pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderStyle(juce::Slider& slider, juce::Label& label);

    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider wetLevelSlider;
    juce::Slider dryLevelSlider;
    juce::Slider widthSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

    juce::Label roomSizeLabel {"Reverb Room Size", "Room Size"};
    juce::Label dampingLabel{"Reverb Damping", "Damping"};
    juce::Label wetLevelLabel {"Reverb Wet Level", "Wet Level"};
    juce::Label dryLevelLabel {"Reverb Dry Level", "Dry Level"};
    juce::Label widthLabel {"Reverb Width", "Width"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
