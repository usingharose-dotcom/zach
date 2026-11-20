cmake_minimum_required(VERSION 3.22)
project(RedTune VERSION 0.1.0)

# JUCE is fetched automatically when CMake configures this project.
include(FetchContent)
FetchContent_Declare(
  JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.6
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(RedTune
  COMPANY_NAME "RedTune Audio"
  PLUGIN_MANUFACTURER_CODE Rdtn
  PLUGIN_CODE Rdt1
  FORMATS VST3
  PRODUCT_NAME "RedTune"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(RedTune PRIVATE
  Source/PluginProcessor.cpp
  Source/PluginProcessor.h
  Source/PluginEditor.cpp
  Source/PluginEditor.h
)

target_compile_features(RedTune PRIVATE cxx_std_17)
target_link_libraries(RedTune PRIVATE
  juce::juce_audio_utils
  juce::juce_dsp
  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)
