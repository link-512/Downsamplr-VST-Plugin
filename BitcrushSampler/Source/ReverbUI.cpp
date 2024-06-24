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

    sizeAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SIZE", sizeSlider);

    //Damping Slider
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(dampingSlider);

    dampingLabel.setFont(10.0f);
    dampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    dampingLabel.setJustificationType(juce::Justification::centredTop);
    dampingLabel.attachToComponent(&dampingSlider, false);

    dampingAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DAMPING", dampingSlider);


    //Dry Level Slider
    drySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(drySlider);

    dryLabel.setFont(10.0f);
    dryLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::centredTop);
    dryLabel.attachToComponent(&drySlider, false);

    dryAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DRYLEVEL", drySlider);


    //Wet Level Slider
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(wetSlider);

    wetLabel.setFont(10.0f);
    wetLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::centredTop);
    wetLabel.attachToComponent(&wetSlider, false);

    wetAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "WETLEVEL", wetSlider);


    //Width Slider
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(widthSlider);

    widthLabel.setFont(10.0f);
    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredTop);
    widthLabel.attachToComponent(&widthSlider, false);

    widthAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "WIDTH", widthSlider);


    //Feedback Slider
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    //addAndMakeVisible(feedbackSlider);

    feedbackLabel.setFont(10.0f);
    feedbackLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centredTop);
    feedbackLabel.attachToComponent(&feedbackSlider, false);

    //feedbackAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "REVERBDECAY", feedbackSlider);



    //Buttons
    //reverbEnable Button
    reverbEnable.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    reverbEnableAttatch = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
        (audioProcessor.getAPVTS(), "REVERBENABLED", reverbEnable);
    reverbEnable.setClickingTogglesState(true);
    addAndMakeVisible(reverbEnable);

    //postEnableButton
    preReverbOn.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    preReverbOnAttatch = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
        (audioProcessor.getAPVTS(), "PREBITCRUSHREVERB", preReverbOn);
    preReverbOn.setClickingTogglesState(true);
    preReverbOn.onClick = [&]() {preReverbHit(); };
    addAndMakeVisible(preReverbOn);
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
    widthSlider.setBounds(startX + (dialWidth * 2), startY, dialWidth, dialHeight);


    //Second Layet
    drySlider.setBounds(startX, startY + dialHeight + 25, dialWidth, dialHeight);
    wetSlider.setBounds(startX + dialWidth, startY + dialHeight + 25, dialWidth, dialHeight);
    //widthSlider.setBounds(startX + (dialWidth * 2), startY + dialHeight + 25, dialWidth, dialHeight);


    //Buttons
    reverbEnable.setBounds(0, 260, getWidth(), 20);
    preReverbOn.setBounds(0, 280, getWidth(), 20);
}

void ReverbUI::preReverbHit()
{
    if (preReverbOn.getButtonText().equalsIgnoreCase("Post Bitcrush"))
    {
        preReverbOn.setButtonText("Pre Bitcrush");
    }

    else
    {
        preReverbOn.setButtonText("Post Bitcrush");
    }
}