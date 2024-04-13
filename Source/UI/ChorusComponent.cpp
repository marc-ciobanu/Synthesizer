/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 13 Apr 2024 11:37:59am
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts)
{
    chorusRateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "CHORUSRATE", chorusRateSlider);
    chorusDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "CHORUSDEPTH", chorusDepthSlider);
    chorusCentreDelayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "CHORUSCENTREDELAY", chorusCentreDelaySlider);
    chorusFeedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "CHORUSFEEDBACK", chorusFeedbackSlider);
    chorusMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "CHORUSMIX", chorusMixSlider);

    setSliderStyle(chorusRateSlider, chorusRateLabel);
    setSliderStyle(chorusDepthSlider, chorusDepthLabel);
    setSliderStyle(chorusCentreDelaySlider, chorusCentreDelayLabel);
    setSliderStyle(chorusFeedbackSlider, chorusFeedbackLabel);
    setSliderStyle(chorusMixSlider, chorusMixLabel);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Chorus", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void ChorusComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    chorusRateSlider.setBounds(10, startPosY + 5, sliderWidth, sliderHeight);
    chorusRateLabel.setBounds(10, startPosY - labelYOffset, 90, labelHeight);

    chorusDepthSlider.setBounds(chorusRateSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    chorusDepthLabel.setBounds(chorusDepthSlider.getX(), chorusDepthSlider.getY() - labelYOffset, chorusDepthSlider.getWidth(), labelHeight);

    chorusCentreDelaySlider.setBounds(chorusDepthSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    chorusCentreDelayLabel.setBounds(chorusCentreDelaySlider.getX(), chorusCentreDelaySlider.getY() - labelYOffset, chorusCentreDelaySlider.getWidth(), labelHeight);

    chorusFeedbackSlider.setBounds(chorusCentreDelaySlider.getRight(), startPosY, sliderWidth, sliderHeight);
    chorusFeedbackLabel.setBounds(chorusFeedbackSlider.getX(), chorusFeedbackSlider.getY() - labelYOffset, chorusFeedbackSlider.getWidth(), labelHeight);

    chorusMixSlider.setBounds(chorusFeedbackSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    chorusMixLabel.setBounds(chorusMixSlider.getX(), chorusMixSlider.getY() - labelYOffset, chorusMixSlider.getWidth(), labelHeight);

}

void ChorusComponent::setSliderStyle(juce::Slider& slider, juce::Label& label)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
}