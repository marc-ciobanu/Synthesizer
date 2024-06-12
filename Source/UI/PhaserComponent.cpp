/*
  ==============================================================================

    PhaserComponent.cpp
    Created: 4 Jun 2024 2:15:00pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PhaserComponent.h"
#include "Styles.h"

//==============================================================================
PhaserComponent::PhaserComponent(juce::AudioProcessorValueTreeState& apvts)
{
    phaserRateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PHASERRATE", phaserRateSlider);
    phaserDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PHASERDEPTH", phaserDepthSlider);
    phaserCentreDelayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PHASERCENTREDELAY", phaserCentreDelaySlider);
    phaserFeedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PHASERFEEDBACK", phaserFeedbackSlider);
    phaserMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PHASERMIX", phaserMixSlider);

    Styles::setRotarySlider(phaserRateSlider, phaserRateLabel, *this, juce::Colour(0xFFbc5090));
    Styles::setRotarySlider(phaserDepthSlider, phaserDepthLabel, *this, juce::Colour(0xFFbc5090));
    Styles::setRotarySlider(phaserCentreDelaySlider, phaserCentreDelayLabel, *this, juce::Colour(0xFFbc5090));
    Styles::setRotarySlider(phaserFeedbackSlider, phaserFeedbackLabel, *this, juce::Colour(0xFFbc5090));
    Styles::setRotarySlider(phaserMixSlider, phaserMixLabel, *this, juce::Colour(0xFFbc5090));
}

PhaserComponent::~PhaserComponent() {}

void PhaserComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
    /*g.drawText("Phaser", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);*/
}

void PhaserComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto labelYOffset = 15;
    const auto labelHeight = 15;

    phaserRateSlider.setBounds(10, startPosY, sliderWidth, sliderHeight);
    phaserRateLabel.setBounds(0, startPosY - labelYOffset, 90, labelHeight);

    phaserDepthSlider.setBounds(phaserRateSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    phaserDepthLabel.setBounds(phaserDepthSlider.getX(), phaserDepthSlider.getY() - labelYOffset, phaserDepthSlider.getWidth(), labelHeight);

    phaserCentreDelaySlider.setBounds(phaserDepthSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    phaserCentreDelayLabel.setBounds(phaserCentreDelaySlider.getX(), phaserCentreDelaySlider.getY() - labelYOffset, phaserCentreDelaySlider.getWidth(), labelHeight);

    phaserFeedbackSlider.setBounds(phaserCentreDelaySlider.getRight(), startPosY, sliderWidth, sliderHeight);
    phaserFeedbackLabel.setBounds(phaserFeedbackSlider.getX(), phaserFeedbackSlider.getY() - labelYOffset, phaserFeedbackSlider.getWidth(), labelHeight);

    phaserMixSlider.setBounds(phaserFeedbackSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    phaserMixLabel.setBounds(phaserMixSlider.getX(), phaserMixSlider.getY() - labelYOffset, phaserMixSlider.getWidth(), labelHeight);
}
