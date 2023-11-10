/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class CompressorAudioProcessor  : public foleys::MagicProcessor
                      /*      #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif*/
{
public:
    //==============================================================================
    CompressorAudioProcessor();
    ~CompressorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void updateCompressorParameters();

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
  struct CompressorParameters
        {
            float threshold = 0.5f;
            float attack = 0.95f;
            float release = 0.5f;
            float ratio = 0.9f;
        } compressorParameters;
    juce::dsp::Compressor<float> compressor;
    juce::AudioProcessorValueTreeState parameters;
    float getInputVolume() const { return inputVolume; }

            foleys::MagicProcessorState& getMagicState() { return magicState; }
private:
        float inputVolume = 0.0f;
   // void initialiseBuilder(foleys::MagicGUIBuilder& builder);
        foleys::MagicPlotSource* analyser = nullptr;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessor)
};
