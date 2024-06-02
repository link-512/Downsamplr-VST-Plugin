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
class BitcrushSamplerAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BitcrushSamplerAudioProcessor();
    ~BitcrushSamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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
    void setStateInformation (const void* data, int sizeInBytes) override;




    //File Reading and Playback
    void loadFile();    //Manual Button File Loading

private:
    //==============================================================================


    //File Reading and Playback
    juce::Synthesiser sampleSynth;      //Synth for audio playback
    const int numVoices = { 5 };        //Number of voices within synth
    juce::AudioFormatManager formatManager;  //Format Manager for reading files
    juce::AudioFormatReader* formatReader{ nullptr };       //Format Reader for reading files
    juce::BigInteger range; //Midi Range



    //Audio Processor Value Tree State
    //juce::AudioProcessorValueTreeState APVTS;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushSamplerAudioProcessor)
};
