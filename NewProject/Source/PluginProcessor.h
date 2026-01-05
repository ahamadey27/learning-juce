/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DelayAudioProcessor(); //Constructor as it has same name as class (loads into computer's memeory)
    ~DelayAudioProcessor() override; // '~' represents a deconstructor that removes plugin from computer memory

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override; //reserves free space in computer memory
    void releaseResources() override; //opposite of above funtion. Called when host stops playing audio 

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override; //Transports audio data to and from via a bus
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override; //Most used function! All DSP code goes here

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override; //these to save and store plugin paramater information so loads when DAW is opened and closed

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
};
