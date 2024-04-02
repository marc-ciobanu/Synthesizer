/*
  ==============================================================================

    OscData.cpp
    Created: 1 Apr 2024 11:40:51pm
    Author:  admin

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    fmOsc.prepare(spec);
    prepare (spec);
}

void OscData::setWaveType(const int waveType) {

    switch (waveType)
    {
    case 0:
        // Sine Wave
        initialise([](float x) { return std::sin(x); });
        break;
    case 1:
        // Saw Wave
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        // Square Wave
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default:
        jassertfalse; // You're not supposed to be here
        break;
    }


}

void OscData::setWaveFrequency(const int midiNoteNumber) {

    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock) {

    // ch = channel
    for (int ch = 0; ch < audioBlock.getNumChannels(); ++ch) {
        // s = sample
        for (int s = 0; s < audioBlock.getNumSamples(); ++s) {
            fmMod = fmOsc.processSample (audioBlock.getSample(ch, s)) * fmDepth;
        }
    }

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::setFmParams(const float depth, const float freq) {
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    setFrequency(abs(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod));
}