/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitcrushSamplerAudioProcessor::BitcrushSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), APVTS(*this, nullptr, "PARAMETERS", createParameters())       //Creates APVTS
#endif
{
    formatManager.registerBasicFormats();       //Registers Basic Audio Formats
    APVTS.state.addListener(this);             //APVTS Listener
    
    for (int i = 0; i < numVoices; i++)         //Adds Voices to sampleSynth
    {
        sampleSynth.addVoice(new juce::SamplerVoice);
    }

    range.setRange(0, 128, true);       //Sets Midi Range
}

BitcrushSamplerAudioProcessor::~BitcrushSamplerAudioProcessor()
{
}

//==============================================================================
const juce::String BitcrushSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitcrushSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BitcrushSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BitcrushSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BitcrushSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BitcrushSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BitcrushSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BitcrushSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BitcrushSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void BitcrushSamplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BitcrushSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    sampleSynth.setCurrentPlaybackSampleRate(sampleRate);     //Sets sample rate for sampler
    updateADSR();

    //Bitcrush
    bits = APVTS.getRawParameterValue("BIT")->load();
    reductionFactor = APVTS.getRawParameterValue("SAMPLE")->load();
    wetDryFactor = APVTS.getRawParameterValue("PRESENCE")->load();

    //Delay
    delayTime = APVTS.getRawParameterValue("DELAYTIME")->load();
    delayMix = APVTS.getRawParameterValue("DELAYMIX")->load();
    feedbackGain = APVTS.getRawParameterValue("FEEDBACK")->load();

    //Delay Buffer Setup
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = 2 * sampleRate + samplesPerBlock;

    delayBuffer.setSize(2, delayBufferSize);
    delayBuffer.clear();

    mSampleRate = sampleRate;


    //Reverb Initialization
    reverb.setSampleRate(sampleRate);
    //Set Reverb Params Here
}

void BitcrushSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BitcrushSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BitcrushSamplerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //Updates ADSR when necessary
    if (shouldUpdate)
    {
        updateADSR();

        //Bitcrush
        bits = APVTS.getRawParameterValue("BIT")->load();
        reductionFactor = APVTS.getRawParameterValue("SAMPLE")->load();
        wetDryFactor = APVTS.getRawParameterValue("PRESENCE")->load();
        shouldUpdate = false;

        //Delay
        delayTime = APVTS.getRawParameterValue("DELAYTIME")->load();
        //delayMix = APVTS.getRawParameterValue("DELAYMIX")->load();
        feedbackGain = APVTS.getRawParameterValue("FEEDBACK")->load();
    }


    // PlayHead
    juce::MidiMessage m;
    juce::MidiBuffer::Iterator it{ midiMessages };
    int sample;

    while (it.getNextEvent(m, sample))
    {
        if (m.isNoteOn())
        {
            mIsNotePlayed = true;
        }

        else if (m.isNoteOff())
        {
            mIsNotePlayed = false;
        }
    }

    mSampleCount = mIsNotePlayed ? mSampleCount += buffer.getNumSamples() : 0;


    sampleSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());       //Renders data with sampleSynth
    

    //Delay Processing
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = delayBuffer.getNumSamples();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {


        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = delayBuffer.getReadPointer(channel);
        float* dryBuffer = buffer.getWritePointer(channel);


        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        feedbackDelay(channel, bufferLength, delayBufferLength, dryBuffer);

    }

    writePosition += bufferLength;
    writePosition %= delayBufferLength;

    //Bitcrush Processing
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        //Bit Reduction
        totalPossibleLevels = 1 << bits;          //Finds total possible bit combinations given bit rate
        bitQuantization = 1.0f / static_cast<float>(totalPossibleLevels);    //Finds space between possible bit levels

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            //Collects Dry Signal
            dryData = channelData[i];
            


            

            wetData = std::floor(channelData[i] / bitQuantization) * bitQuantization;      //Divides channel data among bit levels and quantizes to them
            



            //Sample Reduction
            if (reductionFactor != 1)
            {
                if (i % reductionFactor != 0)
                {
                    wetData = channelData[i - (i % reductionFactor)];
                }
            }

            channelData[i] = (1.0f - wetDryFactor) * dryData + wetDryFactor * wetData;     //Mixes Wet and dry signals together
            //NOTE: This is not a simple wet dry mix as the sample rate reduction is acting on the mixed past data rather than the wet past data
        }
    }
    
    //Reverb
    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
    

    
}

//==============================================================================
bool BitcrushSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BitcrushSamplerAudioProcessor::createEditor()
{
    return new BitcrushSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void BitcrushSamplerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BitcrushSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitcrushSamplerAudioProcessor();
}

