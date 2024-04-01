/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"

//==============================================================================
/**
*/
class Synth1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Synth1AudioProcessor& audioProcessor;

    AdsrComponent adsr;

    OscComponent osc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
};
