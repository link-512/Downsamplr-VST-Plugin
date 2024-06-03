/*
  ==============================================================================

    ADSRKnobs.cpp
    Created: 3 Jun 2024 12:59:56pm
    Author:  Natha

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRKnobs.h"

//==============================================================================
ADSRKnobs::ADSRKnobs(BitcrushSamplerAudioProcessor & p) : audioProcessor (p)
{
    //ADSR Sliders
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(attackSlider);

    attackLabel.setFont(10.0f);
    attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centredTop);
    attackLabel.attachToComponent(&attackSlider, false);
    

    //attackAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "ATTACK", attackSlider);



    decaySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    decaySlider.setRange(0.0f, 5.0f, 0.01f);
    addAndMakeVisible(decaySlider);

    decayLabel.setFont(10.0f);
    decayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centredTop);
    decayLabel.attachToComponent(&decaySlider, false);

    //decayAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DECAY", mDecaySlider);


    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    sustainSlider.setRange(0.0f, 1.0f, 0.01f);
    addAndMakeVisible(sustainSlider);

    sustainLabel.setFont(10.0f);
    sustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centredTop);
    sustainLabel.attachToComponent(&sustainSlider, false);


    //sustainAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SUSTAIN", sustainSlider);


    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    releaseSlider.setRange(0.0f, 5.0f, 0.01f);
    addAndMakeVisible(releaseSlider);

    releaseLabel.setFont(10.0f);
    releaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centredTop);
    releaseLabel.attachToComponent(&releaseSlider, false);


    //releaseAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "RELEASE", releaseSlider);

}

ADSRKnobs::~ADSRKnobs()
{
}

void ADSRKnobs::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::blueviolet);
}

void ADSRKnobs::resized()
{
    //ADSR Sliders
    const auto startX = 0;
    const auto startY = 30;
    const auto dialWidth = 75;
    const auto dialHeight = 75;

    attackSlider.setBounds(startX, startY, dialWidth, dialHeight);
    decaySlider.setBounds(startX + dialWidth, startY, dialWidth, dialHeight);
    sustainSlider.setBounds(startX + (dialWidth * 2), startY, dialWidth, dialHeight);
    releaseSlider.setBounds(startX + (dialWidth * 3), startY, dialWidth, dialHeight);

}
