/*
  ==============================================================================

    CompressorComponent.h
    Created: 31 May 2024 2:46:00pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CompressorComponent  : public juce::Component
{
public:
    CompressorComponent();
    ~CompressorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorComponent)
};
