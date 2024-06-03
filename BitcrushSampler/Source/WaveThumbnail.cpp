/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 2 Jun 2024 2:58:58pm
    Author:  Natha

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(BitcrushSamplerAudioProcessor& p) : audioProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{
    //Draws Waveform
    auto waveform = audioProcessor.getWaveform();
    juce::Path p;

    if (waveform.getNumSamples() > 0)
    {

        mAudioPoints.clear();


        auto xRatio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);


        //Scales audio file to window on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample += xRatio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }

        g.setColour(juce::Colours::yellow);
        p.startNewSubPath(0, getHeight() / 2);

        //Scales on y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            p.lineTo(sample, juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0));
        }


        g.strokePath(p, juce::PathStrokeType(2));


        auto playHeadPosition = juce::jmap<int>(audioProcessor.getSampleCount(), 0, audioProcessor.getWaveform().getNumSamples(), 0, getWidth());

        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);

        g.setColour(juce::Colours::black.withAlpha(0.2f));
        g.fillRect(0, 0, playHeadPosition, getHeight());

    }

    else
    {
        g.setColour(juce::Colours::white);
        g.setFont(40.0f);
        g.drawFittedText("Load an Audio File", getLocalBounds(), juce::Justification::centred, 1);
    }


    g.setColour(juce::Colours::white);
    g.setFont(15.0f);

    auto textBounds = getLocalBounds().reduced(10, 10);

    g.drawFittedText(audioProcessor.getSampleName(), textBounds, juce::Justification::topRight, 1);
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

//Checks if file is able to be dragged and droped
bool WaveThumbnail::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }


    return false;
}

//Loads the new file
void WaveThumbnail::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            auto myFile = std::make_unique<juce::File>(file);
            //mFileName = myFile->getFileNameWithoutExtension();

            audioProcessor.loadFile(file);
        }
    }

    repaint();
}
