/*
  ==============================================================================

    LadderComponent.h
    Created: 2 Jun 2024 3:25:56am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LadderComponent  : public juce::Component
{
public:
    LadderComponent();
    ~LadderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LadderComponent)
};
