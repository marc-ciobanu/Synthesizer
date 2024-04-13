/*
  ==============================================================================

    ChorusComponent.h
    Created: 13 Apr 2024 11:37:59am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent();
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
