#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);
    modAdsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    gain.setGainLinear(0.3f);
    osc.prepareToPlay(spec);
    gain.prepare(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    reverb.setSampleRate(sampleRate);
    chorus.prepareToPlay(sampleRate, samplesPerBlock);
    delay.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    // Clear the buffer to avoid any residual data
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    // Process the oscillator output
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.getNextAudioBlock(audioBlock);

    // Apply envelopes
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    // Apply filter
    filter.process(synthBuffer);

    // Apply reverb and chorus
    reverb.process(synthBuffer, synthBuffer.getNumSamples());
    chorus.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    delay.process(outputBuffer);


    // Mix the processed buffer to the output buffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
    }

    // Clear the current note if ADSR is inactive
    if (!adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateParameters(attack, decay, sustain, release);
}

void SynthVoice::updateFilter(const int filterType, const float frequency, const float resonance)
{
    auto modulator = modAdsr.getNextSample();
    filter.updateParameters(modulator, filterType, frequency, resonance);
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

void SynthVoice::updateDelay(int samples, float feedback, float wetLevel, float dryLevel)
{
    delay.updateParameteres(samples, feedback, wetLevel, dryLevel);
}