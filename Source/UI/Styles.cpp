// Styles.cpp

#include "Styles.h"

// Define the static member

Styles::CustomLookAndFeel Styles::customLookAndFeel;

void Styles::paintComponent(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour(juce::Colour(0xFFDAD3BE));
    g.setFont(juce::Font("Cascadia Code", 20.0f, juce::Font::plain));
}

void Styles::setRotarySlider(juce::Slider& slider, juce::Label& label, juce::Component& component, juce::Colour color)
{
    component.addAndMakeVisible(slider);
    component.addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    // Set minimalist color scheme
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, color);
    slider.setColour(juce::Slider::thumbColourId, color);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxTextColourId, color);

    slider.setLookAndFeel(&customLookAndFeel);

    label.setColour(juce::Label::ColourIds::textColourId, color);
    label.setFont(juce::Font("Cascadia Code", 15.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
}

void Styles::setVerticalSlider(juce::Slider& slider, juce::Label& label, juce::Component& component, juce::Colour color)
{
    component.addAndMakeVisible(slider);
    component.addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    // Set minimalist color scheme
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, color);
    slider.setColour(juce::Slider::thumbColourId, color);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxTextColourId, color);

    slider.setLookAndFeel(&customLookAndFeel);

    label.setColour(juce::Label::ColourIds::textColourId, color);
    label.setFont(juce::Font("Cascadia Code", 15.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
}

void Styles::setComboBox(juce::ComboBox& combobox, juce::Component& component, juce::Colour color)
{
    component.addAndMakeVisible(combobox);
    combobox.setLookAndFeel(&customLookAndFeel);
    combobox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::transparentBlack);
    combobox.setColour(juce::ComboBox::outlineColourId, color);
    combobox.setColour(juce::ComboBox::textColourId, color);
    combobox.setColour(juce::ComboBox::arrowColourId, color);
    combobox.setColour(juce::ComboBox::buttonColourId, color);
}