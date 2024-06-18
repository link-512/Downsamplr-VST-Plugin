/*
  ==============================================================================

    ReverbUI.h
    Created: 13 Jun 2024 3:00:49pm
    Author:  Natha

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ReverbUI  : public juce::Component
{
public:
    ReverbUI(BitcrushSamplerAudioProcessor& p);
    ~ReverbUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider sizeSlider;    //Reverb Size
    juce::Label sizeLabel;

    juce::Slider dampingSlider;  //Reverb Damping
    juce::Label dampingLabel;

    juce::Slider drySlider;     //Reverb Dry Level
    juce::Label dryLabel;

    juce::Slider wetSlider;      //Reverb Wet Label
    juce::Label wetLabel;

    juce::Slider widthSlider;    //Reverb Width
    juce::Label widthLabel;

    juce::Slider feedbackSlider;    //Reverb Feedback
    juce::Label feedbackLabel;


    //Enable/Disable
    juce::TextButton preEnable{ "Pre Bitcrush" };
    juce::TextButton postEnable{ "Post Bitcrush" };

    void preReverbHit();
    void postReverbHit();


    //APVTS Attatchments
    //APVTS Attatchment
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeAttatchment;

    BitcrushSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbUI)
};
