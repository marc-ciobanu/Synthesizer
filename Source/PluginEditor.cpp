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
    , phaser(audioProcessor.apvts)
    , ladder(audioProcessor.apvts)
{
    setSize(1000, 700);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(ladder);

    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);
    addAndMakeVisible(phaser);
    

    repaint();
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

void Synth1AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xFF192E25));
    // parameters: X up-left corner, Y up-left corner, Grosime, Inaltime, Radius of corners, Thickness of outline

    // height2 + paddingY + paddingX + 70
    /////// RECTANGLES VARIABLES ////////
    const auto paddingX = 15;
    const auto paddingY = 80;
    const auto width1 = 275;
    const auto height1 = 605;
    const auto radius = 10;
    const auto thickness = 2;

    const auto width2 = 390;
    const auto height2 = 210;
    const auto height3 = 380;

    //////// TEXT VARIABLES /////// 
    const auto xOscLabel = 15;
    const auto yOscLabel = 110;
    const auto oscLabelWidth = 275;
    const auto oscLabelHeight = 20;

    ///////// DRAWING TEXT ////////////

    g.setColour(juce::Colour(0xFFDAD3BE));
    g.setFont(juce::Font("Cascadia Code", 22.0f, juce::Font::plain));

    g.drawText("OSCILLATOR", xOscLabel, yOscLabel, oscLabelWidth, oscLabelHeight, juce::Justification::centred);
    g.drawText("FM MODULATION", xOscLabel, height1 - 85, oscLabelWidth, oscLabelHeight, juce::Justification::centred);
    g.drawText("FILTER", width1 + 2 * paddingX, yOscLabel, oscLabelWidth, oscLabelHeight, juce::Justification::centred);
    g.drawText("LADDER FILTER", width1 + 2 * paddingX, yOscLabel + 390, oscLabelWidth, oscLabelHeight - 10, juce::Justification::centred);

    g.setFont(juce::Font("Cascadia Code", 24.0f, juce::Font::plain));
    g.drawText("EFFECTS", width1 * 2 + 3 * paddingX, height2 + paddingY - 15, width2, oscLabelHeight, juce::Justification::centred);

    g.setFont(juce::Font("Cascadia Code", 20.0f, juce::Font::plain));
    g.drawText("REVERB", width1 * 2 + 3 * paddingX, height2 + paddingY + 10, width2, oscLabelHeight, juce::Justification::centred);
    g.drawText("CHORUS", width1 * 2 + 3 * paddingX, height2 + paddingY + 140, width2, oscLabelHeight, juce::Justification::centred);
    g.drawText("PHASER", width1 * 2 + 3 * paddingX, height2 + paddingY + 160 + 110, width2, oscLabelHeight, juce::Justification::centred);


    ///////// DRAWING RECTANGLES ///////////////

    g.setColour(juce::Colours::white);

    // Oscillator    
    g.drawRoundedRectangle(paddingX, paddingY, width1, height1, radius, thickness);

    // Filter
    g.drawRoundedRectangle(width1 + 2 * paddingX, paddingY, width1, height1, radius, thickness);

    // Mixer
    g.drawRoundedRectangle(width1 * 2 + 3 * paddingX, paddingY, width2, height2 - 30, radius, thickness);

    // Effects
    g.drawRoundedRectangle(width1 * 2 + 3 * paddingX, paddingY + height2 - 20, width2, height3 + 35, radius, thickness);
}

void Synth1AudioProcessorEditor::resized()
{
    // Oscillator + FM Modulation
    const auto xOsc = 15;
    const auto yOsc = 80;
    const auto widthOsc = 275;
    const auto heightOsc = 605;
    osc.setBounds(xOsc, yOsc, widthOsc, heightOsc);

    // ADSR
    const auto xAdsr1 = 30;
    const auto yAdsr1 = 265;
    const auto widthAdsr = 245;
    const auto heightAdsr = 210;
    adsr.setBounds(xAdsr1, yAdsr1, widthAdsr, widthAdsr);
    
    // Filter
    const auto xFilter = 305;
    const auto yFilter = 80;
    filter.setBounds(xFilter, yFilter, widthOsc, heightOsc);

    // Filter ADSR
    const auto xModAdsr = 320;
    const auto yModAdsr = 275;
    modAdsr.setBounds(xModAdsr, yModAdsr, widthAdsr, heightAdsr);

    // Ladder
    const auto yLadder = 440;
    const auto heightLadder = 300;
    ladder.setBounds(xFilter, yLadder, widthOsc, heightLadder);

    // EFFECTS
    const auto xEffects = 582.5;
    const auto yEffects = 285;
    const auto widthEffects = 500;
    const auto heightEffects = 150;

    // Reverb
    reverb.setBounds(xEffects, yEffects, widthEffects, heightEffects);

    // Chorus
    chorus.setBounds(xEffects, yEffects + 130, widthEffects, heightEffects);

    // Phaser
    phaser.setBounds(xEffects, yEffects + 130 * 2, widthEffects, heightEffects);

    /*const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;
    const auto width = 300;
    const auto height = 200;*/
    
    //filter.setBounds(paddingX, paddingY2, width, height);
    //modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
    //reverb.setBounds(paddingX, 435, 490, height);
    //chorus.setBounds(reverb.getRight(), 435, 490, height);
}