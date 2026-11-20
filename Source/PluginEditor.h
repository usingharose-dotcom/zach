#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class RedTuneAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit RedTuneAudioProcessorEditor (RedTuneAudioProcessor&);
    ~RedTuneAudioProcessorEditor() override = default;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RedTuneAudioProcessor& audioProcessor;
    juce::Slider retuneSlider, humanizeSlider, mixSlider;
    juce::ComboBox keyBox, scaleBox;
    juce::Label titleLabel, retuneLabel, humanizeLabel, mixLabel, keyLabel, scaleLabel;

    using SliderAttachment = RedTuneAudioProcessor::APVTS::SliderAttachment;
    using ComboAttachment = RedTuneAudioProcessor::APVTS::ComboBoxAttachment;
    std::unique_ptr<SliderAttachment> retuneAttachment, humanizeAttachment, mixAttachment;
    std::unique_ptr<ComboAttachment> keyAttachment, scaleAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedTuneAudioProcessorEditor)
};
