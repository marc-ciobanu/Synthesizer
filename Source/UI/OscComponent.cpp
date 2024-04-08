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
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colour(0xff135d66));
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    oscSelector.setBounds(10, startPosY + 5, 90, 30);
    oscSelectorLabel.setBounds(10, startPosY - labelYOffset, 90, labelHeight);

    fmFreqSlider.setBounds(oscSelector.getRight(), startPosY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);
    
    fmDepthSlider.setBounds(fmFreqSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
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