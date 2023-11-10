/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    auto inputVolumeSlider = std::make_unique<juce::Slider>();

    // Configure the Slider
    inputVolumeSlider->setRange(0.0, 1.0);
    inputVolumeSlider->setValue(audioProcessor.getMagicState().getPropertyAsValue("inputVolume").getValue());

    // Add the Slider to the editor
    addAndMakeVisible(inputVolumeSlider.get());

    // Transfer ownership of the Slider to the editor
    inputVolumeSlider.release();

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void CompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
