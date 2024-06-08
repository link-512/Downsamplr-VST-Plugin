/*
  ==============================================================================

    BitcrushUI.cpp
    Created: 8 Jun 2024 3:19:21pm
    Author:  Natha

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BitcrushUI.h"

//==============================================================================
BitcrushUI::BitcrushUI(BitcrushSamplerAudioProcessor& p) : audioProcessor (p)
{
    //Bit Rate Slider
    bitSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    bitSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    bitSlider.setRange(1.0f, 31.99f, 0.01f);
    addAndMakeVisible(bitSlider);
    //bitSliderAttatch = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "BIT", bitSlider);

    bitLabel.setFont(10.0);
    bitLabel.setText("Bit Rate", juce::NotificationType::dontSendNotification);
    bitLabel.setJustificationType(juce::Justification::centredTop);
    bitLabel.attachToComponent(&bitSlider, false);
    


    //Sample Reduction Slider
    sampleSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sampleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    sampleSlider.setRange(1.0f, 50.0f, 1);
    addAndMakeVisible(sampleSlider);
    //sampleSliderAttatch = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SAMPLE", sampleSlider);

    sampleLabel.setFont(10.0f);
    sampleLabel.setText("Sample Reduction", juce::NotificationType::dontSendNotification);
    sampleLabel.setJustificationType(juce::Justification::centredTop);
    sampleLabel.attachToComponent(&sampleSlider, false);
    

    //Wet Dry Mix Slider
    wetDrySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    wetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    wetDrySlider.setRange(0.0f, 1.0f, 0.001f);
    addAndMakeVisible(wetDrySlider);
    //wetDrySliderAttatch = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "PRESENCE", wetDrySlider);

    wetDryLabel.setFont(10.0f);
    wetDryLabel.setText("Presence", juce::NotificationType::dontSendNotification);
    wetDryLabel.setJustificationType(juce::Justification::centredTop);
    wetDryLabel.attachToComponent(&wetDrySlider, false);
    
}

BitcrushUI::~BitcrushUI()
{
}

void BitcrushUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::red);
}

void BitcrushUI::resized()
{
    //Bitcrush Sliders
    const auto startX = 0;
    const auto startY = 30;
    const auto dialWidth = 75;
    const auto dialHeight = 75;

    bitSlider.setBounds(startX, startY, dialWidth, dialHeight);
    sampleSlider.setBounds(startX + dialWidth, startY, dialWidth, dialHeight);
    wetDrySlider.setBounds(startX + (dialWidth * 2), startY, dialWidth, dialHeight);

}
