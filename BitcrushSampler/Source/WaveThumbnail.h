/*
  ==============================================================================

    WaveThumbnail.h
    Created: 2 Jun 2024 2:58:58pm
    Author:  Natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    WaveThumbnail(BitcrushSamplerAudioProcessor& p);
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;



    //File Drag and Drop
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;


 

private:

    //Waveform generation
    std::vector<float> mAudioPoints;


    //Indicator Colour
    juce::Colour waveformColour;
    BitcrushSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
