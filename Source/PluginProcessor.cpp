/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"


//==============================================================================
Synth1AudioProcessor::Synth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

Synth1AudioProcessor::~Synth1AudioProcessor(){}

const juce::String Synth1AudioProcessor::getName() const{ return JucePlugin_Name; }

bool Synth1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth1AudioProcessor::getTailLengthSeconds() const{ return 0.0; }
int Synth1AudioProcessor::getNumPrograms() { return 1; }
int Synth1AudioProcessor::getCurrentProgram() { return 0; }
void Synth1AudioProcessor::setCurrentProgram (int index){}
const juce::String Synth1AudioProcessor::getProgramName (int index){ return {}; }
void Synth1AudioProcessor::changeProgramName(int index, const juce::String& newName) {}

//==============================================================================

void Synth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void Synth1AudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================

void Synth1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) 
        {
            auto& oscWaveType = *apvts.getRawParameterValue("OSC");

            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& resonance = *apvts.getRawParameterValue("FILTERRES");

            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");       

            auto& reverbRoomSize = *apvts.getRawParameterValue("REVERBROOMSIZE");
            auto& reverbDamping = *apvts.getRawParameterValue("REVERBDAMPING");
            auto& reverbWetLevel = *apvts.getRawParameterValue("REVERBWETLEVEL");
            auto& reverbDryLevel = *apvts.getRawParameterValue("REVERBDRYLEVEL");
            auto& reverbWidth = *apvts.getRawParameterValue("REVERBWIDTH");

            auto& chorusRate = *apvts.getRawParameterValue("CHORUSRATE");
            auto& chorusDepth = *apvts.getRawParameterValue("CHORUSDEPTH");
            auto& chorusCentreDelay = *apvts.getRawParameterValue("CHORUSCENTREDELAY");
            auto& chorusFeedback = *apvts.getRawParameterValue("CHORUSFEEDBACK");
            auto& chorusMix = *apvts.getRawParameterValue("CHORUSMIX");

            voice->getOscillator().setWaveType(oscWaveType);
            voice->getOscillator().setFmParams(fmDepth, fmFreq);

            // aici avem valori Atomic, nu floaturi normale. atomic e mai heavy
            voice->updateAdsr(attack, decay, sustain, release);
            
            voice->updateFilter(filterType, cutoff, resonance);

            voice->updateModAdsr(modAttack, modDecay, modSustain, modRelease);

            voice->updateReverb(reverbRoomSize, reverbDamping, reverbWetLevel, reverbDryLevel, reverbWidth);

            voice->updateChorus(chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix);
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

bool Synth1AudioProcessor::hasEditor() const{ return true; }
juce::AudioProcessorEditor* Synth1AudioProcessor::createEditor(){ return new Synth1AudioProcessorEditor(*this); }
void Synth1AudioProcessor::getStateInformation (juce::MemoryBlock& destData){}
void Synth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes){}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){ return new Synth1AudioProcessor(); }

//==============================================================================

juce::AudioProcessorValueTreeState::ParameterLayout Synth1AudioProcessor::createParams() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Main oscillator type
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // FM Frequency
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Frequency", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01, 0.3f}, 0.0f));

    // FM Depth
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH", "FM Depth", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));

    // Osc ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{ 0.1f, 3.0f, 0.01f }, 0.4f));

    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Mod Attack", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Mod Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Mod Sustain", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Mod Release", juce::NormalisableRange<float>{ 0.1f, 3.0f, 0.01f }, 0.4f));

    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float>{ 20.0f, 20000.0f, 0.01f, 0.6f }, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float>{ 1.0f, 10.0f, 0.01f}, 1.0f));

    // Reverb
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBROOMSIZE", "Reverb Room Size", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDAMPING", "Reverb Damping", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWETLEVEL", "Reverb Wet Level", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.9f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDRYLEVEL", "Reverb Dry Level", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWIDTH", "Reverb Width", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.1f));

    // Chorus
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSRATE", "Chorus Rate", juce::NormalisableRange<float>{ 0.0f, 99.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSDEPTH", "Chorus Depth", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSCENTREDELAY", "Chorus Centre Delay", juce::NormalisableRange<float>{ 0.0f, 100.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSFEEDBACK", "Chorus Feedback", juce::NormalisableRange<float>{ -1.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSMIX", "Chorus Mix", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.1f));

    // Eq
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOWCUTFREQ", "LowCut Freq", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 20.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGHCUTFREQ", "HighCut Freq", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 20000.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAKFREQ", "Peak Freq", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f), 750.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAKGAIN", "Peak Gain", juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAKQUALITY", "Peak Quality", juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f));

    juce::StringArray stringArray;
    for (int i = 0; i < 4; ++i)
    {
        juce::String str;
        str << (12 + i * 12);
        str << " db/Oct";
        stringArray.add(str);
    }

    params.push_back(std::make_unique<juce::AudioParameterChoice>("LOWCUTSLOPE", "LowCut Slope", stringArray, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("HIGHCUTSLOPE", "HighCut Slope", stringArray, 0));

    return{ params.begin(), params.end() };
}