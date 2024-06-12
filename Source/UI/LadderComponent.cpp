/*
  ==============================================================================

    LadderComponent.cpp
    Created: 2 Jun 2024 3:25:56am
    Author:  admin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LadderComponent.h"
#include "Styles.h"

//==============================================================================
LadderComponent::LadderComponent(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray ladderModes{ "LPF12", "HPF12", "BPF12", "LPF24", "HPF24", "BPF24" };
    ladderMode.addItemList(ladderModes, 1);

    ladderModeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "LADDERMODE", ladderMode);
    ladderCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "LADDERCUTOFF", ladderCutoff);
    ladderResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "LADDERRESONANCE", ladderResonance);
    ladderDriveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "LADDERDRIVE", ladderDrive);

    Styles::setComboBox(ladderMode, *this, juce::Colour(0xFF003f5c));
    Styles::setRotarySlider(ladderCutoff, ladderCutoffLabel, *this, juce::Colour(0xFF003f5c));
    Styles::setRotarySlider(ladderResonance, ladderResonanceLabel, *this, juce::Colour(0xFF003f5c));
    Styles::setRotarySlider(ladderDrive, ladderDriveLabel, *this, juce::Colour(0xFF003f5c));
}

LadderComponent::~LadderComponent()
{
}

void LadderComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    Styles::paintComponent(g);
}

void LadderComponent::resized()
{
    const auto xFilter = 35;
    const auto yFilter = 85;
    const auto filterWidth = 205;
    const auto filterHeight = 30;

    const auto xSlide = 35;
    const auto ySlide = 150;
    const auto sliderWidth = filterWidth / 3;
    const auto sliderHeight = 80;

    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    ladderMode.setBounds(xFilter, yFilter, filterWidth, filterHeight);

    ladderCutoff.setBounds(xSlide, ySlide, sliderWidth, sliderHeight);
    ladderCutoffLabel.setBounds(ladderCutoff.getX(), ladderCutoff.getY() - labelYOffset, ladderCutoff.getWidth(), labelHeight);

    ladderResonance.setBounds(xSlide + sliderWidth, ySlide, sliderWidth, sliderHeight);
    ladderResonanceLabel.setBounds(ladderResonance.getX(), ladderResonance.getY() - labelYOffset, ladderResonance.getWidth(), labelHeight);

    ladderDrive.setBounds(xSlide + 2 * sliderWidth, ySlide, sliderWidth, sliderHeight);
    ladderDriveLabel.setBounds(ladderDrive.getX(), ladderDrive.getY() - labelYOffset, ladderDrive.getWidth(), labelHeight);

}