//Loads A file when prompted by button
void BitcrushSamplerAudioProcessor::loadFile()
{
    sampleSynth.clearSounds();      //Clears all previous sounds

    juce::FileChooser chooser{ "Select File" };

    if (chooser.browseForFileToOpen())      //Opens File Explorer for file
    {
        auto file = chooser.getResult();
        fileName = file.getFileNameWithoutExtension();

        formatReader = formatManager.createReaderFor(file);

        //Creates buffer for waveform data
        waveform.clear();
        waveform.setSize(1, static_cast<int>(formatReader->lengthInSamples));
        formatReader->read(&waveform, 0, static_cast<int>(formatReader->lengthInSamples), 0, true, false);

        sampleSynth.addSound(new juce::SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10.0));
        
    }
    
}

//Loads a file when a new file is dragged
void BitcrushSamplerAudioProcessor::loadFile(const juce::String& path)
{
    sampleSynth.clearSounds();

    auto file = juce::File(path);
    fileName = file.getFileNameWithoutExtension();

    formatReader = formatManager.createReaderFor(file);


    //Creates buffer for waveform data
    waveform.clear();
    waveform.setSize(1, static_cast<int>(formatReader->lengthInSamples));
    formatReader->read(&waveform, 0, static_cast<int>(formatReader->lengthInSamples), 0, true, false);

    sampleSynth.addSound(new juce::SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10.0));

    //updateADSR();
}

void BitcrushSamplerAudioProcessor::updateADSR()       //Updates ADSR Values
{
    ADSRParams.attack = APVTS.getRawParameterValue("ATTACK")->load();
    ADSRParams.decay = APVTS.getRawParameterValue("DECAY")->load();
    ADSRParams.sustain = APVTS.getRawParameterValue("SUSTAIN")->load();
    ADSRParams.release = APVTS.getRawParameterValue("RELEASE")->load();

    //Iterates for ADSR Envelope
    for (int i = 0; i < sampleSynth.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(sampleSynth.getSound(i).get()))
        {
            sound->setEnvelopeParameters(ADSRParams);
        }
    }
}


//Updates ADSR when knob value is changed
void BitcrushSamplerAudioProcessor::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{
    shouldUpdate = true;
}

//Creates ADSR Parameters
juce::AudioProcessorValueTreeState::ParameterLayout BitcrushSamplerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.01f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.0f, 3.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 0.01f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("BIT", "Bit Rate", 1.0f, 31.999f, 31.999f));
    parameters.push_back(std::make_unique<juce::AudioParameterInt>("SAMPLE", "Sample Reduction", 1, 50, 1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("PRESENCE", "Presence", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DELAYTIME", "Delay Time", 1, 1000, 200));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DELAYMIX", "Delay Mix", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", 0.0f, 1.0f, 0.5f));

    return { parameters.begin(), parameters.end() };
}


//Copys the base data to the delay buffer
void BitcrushSamplerAudioProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    

    //Copy from main to delay
    if (delayBufferLength > bufferLength + writePosition)
    {
        delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, bufferLength, delayMix, delayMix);
    }

    else
    {
        const int bufferRemaining = delayBufferLength - writePosition;

        delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, bufferRemaining, delayMix, delayMix);
        delayBuffer.copyFromWithRamp(channel, 0, bufferData + bufferRemaining, bufferLength - bufferRemaining, delayMix, delayMix);
    }
}

//Sends the delayed buffer back to the normal buffer for output
void BitcrushSamplerAudioProcessor::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel,
    const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{

    const int readPosition = static_cast<int>(delayBufferLength + writePosition - (mSampleRate * delayTime / 1000)) % delayBufferLength;

    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    }

    else
    {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
}

//Sends the main buffer back to the delay to generate feedback
void BitcrushSamplerAudioProcessor::feedbackDelay(int channel,
    const int bufferLength, const int delayBufferLength, const float* dryBuffer)
{

    if (delayBufferLength > bufferLength + writePosition)
    {
        delayBuffer.addFromWithRamp(channel, writePosition, dryBuffer, bufferLength, feedbackGain, feedbackGain);
    }

    else
    {
        const int bufferRemaining = delayBufferLength - writePosition;
        delayBuffer.addFromWithRamp(channel, writePosition, dryBuffer, bufferRemaining, feedbackGain, feedbackGain);
        delayBuffer.addFromWithRamp(channel, 0, dryBuffer + bufferRemaining, bufferLength - bufferRemaining, feedbackGain, feedbackGain);
    }
}
