/*
  ==============================================================================

    ReverbComponent.h
    Created: 12 Apr 2024 3:37:15pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent();
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
