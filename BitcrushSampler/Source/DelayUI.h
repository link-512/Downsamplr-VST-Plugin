/*
  ==============================================================================

    DelayUI.h
    Created: 12 Jun 2024 3:56:19pm
    Author:  Natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class DelayUI  : public juce::Component
{
public:
    DelayUI(BitcrushSamplerAudioProcessor& p);
    ~DelayUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Sliders for Delay
    juce::Slider timeSlider;
    juce::Slider mixSlider;
    juce::Slider feedbackSlider;

    //Labels
    juce::Label timeLabel;
    juce::Label mixLabel;
    juce::Label feedbackLabel;

    //APVTS Control
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttatchment;

    //Enable/Disable
    juce::TextButton preEnable{ "Pre Bitcrush" };
    juce::TextButton postEnable{ "Post Bitcrush" };


    BitcrushSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayUI)
};
