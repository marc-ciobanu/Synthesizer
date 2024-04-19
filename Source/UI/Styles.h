/*
  ==============================================================================

    Styles.h
    Created: 15 Apr 2024 1:09:28pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Styles 
{
public:
    static void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::Component& component)
    {
        component.addAndMakeVisible(slider);
        component.addAndMakeVisible(label);

        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
        label.setFont(15.0f);
        label.setJustificationType(juce::Justification::centred);
    }

private:

};