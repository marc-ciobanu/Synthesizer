/*
  ==============================================================================

    CompressorComponent.cpp
    Created: 4 Jun 2024 4:15:00pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CompressorComponent.h"
#include "Styles.h"

//==============================================================================
CompressorComponent::CompressorComponent(juce::AudioProcessorValueTreeState& apvts)
{
    compressorThresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "COMPRESSORTHRESHOLD", compressorThresholdSlider);
    compressorRatioAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "COMPRESSORRATIO", compressorRatioSlider);
    compressorAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "COMPRESSORATTACK", compressorAttackSlider);
    compressorReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "COMPRESSORRELEASE", compressorReleaseSlider);

    Styles::setRotarySlider(compressorThresholdSlider, compressorThresholdLabel, *this);
    Styles::setRotarySlider(compressorRatioSlider, compressorRatioLabel, *this);
    Styles::setRotarySlider(compressorAttackSlider, compressorAttackLabel, *this);
    Styles::setRotarySlider(compressorReleaseSlider, compressorReleaseLabel, *this);
}

CompressorComponent::~CompressorComponent() {}

void CompressorComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
}

void CompressorComponent::resized()
{
    const auto startPosY = 55;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto labelYOffset = 15;
    const auto labelHeight = 15;

    compressorThresholdSlider.setBounds(10, startPosY, sliderWidth, sliderHeight);
    compressorThresholdLabel.setBounds(0, startPosY - labelYOffset, 90, labelHeight);

    compressorRatioSlider.setBounds(compressorThresholdSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    compressorRatioLabel.setBounds(compressorRatioSlider.getX(), compressorRatioSlider.getY() - labelYOffset, compressorRatioSlider.getWidth(), labelHeight);

    compressorAttackSlider.setBounds(compressorRatioSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    compressorAttackLabel.setBounds(compressorAttackSlider.getX(), compressorAttackSlider.getY() - labelYOffset, compressorAttackSlider.getWidth(), labelHeight);

    compressorReleaseSlider.setBounds(compressorAttackSlider.getRight(), startPosY, sliderWidth, sliderHeight);
    compressorReleaseLabel.setBounds(compressorReleaseSlider.getX(), compressorReleaseSlider.getY() - labelYOffset, compressorReleaseSlider.getWidth(), labelHeight);
}
