/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 12 Apr 2024 3:37:15pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts)
{
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBROOMSIZE", roomSizeSlider);
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBDAMPING", dampingSlider);
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWETLEVEL", wetLevelSlider);
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBDRYLEVEL", dryLevelSlider);
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWIDTH", widthSlider);

    setSliderStyle(roomSizeSlider, roomSizeLabel);
    setSliderStyle(dampingSlider, dampingLabel);
    setSliderStyle(wetLevelSlider, wetLevelLabel);
    setSliderStyle(dryLevelSlider, dryLevelLabel);
    setSliderStyle(widthSlider, widthLabel);
}

ReverbComponent::~ReverbComponent(){}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Reverb", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void ReverbComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    roomSizeSlider.setBounds(10, startPosY + 5, 90, 30);
    roomSizeLabel.setBounds(10, startPosY - labelYOffset, 90, labelHeight);

    dampingSlider.setBounds(roomSizeSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    dampingLabel.setBounds(dampingSlider.getX(), dampingSlider.getY() - labelYOffset, dampingSlider.getWidth(), labelHeight);

    wetLevelSlider.setBounds(dampingSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    wetLevelLabel.setBounds(wetLevelSlider.getX(), wetLevelSlider.getY() - labelYOffset, wetLevelSlider.getWidth(), labelHeight);

    dryLevelSlider.setBounds(wetLevelSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    dryLevelLabel.setBounds(dryLevelSlider.getX(), dryLevelSlider.getY() - labelYOffset, dryLevelSlider.getWidth(), labelHeight);
    
    widthSlider.setBounds(dryLevelSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    widthLabel.setBounds(widthSlider.getX(), widthSlider.getY() - labelYOffset, widthSlider.getWidth(), labelHeight);
}

void ReverbComponent::setSliderStyle(juce::Slider& slider, juce::Label& label) 
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
}
