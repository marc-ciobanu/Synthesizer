/*
  ==============================================================================

    DelayData.h
    Created: 19 May 2024 10:32:06pm
    Author:  admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DelayData {
public:
    DelayData();
    ~DelayData();

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void reset();

    void setDelayTime(int samples);
    void setFeedback(float feedback);
    void setWetLevel(float wetLevel);
    void setDryLevel(float dryLevel);

    void updateParameteres(int samples, float feedback, float wetLevel, float dryLevel);

    void process(juce::AudioBuffer<float>& buffer);

private:
    juce::AudioBuffer<float> delayBuffer;
    int delayTime{ 44100 }; // Default delay time (1 second)
    float feedback{ 0.5f };
    float wetLevel{ 0.5f };
    float dryLevel{ 0.5f };
    int writePos{ 0 };
};

