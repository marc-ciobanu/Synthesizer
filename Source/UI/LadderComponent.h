/*
  ==============================================================================

    LadderComponent.h
    Created: 2 Jun 2024 3:25:56am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LadderComponent  : public juce::Component
{
public:
    LadderComponent(juce::AudioProcessorValueTreeState& apvts);
    ~LadderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox ladderMode;
    juce::Slider ladderCutoff;
    juce::Slider ladderResonance;
    juce::Slider ladderDrive;

    // Attachment catre variabila din ValueTreeState
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ladderModeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ladderCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ladderResonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ladderDriveAttachment;

    juce::Label ladderCutoffLabel{ "Ladder Cutoff", "Cutoff" };
    juce::Label ladderResonanceLabel{ "Ladder Resonance", "Resonance" };
    juce::Label ladderDriveLabel{ "Ladder Drive", "Drive" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LadderComponent)
};
