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
    OscComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setOscParams(juce::ComboBox& comboBox);

    // Butonul in sine
    juce::ComboBox oscSelector;
    
    // Attachment catre variabila din ValueTreeState
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ComboBoxAttachment> oscSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
