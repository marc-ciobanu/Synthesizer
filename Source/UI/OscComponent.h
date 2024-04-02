/*
  ==============================================================================

    OscComponent.h
    Created: 2 Apr 2024 12:14:10am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscSelectorId, juce::String fmFreqId, juce::String fmDepthI);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setOscStyle(juce::ComboBox& comboBox);
    void setFmSliderStyle(juce::Slider& slider, juce::Label& label);

    // Butonul in sine
    juce::ComboBox oscSelector;
    
    // Attachment catre variabila din ValueTreeState
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectorAttachment;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;

    juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
