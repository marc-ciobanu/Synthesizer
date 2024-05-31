/*
  ==============================================================================

    LimiterComponent.h
    Created: 31 May 2024 2:45:45pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LimiterComponent  : public juce::Component
{
public:
    LimiterComponent();
    ~LimiterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LimiterComponent)
};
