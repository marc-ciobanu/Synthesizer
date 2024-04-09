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
    void setComboBoxStyle(juce::ComboBox& comboBox, juce::Label& label);
    void setSliderStyle(juce::Slider& slider, juce::Label& label);

    // Butonul in sine
    juce::ComboBox oscSelector;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    // Attachment catre variabila din ValueTreeState
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;

    juce::Label oscSelectorLabel{ "Wave Type", "Wave Type" };
    juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
