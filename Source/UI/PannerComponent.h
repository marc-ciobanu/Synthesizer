/*
  ==============================================================================

    PannerComponent.h
    Created: 11 Jun 2024 8:35:45pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PannerComponent  : public juce::Component
{
public:
    PannerComponent();
    ~PannerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PannerComponent)
};
