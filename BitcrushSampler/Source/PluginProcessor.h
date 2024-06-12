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
class BitcrushSamplerAudioProcessor  : public juce::AudioProcessor, public juce::ValueTree::Listener
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
    void loadFile(const juce::String& path);    //Drag and Drop File Loading
    juce::String getSampleName() { return fileName; };  //Returns Name of File Sampled


    //Waveform Generation
    int getNumSamplerSounds() { return sampleSynth.getNumSounds(); };
    juce::AudioBuffer<float>& getWaveform() { return waveform; };


    // Playhead
    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; };
    std::atomic<int>& getSampleCount() { return mSampleCount; };


    //ADSR Variables
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    juce::ADSR::Parameters& getADSRParams() { return ADSRParams; };

    void updateADSR();

    juce::AudioProcessorValueTreeState& getAPVTS() { return APVTS; };



    //Delay Functions
    void fillDelayBuffer(int channel, const int bufferLength, 
        const int delayBufferLength, const float* bufferData, const float* delayBufferData);

    void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, 
        const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);

    void feedbackDelay(int channel,
        const int bufferLength, const int delayBufferLength, const float* dryBuffer);

private:
    //==============================================================================


    //File Reading and Playback
    juce::Synthesiser sampleSynth;      //Synth for audio playback
    const int numVoices = { 5 };        //Number of voices within synth
    juce::AudioFormatManager formatManager;  //Format Manager for reading files
    juce::AudioFormatReader* formatReader{ nullptr };       //Format Reader for reading files
    juce::BigInteger range; //Midi Range
    juce::String fileName{ "" };  //Name of file being played



    //Waveform generation
    juce::AudioBuffer<float> waveform;

    //Playhead
    std::atomic<bool> shouldUpdate{ false };
    std::atomic<bool> mIsNotePlayed{ false };
    std::atomic<int> mSampleCount{ 0 };

    //Audio Processor Value Tree State
    juce::AudioProcessorValueTreeState APVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    //ADSR
    juce::ADSR::Parameters ADSRParams;     //Sampler Envelope Parameters

    
    //Bit Reduction
    int bits;       //Simulated Bit Level
    int totalPossibleLevels;        //Total Possible values where a sample can be playing at a moment
    float bitQuantization;          //Value used to quantize incoming sample rate into simulated bit level

    //Sample Rate Reduction
    int reductionFactor;        //Reduction factor of how much sample rate is reduced


    //Wet Dry Mix
    float wetData;                  //Contains the value for the bitcrushed channelData at a given time
    float dryData;                  //Dry channelData at a time
    float wetDryFactor = 1.0f;     //Mix Balance



    //Synth Rendering
    juce::AudioSampleBuffer synthBuffer;


    //Delay Variables
    juce::AudioBuffer<float> delayBuffer;      //Buffer that contains the delay data

    int writePosition{ 0 };
    int mSampleRate{ 44100 };

    int delayTime;      //Time in between each loop of the delay
    float delayMix;      //Gain of the delayed portion of the mix
    float feedbackGain; //Amount of feedback

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushSamplerAudioProcessor)
};
