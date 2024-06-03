/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitcrushSamplerAudioProcessorEditor::BitcrushSamplerAudioProcessorEditor (BitcrushSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), waveThumbnail (p), audioProcessor (p)
{
    //Manual Load Button
    manualLoad.onClick = [&]() {audioProcessor.loadFile(); };
    addAndMakeVisible(manualLoad);


    //Waveform Preview
    addAndMakeVisible(waveThumbnail);


    //Start Timer
    startTimerHz(30);

    setSize (1000, 500);
}

BitcrushSamplerAudioProcessorEditor::~BitcrushSamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void BitcrushSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void BitcrushSamplerAudioProcessorEditor::resized()
{
    manualLoad.setBounds(400, 0, 100, 100);
    waveThumbnail.setBounds(0,0, 400, 200);
}

//Repaints for playhead movement
void BitcrushSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}


