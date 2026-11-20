#include "PluginProcessor.h"
#include "PluginEditor.h"

RedTuneAudioProcessor::APVTS::ParameterLayout RedTuneAudioProcessor::createParameterLayout()
{
    APVTS::ParameterLayout layout;
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "retune", "Retune Speed", juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f), 35.0f));
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "humanize", "Humanize", juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f), 20.0f));
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "mix", "Mix", juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f), 100.0f));
    layout.add (std::make_unique<juce::AudioParameterChoice>(
        "key", "Key", juce::StringArray { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" }, 0));
    layout.add (std::make_unique<juce::AudioParameterChoice>(
        "scale", "Scale", juce::StringArray { "Major", "Minor", "Chromatic" }, 0));
    return layout;
}

RedTuneAudioProcessor::RedTuneAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput ("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

void RedTuneAudioProcessor::prepareToPlay (double, int) {}
void RedTuneAudioProcessor::releaseResources() {}

void RedTuneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    // Starter build: clean audio pass-through. Pitch correction will be implemented next.
    juce::ignoreUnused (buffer);
}

juce::AudioProcessorEditor* RedTuneAudioProcessor::createEditor()
{
    return new RedTuneAudioProcessorEditor (*this);
}

void RedTuneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void RedTuneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName (parameters.state.getType()))
        parameters.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RedTuneAudioProcessor();
}
