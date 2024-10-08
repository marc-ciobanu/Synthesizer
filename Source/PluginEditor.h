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
#include "UI/FilterComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/ChorusComponent.h"
#include "UI/PhaserComponent.h"
#include "UI/LadderComponent.h"
#include "UI/CompressorComponent.h"
#include "UI/PannerComponent.h"

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

    OscComponent osc;

    AdsrComponent adsr;

    FilterComponent filter;

    AdsrComponent modAdsr;

    LadderComponent ladder;

    ReverbComponent reverb;

    ChorusComponent chorus;

    PhaserComponent phaser;

    CompressorComponent compressor;

    PannerComponent panner;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
};
