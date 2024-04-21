/*
  ==============================================================================

    EqComponent.h
    Created: 21 Apr 2024 1:34:02pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EqComponent  : public juce::Component
{
public:
    EqComponent();
    ~EqComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqComponent)
};
