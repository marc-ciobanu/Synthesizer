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
    setSize(1000, 700);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);

    repaint();
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

void Synth1AudioProcessorEditor::paint(juce::Graphics& g)
{
    const auto paddingX = 15;
    const auto paddingY = 80;
    const auto width1 = 275;
    const auto height1 = 605;
    const auto radius = 10;
    const auto thickness = 2;

    const auto width2 = 390;
    const auto height2 = 210;
    const auto height3 = 380;
    g.fillAll(juce::Colour(0xFF192E25));
    g.setColour(juce::Colours::white);
    // parameters: X up-left corner, Y up-left corner, Grosime, Inaltime, Radius of corners, Thickness of outline

    // Oscillator
    g.drawRoundedRectangle(paddingX, paddingY, width1, height1, radius, thickness);

    // Filter
    g.drawRoundedRectangle(width1 + 2 * paddingX, paddingY, width1, height1, radius, thickness);

    // Mixer
    g.drawRoundedRectangle(width1 * 2 + 3 * paddingX, paddingY, width2, height2, radius, thickness);

    // Effects
    g.drawRoundedRectangle(width1 * 2 + 3 * paddingX, height2 + paddingY + paddingX, width2, height3, radius, thickness);
}

void Synth1AudioProcessorEditor::resized()
{
    const auto paddingX = 15;
    const auto paddingY = 80;
    const auto width1 = 275;
    const auto height1 = 605;
    const auto radius = 10;
    const auto thickness = 2;

    const auto width2 = 390;
    const auto height2 = 210;
    const auto height3 = 380;

    /*const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;
    const auto width = 300;
    const auto height = 200;*/

    osc.setBounds(paddingX, paddingY, width1, height1);
    //adsr.setBounds(osc.getRight(), paddingY, width, height);
    //filter.setBounds(paddingX, paddingY2, width, height);
    //modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
    //reverb.setBounds(paddingX, 435, 490, height);
    //chorus.setBounds(reverb.getRight(), 435, 490, height);
}