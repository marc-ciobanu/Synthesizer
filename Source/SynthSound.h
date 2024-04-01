/*
  ==============================================================================

    SynthSound.h
    Created: 20 Mar 2024 11:37:55am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

private:

};