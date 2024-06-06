/*
  ==============================================================================

    FilterComponent.h
    Created: 8 Apr 2024 5:21:15pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Butonul in sine
    juce::ComboBox filterSelector;
    juce::Slider filterCutoff;
    juce::Slider filterRes;

    // Attachment catre variabila din ValueTreeState
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResAttachment;

    juce::Label filterSelectorLabel { "Filter Type", "Filter Type" };
    juce::Label filterCutoffLabel{ "Filter Cutoff", "Cutoff" };
    juce::Label filterResLabel{ "Filter Resonance", "Resonance" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
