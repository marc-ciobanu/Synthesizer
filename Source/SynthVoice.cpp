/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Mar 2024 11:37:14am
    Author:  admin

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();

}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    gain.prepare(spec);

    
    gain.setGainLinear(0.3f);

    isPrepared = true;
}



void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    osc.getNextAudioBlock(audioBlock);

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}