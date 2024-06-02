/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitcrushSamplerAudioProcessorEditor::BitcrushSamplerAudioProcessorEditor (BitcrushSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Manual Load Button
    manualLoad.onClick = [&]() {audioProcessor.loadFile(); };
    addAndMakeVisible(manualLoad);


    setSize (1000, 500);
}

BitcrushSamplerAudioProcessorEditor::~BitcrushSamplerAudioProcessorEditor()
{
}

//==============================================================================
void BitcrushSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void BitcrushSamplerAudioProcessorEditor::resized()
{
    manualLoad.setBounds(0, 0, 100, 100);
}
