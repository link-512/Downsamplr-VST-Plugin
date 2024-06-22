/*
  ==============================================================================

    BitcrushUI.h
    Created: 8 Jun 2024 3:19:21pm
    Author:  Natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class BitcrushUI  : public juce::Component
{
public:
    BitcrushUI(BitcrushSamplerAudioProcessor& p);
    ~BitcrushUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Bitcrush Sliders
    juce::Slider bitSlider;     //Bit Rate Slider
    juce::Label bitLabel;

    juce::Slider sampleSlider;  //Sample Reduction Slider
    juce::Label sampleLabel;

    juce::Slider wetDrySlider;  //Mix Slider
    juce::Label wetDryLabel;

    //APVTS Attatchment
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bitSliderAttatch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sampleSliderAttatch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetDrySliderAttatch;



    //Enable button
    juce::TextButton enableButton{ "Enable" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bitcrushEnableAttatch;

    void enableButtonHit();


    BitcrushSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrushUI)
};
