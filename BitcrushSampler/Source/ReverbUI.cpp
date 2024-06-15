/*
  ==============================================================================

    ReverbUI.cpp
    Created: 13 Jun 2024 3:00:49pm
    Author:  Natha

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbUI.h"

//==============================================================================
ReverbUI::ReverbUI(BitcrushSamplerAudioProcessor& p) : audioProcessor(p)
{
    //Size Slider
    sizeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(sizeSlider);

    sizeLabel.setFont(10.0f);
    sizeLabel.setText("Size", juce::NotificationType::dontSendNotification);
    sizeLabel.setJustificationType(juce::Justification::centredTop);
    sizeLabel.attachToComponent(&sizeSlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);

    //Damping Slider
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(dampingSlider);

    dampingLabel.setFont(10.0f);
    dampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    dampingLabel.setJustificationType(juce::Justification::centredTop);
    dampingLabel.attachToComponent(&dampingSlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);


    //Dry Level Slider
    drySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(drySlider);

    dryLabel.setFont(10.0f);
    dryLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::centredTop);
    dryLabel.attachToComponent(&drySlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);


    //Wet Level Slider
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(wetSlider);

    wetLabel.setFont(10.0f);
    wetLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::centredTop);
    wetLabel.attachToComponent(&wetSlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);


    //Width Slider
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(widthSlider);

    widthLabel.setFont(10.0f);
    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredTop);
    widthLabel.attachToComponent(&widthSlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);


    //Feedback Slider
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(feedbackSlider);

    feedbackLabel.setFont(10.0f);
    feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centredTop);
    feedbackLabel.attachToComponent(&feedbackSlider, false);

    //timeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DELAYTIME", timeSlider);



    //Buttons
    addAndMakeVisible(preEnable);
    addAndMakeVisible(postEnable);
}

ReverbUI::~ReverbUI()
{
}

void ReverbUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkblue);
}

void ReverbUI::resized()
{
    //Bitcrush Sliders
    const auto startX = 0;
    const auto startY = 30;
    const auto dialWidth = 75;
    const auto dialHeight = 75;


    //First Layer
    sizeSlider.setBounds(startX, startY, dialWidth, dialHeight);
    dampingSlider.setBounds(startX + dialWidth, startY, dialWidth, dialHeight);
    feedbackSlider.setBounds(startX + (dialWidth * 2), startY, dialWidth, dialHeight);


    //Second Layet
    drySlider.setBounds(startX, startY + dialHeight + 25, dialWidth, dialHeight);
    wetSlider.setBounds(startX + dialWidth, startY + dialHeight + 25, dialWidth, dialHeight);
    widthSlider.setBounds(startX + (dialWidth * 2), startY + dialHeight + 25, dialWidth, dialHeight);


    //Buttons
    preEnable.setBounds(0, 260, getWidth(), 20);
    postEnable.setBounds(0, 280, getWidth(), 20);
}
