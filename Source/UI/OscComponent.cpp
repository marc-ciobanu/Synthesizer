/*
  ==============================================================================

    OscComponent.cpp
    Created: 2 Apr 2024 12:14:10am
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"
#include "Styles.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray waveTypes{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(waveTypes, 1);

    oscSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscSelectorId, oscSelector);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);

    Styles::setComboBox(oscSelector, *this);
    Styles::setRotarySlider(fmFreqSlider, fmFreqLabel, *this);
    Styles::setRotarySlider(fmDepthSlider, fmDepthLabel, *this);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
    
    /*g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);*/
}

void OscComponent::resized()
{
    const auto xOsc = 35;
    const auto yOsc = 65;
    const auto oscWidth = 205;
    const auto oscHeight = 30;

    const auto xSlide = 35;
    const auto ySlide = 495;
    const auto sliderWidth = 102.5;
    const auto sliderHeight = 102.5;

    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    oscSelector.setBounds(xOsc, yOsc, oscWidth, oscHeight);
    //oscSelectorLabel.setBounds(10, startPosY - labelYOffset, 90, labelHeight);

    fmFreqSlider.setBounds(xSlide, ySlide, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);
    
    fmDepthSlider.setBounds(xSlide + sliderWidth, ySlide, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
}