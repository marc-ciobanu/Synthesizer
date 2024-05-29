#pragma once

#include <JuceHeader.h>

class Styles
{
public:
    static void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::Component& component);

private:
    // Custom LookAndFeel class for additional slider customization
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
            float sliderPosProportional, float rotaryStartAngle,
            float rotaryEndAngle, juce::Slider& slider) override
        {
            auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
            auto centreX = (float)x + (float)width * 0.5f;
            auto centreY = (float)y + (float)height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

            // Fill
            g.setColour(juce::Colours::transparentBlack);
            g.fillEllipse(rx, ry, rw, rw);

            // Outline
            g.setColour(slider.findColour(juce::Slider::rotarySliderOutlineColourId));
            g.drawEllipse(rx, ry, rw, rw, 2.0f);

            juce::Path p;
            auto pointerLength = radius * 0.6f;
            auto pointerThickness = 2.0f;
            p.addRoundedRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength, 1.0f);
            p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

            // Pointer
            g.setColour(slider.findColour(juce::Slider::thumbColourId));
            g.fillPath(p);
        }
    };

    static CustomLookAndFeel customLookAndFeel; // Declaration only
};
