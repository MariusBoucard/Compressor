/*
  ==============================================================================

    RotaryLookAndFeel.h
    Created: 26 Oct 2023 8:56:10pm
    Author:  Marius Boucard Bocciarelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//===============================================P===============================
/*
*/
class RootLookAndFeel  : public juce::LookAndFeel_V3
{
public:
  RootLookAndFeel()
  {
        const char* imageData = BinaryData::space_jpg;
    int imageSize = BinaryData::space_jpgSize;
    juce::Image myBackgroundImage = juce::ImageCache::getFromMemory(imageData, imageSize);
    
    setColour(juce::Slider::backgroundColourId, juce::Colour::fromRGB(0, 0, 0));
    // Set the background color of the root element to black
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RootLookAndFeel)
};
