/*
  ==============================================================================

    DelayUI.cpp
    Created: 12 Jun 2024 3:56:19pm
    Author:  Natha

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayUI.h"

//==============================================================================
DelayUI::DelayUI(BitcrushSamplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.



    //Time Slider
    timeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    timeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(timeSlider);

    timeLabel.setFont(10.0f);
    timeLabel.setText("Time", juce::NotificationType::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centredTop);
    timeLabel.attachToComponent(&timeSlider, false);

    //Mix Slider
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(mixSlider);

    mixLabel.setFont(10.0f);
    mixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centredTop);
    mixLabel.attachToComponent(&mixSlider, false);

    //Feedback Slider
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);

    addAndMakeVisible(feedbackSlider);

    feedbackLabel.setFont(10.0f);
    feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centredTop);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
}

DelayUI::~DelayUI()
{
}

void DelayUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
}

void DelayUI::resized()
{
    //ADSR Sliders
    const auto startX = 0;
    const auto startY = 30;
    const auto dialWidth = 75;
    const auto dialHeight = 75;

    timeSlider.setBounds(startX, startY, dialWidth, dialHeight);
    feedbackSlider.setBounds(startX + dialWidth, startY, dialWidth, dialHeight);
    mixSlider.setBounds(startX + (dialWidth * 2), startY, dialWidth, dialHeight);

}
