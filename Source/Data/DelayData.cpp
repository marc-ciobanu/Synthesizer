/*
  ==============================================================================

    DelayData.cpp
    Created: 19 May 2024 10:32:06pm
    Author:  admin

  ==============================================================================
*/

#include "DelayData.h"

DelayData::DelayData() {}

DelayData::~DelayData() {}

void DelayData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels) {
    delayBuffer.setSize(numChannels, sampleRate, false, true, true);
    reset();
}

void DelayData::reset() {
    delayBuffer.clear();
    writePos = 0;
}

void DelayData::setDelayTime(int samples) {
    delayTime = juce::jlimit(0, delayBuffer.getNumSamples(), samples);
}

void DelayData::setFeedback(float feedback) {
    this->feedback = juce::jlimit(0.0f, 1.0f, feedback);
}

void DelayData::setWetLevel(float wetLevel) {
    this->wetLevel = juce::jlimit(0.0f, 1.0f, wetLevel);
}

void DelayData::setDryLevel(float dryLevel) {
    this->dryLevel = juce::jlimit(0.0f, 1.0f, dryLevel);
}

void DelayData::updateParameteres(int samples, float feedback, float wetLevel, float dryLevel)
{
    delayTime = juce::jlimit(0, delayBuffer.getNumSamples(), samples);
    this->feedback = juce::jlimit(0.0f, 1.0f, feedback);
    this->wetLevel = juce::jlimit(0.0f, 1.0f, wetLevel);
    this->dryLevel = juce::jlimit(0.0f, 1.0f, dryLevel);
}

void DelayData::process(juce::AudioBuffer<float>& buffer) {
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    for (int channel = 0; channel < numChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);
        auto* delayChannelData = delayBuffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample) {
            const float in = channelData[sample];
            const float delayed = delayChannelData[(writePos - delayTime + delayBuffer.getNumSamples()) % delayBuffer.getNumSamples()];
            const float out = (in * dryLevel) + (delayed * wetLevel * feedback);

            delayChannelData[writePos] = in + (delayed * feedback);

            channelData[sample] = out;
            ++writePos;
            if (writePos >= delayBuffer.getNumSamples())
                writePos = 0;
        }
    }
}

