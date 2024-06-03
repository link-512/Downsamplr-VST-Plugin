/*
  ==============================================================================

    ADSRKnobs.h
    Created: 3 Jun 2024 12:59:56pm
    Author:  Natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSRKnobs  : public juce::Component
{
public:
    ADSRKnobs(BitcrushSamplerAudioProcessor& p);
    ~ADSRKnobs() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //ADSR Slider
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;


    //ADSR Slider Control
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttatchment;

    BitcrushSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRKnobs)
};
