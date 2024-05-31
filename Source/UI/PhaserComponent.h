/*
  ==============================================================================

    PhaserComponent.h
    Created: 31 May 2024 2:45:23pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PhaserComponent  : public juce::Component
{
public:
    PhaserComponent();
    ~PhaserComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserComponent)
};
