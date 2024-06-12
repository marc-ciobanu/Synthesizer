/*
  ==============================================================================

    PannerComponent.cpp
    Created: 11 Jun 2024 8:35:45pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PannerComponent.h"
#include "Styles.h"

//==============================================================================
PannerComponent::PannerComponent(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray pannerRules{ "linear", "balanced", "sin3dB", "sin4p5dB", "sin6dB", "squareRoot3dB", "squareRoot4p5dB" };
    rule.addItemList(pannerRules, 1);

    ruleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "PANNERRULE", rule);
    panAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PANNERPAN", pan);

    Styles::setComboBox(rule, *this);
    Styles::setRotarySlider(pan, panLabel, *this);

    addAndMakeVisible(ruleLabel);
}

PannerComponent::~PannerComponent()
{
}

void PannerComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
}

void PannerComponent::resized()
{
    const auto xFilter = 35;
    const auto yFilter = 30;
    const auto filterWidth = 130;
    const auto filterHeight = 30;

    const auto xSlide = 0;
    const auto ySlide = 70;
    const auto sliderWidth = 102.5;
    const auto sliderHeight = 85;

    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    rule.setBounds(xFilter, yFilter, filterWidth, filterHeight);

    ruleLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    ruleLabel.setFont(juce::Font("Cascadia Code", 20.0f, juce::Font::plain));
    ruleLabel.setJustificationType(juce::Justification::left);
    ruleLabel.setBounds(rule.getX() - 5, rule.getY() - labelYOffset - 5, rule.getWidth(), labelHeight);
    

    pan.setBounds(rule.getRight() - 5, yFilter - (filterHeight / 2), sliderWidth, sliderHeight);
    panLabel.setBounds(pan.getX(), pan.getY() - labelYOffset, pan.getWidth(), labelHeight);

}
