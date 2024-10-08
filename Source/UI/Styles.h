// Styles.h

#pragma once

#include <JuceHeader.h>

class Styles
{
public:
    static void setRotarySlider(juce::Slider& slider, juce::Label& label, juce::Component& component, juce::Colour color);
    static void setVerticalSlider(juce::Slider& slider, juce::Label& label, juce::Component& component, juce::Colour color);
    static void setComboBox(juce::ComboBox& combobox, juce::Component& component, juce::Colour color);
    static void paintComponent(juce::Graphics& g);

private:
    juce::Colour sliderColour = juce::Colour(0xFFDAD3BE);
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
            g.fillEllipse((float)rx, (float)ry, (float)rw, (float)rw);

            // Outline
            g.setColour(slider.findColour(juce::Slider::rotarySliderOutlineColourId));
            g.drawEllipse((float)rx, (float)ry, (float)rw, (float)rw, 2.0f);

            juce::Path p;
            auto pointerLength = radius * 0.6f;
            auto pointerThickness = 2.0f;
            p.addRoundedRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength, 1.0f);
            p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

            // Pointer
            g.setColour(slider.findColour(juce::Slider::thumbColourId));
            g.fillPath(p);
        }

        void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
            float sliderPos, float minSliderPos, float maxSliderPos,
            const juce::Slider::SliderStyle style, juce::Slider& slider) override
        {
            auto trackWidth = 5.0f;
            auto startX = (float)x + (float)width * 0.5f - trackWidth * 0.5f;
            auto startY = (float)y;
            auto endX = startX;
            auto endY = (float)y + (float)height;
            auto cornerSize = 3.0f; // Corner radius for rounded edges

            // Fill with rounded rectangle
            g.setColour(juce::Colours::transparentBlack);
            g.fillRoundedRectangle((float)startX, (float)startY, trackWidth, (float)height, cornerSize);

            // Outline with rounded rectangle
            g.setColour(slider.findColour(juce::Slider::rotarySliderOutlineColourId));
            g.drawRoundedRectangle((float)startX, (float)startY, trackWidth, (float)height, cornerSize, 2.0f);

            // Thumb
            auto thumbWidth = 15.0f;
            auto thumbHeight = 10.0f;
            auto thumbX = startX + trackWidth * 0.5f - thumbWidth * 0.5f;
            auto thumbY = sliderPos - thumbHeight * 0.5f;
            auto thumbCorner = 3.0f;

            // Filled thumb
            g.setColour(slider.findColour(juce::Slider::thumbColourId));
            g.fillRoundedRectangle((float)thumbX, (float)thumbY, thumbWidth, thumbHeight, thumbCorner);
        }

        void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
            int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box)
        {
            g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
            g.fillRoundedRectangle(0.0f, 0.0f, (float)width, (float)height, 5.0f);

            g.setColour(box.findColour(juce::ComboBox::outlineColourId));
            g.drawRoundedRectangle(0.0f, 0.0f, (float)width, (float)height, 5.0f, 2.0f);

            juce::Rectangle<int> arrowZone(width - 30, 0, 20, height);
            juce::Path path;
            path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
            path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
            path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

            g.setColour(box.findColour(juce::ComboBox::arrowColourId));
            g.strokePath(path, juce::PathStrokeType(2.0f));
        }
    };

    static CustomLookAndFeel customLookAndFeel; // Declaration only
};
