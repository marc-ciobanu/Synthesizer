/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Mar 2024 11:37:14am
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"
#include "Data/ReverbData.h"
#include "Data/ChorusData.h"
#include "Data/DelayData.h"


class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateFilter(const int filterType, const float frequency, const float resonance);
    void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateReverb(float roomSize, float damping, float wetLevel, float dryLevel, float reverbWidth);
    void updateChorus(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix);
    void updateDelay(int samples, float feedback, float wetLevel, float dryLevel);

    OscData& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return modAdsr; }
    FilterData& getFilter() { return filter; }

    
private:
    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;
    ReverbData reverb;
    ChorusData chorus;
    DelayData delay;

    juce::dsp::Gain<float> gain;

    bool isPrepared{ false };
};