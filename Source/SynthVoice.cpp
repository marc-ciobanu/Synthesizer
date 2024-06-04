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
    phaser.prepareToPlay(sampleRate, samplesPerBlock);
    compressor.preprareToPlay(sampleRate, samplesPerBlock);
    ladder.prepareToPlay(sampleRate, samplesPerBlock);

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
    phaser.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    compressor.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    ladder.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

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

void SynthVoice::updatePhaser(float phaserRate, float phaserDepth, float phaserCentre, float phaserFeedback, float phaserMix)
{
    phaser.updateParameters(phaserRate, phaserDepth, phaserCentre, phaserFeedback, phaserMix);
}

void SynthVoice::updateCompressor(float compressorThreshold, float compressorRatio, float compressorAttack, float compressorRelease)
{
    compressor.updateParameters(compressorThreshold, compressorRatio, compressorAttack, compressorRelease);
}

void SynthVoice::updateLadder(bool ladderEnable, int ladderMode, float ladderCutoff, float ladderResonance, float ladderDrive)
{
    ladder.updateParameters(ladderEnable, ladderMode, ladderCutoff, ladderResonance, ladderDrive);
}
