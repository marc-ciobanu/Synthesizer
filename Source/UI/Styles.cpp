#include "Styles.h"

// Define the static member
Styles::CustomLookAndFeel Styles::customLookAndFeel;

void Styles::setRotarySlider(juce::Slider& slider, juce::Label& label, juce::Component& component)
{
    component.addAndMakeVisible(slider);
    component.addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    // Set minimalist color scheme
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFFD0EFBD));
    slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFD0EFBD));
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);

    slider.setLookAndFeel(&customLookAndFeel);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(juce::Font("Cascadia Code", 15.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
}

void Styles::setVerticalSlider(juce::Slider& slider, juce::Label& label, juce::Component& component)
{
    component.addAndMakeVisible(slider);
    component.addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    // Set minimalist color scheme
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFFD0EFBD));
    slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFD0EFBD));
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);

    slider.setLookAndFeel(&customLookAndFeel);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(juce::Font("Cascadia Code", 15.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
}
