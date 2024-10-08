/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 Apr 2024 5:21:15pm
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"
#include "Styles.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray filterTypes{ "Lowpass", "Bandpass", "Highpass" };
    filterSelector.addItemList(filterTypes, 1);

    filterSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterSelector);
    filterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERCUTOFF", filterCutoff);
    filterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERRES", filterRes);

    Styles::setComboBox(filterSelector, *this, juce::Colour(0xFF809bce));
    Styles::setRotarySlider(filterCutoff, filterCutoffLabel, *this, juce::Colour(0xFF809bce));
    Styles::setRotarySlider(filterRes, filterResLabel, *this, juce::Colour(0xFF809bce));
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
    /*g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);*/
}

void FilterComponent::resized()
{
    const auto xFilter = 35;
    const auto yFilter = 65;
    const auto filterWidth = 205;
    const auto filterHeight = 30;

    const auto xSlide = 35;
    const auto ySlide = 130;
    const auto sliderWidth = 102.5;
    const auto sliderHeight = 90;

    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterSelector.setBounds(xFilter, yFilter, filterWidth, filterHeight);

    filterCutoff.setBounds(xSlide, ySlide, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoff.getX(), filterCutoff.getY() - labelYOffset, filterCutoff.getWidth(), labelHeight);

    filterRes.setBounds(xSlide + sliderWidth, ySlide, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterRes.getX(), filterRes.getY() - labelYOffset, filterRes.getWidth(), labelHeight);
    

    /*const auto startPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterSelector.setBounds(10, startPosY + 5, 90, 30);
    filterSelectorLabel.setBounds(10, startPosY - labelYOffset, 90, labelHeight);

    filterCutoff.setBounds(filterSelector.getRight(), startPosY, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoff.getX(), filterCutoff.getY() - labelYOffset, filterCutoff.getWidth(), labelHeight);

    filterRes.setBounds(filterCutoff.getRight(), startPosY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterRes.getX(), filterRes.getY() - labelYOffset, filterRes.getWidth(), labelHeight);*/

}

//void FilterComponent::setComboBoxStyle(juce::ComboBox& combobox, juce::Label& label)
//{
//    addAndMakeVisible(combobox);
//    addAndMakeVisible(label);
//
//    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
//    label.setFont(15.0f);
//    label.setJustificationType(juce::Justification::centred);
//}