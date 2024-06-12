/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 12 Apr 2024 3:37:15pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"
#include "Styles.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts)
{
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBROOMSIZE", roomSizeSlider);
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBDAMPING", dampingSlider);
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWETLEVEL", wetLevelSlider);
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBDRYLEVEL", dryLevelSlider);
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "REVERBWIDTH", widthSlider);

    Styles::setRotarySlider(roomSizeSlider, roomSizeLabel, *this, juce::Colour(0xFFff8531));
    Styles::setRotarySlider(dampingSlider, dampingLabel, *this, juce::Colour(0xFFff8531));
    Styles::setRotarySlider(wetLevelSlider, wetLevelLabel, *this, juce::Colour(0xFFff8531));
    Styles::setRotarySlider(dryLevelSlider, dryLevelLabel, *this, juce::Colour(0xFFff8531));
    Styles::setRotarySlider(widthSlider, widthLabel, *this, juce::Colour(0xFFff8531));
}

ReverbComponent::~ReverbComponent(){}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
    /*g.drawText("Reverb", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);*/
}

void ReverbComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto labelYOffset = 15;
    const auto labelHeight = 15;

    roomSizeSlider.setBounds(10, startPosY, sliderWidth, sliderHeight);
    roomSizeLabel.setBounds(0, startPosY - labelYOffset, 90, labelHeight);

    dampingSlider.setBounds(roomSizeSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    dampingLabel.setBounds(dampingSlider.getX(), dampingSlider.getY() - labelYOffset, dampingSlider.getWidth(), labelHeight);

    wetLevelSlider.setBounds(dampingSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    wetLevelLabel.setBounds(wetLevelSlider.getX(), wetLevelSlider.getY() - labelYOffset, wetLevelSlider.getWidth(), labelHeight);

    dryLevelSlider.setBounds(wetLevelSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    dryLevelLabel.setBounds(dryLevelSlider.getX(), dryLevelSlider.getY() - labelYOffset, dryLevelSlider.getWidth(), labelHeight);
    
    widthSlider.setBounds(dryLevelSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    widthLabel.setBounds(widthSlider.getX(), widthSlider.getY() - labelYOffset, widthSlider.getWidth(), labelHeight);
}
