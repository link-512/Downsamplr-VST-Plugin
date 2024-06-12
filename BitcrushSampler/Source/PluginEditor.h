/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"
#include "ADSRKnobs.h"
#include "BitcrushUI.h"
#include "DelayUI.h"

//==============================================================================
/**
*/
class BitcrushSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    BitcrushSamplerAudioProcessorEditor (BitcrushSamplerAudioProcessor&);
    ~BitcrushSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;



    //File Drag and Drop
    


    //Playhead
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BitcrushSamplerAudioProcessor& audioProcessor;
    WaveThumbnail waveThumbnail;
    ADSRKnobs adsrKnobs;
    BitcrushUI bitcrushUI;
    DelayUI delayUI;

    //File Loading
    juce::TextButton manualLoad{ "Load" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushSamplerAudioProcessorEditor)
};
