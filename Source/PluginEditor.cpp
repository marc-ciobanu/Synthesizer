/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC", "FMFREQ", "FMDEPTH"), adsr(audioProcessor.apvts)
{
    setSize (400, 300);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

void Synth1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void Synth1AudioProcessorEditor::resized()
{
    osc.setBounds(10, 10, 180, 200);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}


