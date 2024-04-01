/*
  ==============================================================================

    OscComponent.cpp
    Created: 2 Apr 2024 12:14:10am
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts)
{
    
    
    juce::StringArray waveTypes{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(waveTypes, 1);

    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    oscSelectorAttachment = std::make_unique<ComboBoxAttachment>(apvts, "OSC", oscSelector);

    setOscParams(oscSelector);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscSelector.setBounds(0, 0, 90, 20);

}

void OscComponent::setOscParams(juce::ComboBox& comboBox) {
    addAndMakeVisible(comboBox);
}
