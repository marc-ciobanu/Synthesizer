/*
  ==============================================================================

    PannerComponent.h
    Created: 11 Jun 2024 8:35:45pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PannerComponent  : public juce::Component
{
public:
    PannerComponent(juce::AudioProcessorValueTreeState& apvts);
    ~PannerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox rule;
    juce::Slider pan;

    // Attachment catre variabila din ValueTreeState
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ruleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panAttachment;

    juce::Label ruleLabel{ "Panner Rule", "Panner" };
    juce::Label panLabel{ "Panner Pan", "Pan" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PannerComponent)
};
