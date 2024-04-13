/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor(Synth1AudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc(audioProcessor.apvts, "OSC", "FMFREQ", "FMDEPTH")
    , adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filter(audioProcessor.apvts)
    , modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
    , reverb(audioProcessor.apvts)
    , chorus(audioProcessor.apvts)
{
    setSize(1000,700);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);
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
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;
    const auto width = 300;
    const auto height = 200;

    osc.setBounds(paddingX, paddingY, width, height);
    adsr.setBounds(osc.getRight(), paddingY, width, height);
    filter.setBounds(paddingX, paddingY2, width, height);
    modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
    reverb.setBounds(paddingX, 435, 490, height);
    chorus.setBounds(reverb.getRight(), 435, 490, height);
}


