#include "PluginEditor.h"

RedTuneAudioProcessorEditor::RedTuneAudioProcessorEditor (RedTuneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (620, 390);

    titleLabel.setText ("REDTUNE", juce::dontSendNotification);
    titleLabel.setFont (juce::Font (32.0f, juce::Font::bold));
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    titleLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (titleLabel);

    auto setupSlider = [this] (juce::Slider& s, juce::Label& l, const juce::String& name)
    {
        s.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 72, 22);
        s.setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffff2638));
        s.setColour (juce::Slider::thumbColourId, juce::Colours::white);
        s.setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
        s.setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0xff63202a));
        l.setText (name, juce::dontSendNotification);
        l.setColour (juce::Label::textColourId, juce::Colours::white);
        l.setJustificationType (juce::Justification::centred);
        addAndMakeVisible (s);
        addAndMakeVisible (l);
    };

    setupSlider (retuneSlider, retuneLabel, "RETUNE SPEED");
    setupSlider (humanizeSlider, humanizeLabel, "HUMANIZE");
    setupSlider (mixSlider, mixLabel, "MIX");

    keyBox.addItemList ({ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" }, 1);
    scaleBox.addItemList ({ "Major", "Minor", "Chromatic" }, 1);
    for (auto* box : { &keyBox, &scaleBox })
    {
        box->setColour (juce::ComboBox::backgroundColourId, juce::Colour (0xff191014));
        box->setColour (juce::ComboBox::textColourId, juce::Colours::white);
        box->setColour (juce::ComboBox::outlineColourId, juce::Colour (0xffff2638));
        addAndMakeVisible (*box);
    }

    keyLabel.setText ("KEY", juce::dontSendNotification);
    scaleLabel.setText ("SCALE", juce::dontSendNotification);
    for (auto* label : { &keyLabel, &scaleLabel })
    {
        label->setColour (juce::Label::textColourId, juce::Colours::white);
        label->setJustificationType (juce::Justification::centred);
        addAndMakeVisible (*label);
    }

    retuneAttachment = std::make_unique<SliderAttachment> (audioProcessor.parameters, "retune", retuneSlider);
    humanizeAttachment = std::make_unique<SliderAttachment> (audioProcessor.parameters, "humanize", humanizeSlider);
    mixAttachment = std::make_unique<SliderAttachment> (audioProcessor.parameters, "mix", mixSlider);
    keyAttachment = std::make_unique<ComboAttachment> (audioProcessor.parameters, "key", keyBox);
    scaleAttachment = std::make_unique<ComboAttachment> (audioProcessor.parameters, "scale", scaleBox);
}

void RedTuneAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff090609));
    g.setColour (juce::Colour (0xff240b12));
    g.fillRoundedRectangle (18.0f, 18.0f, 584.0f, 354.0f, 18.0f);
    g.setColour (juce::Colour (0xffff2638));
    g.drawRoundedRectangle (18.0f, 18.0f, 584.0f, 354.0f, 18.0f, 2.0f);
    g.setColour (juce::Colour (0xff7d1022));
    g.fillRect (40, 75, 540, 2);
}

void RedTuneAudioProcessorEditor::resized()
{
    titleLabel.setBounds (35, 28, 550, 45);
    retuneSlider.setBounds (55, 105, 150, 150);
    humanizeSlider.setBounds (235, 105, 150, 150);
    mixSlider.setBounds (415, 105, 150, 150);
    retuneLabel.setBounds (55, 255, 150, 25);
    humanizeLabel.setBounds (235, 255, 150, 25);
    mixLabel.setBounds (415, 255, 150, 25);
    keyLabel.setBounds (145, 305, 90, 20);
    scaleLabel.setBounds (385, 305, 90, 20);
    keyBox.setBounds (145, 327, 90, 26);
    scaleBox.setBounds (325, 327, 150, 26);
}
