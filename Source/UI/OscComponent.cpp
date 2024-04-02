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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    
    
    juce::StringArray waveTypes{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(waveTypes, 1);

    oscSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscSelectorId, oscSelector);

    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);

    setOscStyle(oscSelector);
    setFmSliderStyle(fmFreqSlider, fmFreqLabel);
    setFmSliderStyle(fmDepthSlider, fmDepthLabel);
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
    fmFreqSlider.setBounds(0, 80, 100, 90);
    fmDepthSlider.setBounds(fmFreqSlider.getWidth(), 80, 100, 90);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - 20, fmFreqSlider.getWidth(), 20);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - 20, fmDepthSlider.getWidth(), 20);
}

void OscComponent::setOscStyle(juce::ComboBox& comboBox) 
{
    addAndMakeVisible(comboBox);
}

void OscComponent::setFmSliderStyle(juce::Slider& slider, juce::Label& label)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
}