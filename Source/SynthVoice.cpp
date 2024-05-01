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
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
    modAdsr.noteOff();
}

//void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
//    osc.setWaveFrequency(midiNoteNumber);
//    adsr.noteOn();
//    modAdsr.noteOn();
//
//    isNotePlaying = true;
//    currentNote = midiNoteNumber;
//}
//
//void SynthVoice::stopNote(float velocity, bool allowTailOff) {
//    adsr.noteOff();
//    modAdsr.noteOff();
//
//    isNotePlaying = false;
//    currentNote = -1;
//}

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

    gain.setGainLinear(0.3f);
    osc.prepareToPlay(spec);
    gain.prepare(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    modAdsr.setSampleRate(sampleRate);
    reverb.setSampleRate(sampleRate);
    chorus.prepareToPlay(sampleRate, samplesPerBlock);
    //eq.prepareToPlay(sampleRate, samplesPerBlock);

    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) 
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    osc.getNextAudioBlock(audioBlock);

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

    filter.process(outputBuffer);

    modAdsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    modAdsr.getNextSample();

    reverb.process(outputBuffer, numSamples);

    chorus.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    //eq.process(outputBuffer);
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release) 
{
    adsr.updateParameters(attack, decay, sustain, release);
}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, cutoff, resonance, modulator);
}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateParameters(attack, decay, sustain, release);
}

void SynthVoice::updateReverb(float roomSize, float damping, float wetLevel, float dryLevel, float reverbWidth)
{
    reverb.updateParameters(roomSize, damping, wetLevel, dryLevel, reverbWidth);
}

void SynthVoice::updateChorus(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix)
{
    chorus.updateParameteres(chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix);
}

//void SynthVoice::updateEq(double sampleRate, float peakFreq, float peakQuality, float peakGainInDecibels, float lowCutFreq, float highCutFreq, Slope lowCutSlope, Slope highCutSlope)
//{
//    eq.updatePeakFilter(sampleRate, peakFreq, peakQuality, peakGainInDecibels);
//    eq.updateLowCutFilter(sampleRate, lowCutFreq, lowCutSlope);
//    eq.updateHighCutFilter(sampleRate, highCutFreq, highCutSlope);
//
//}