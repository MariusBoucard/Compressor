/*
  ==============================================================================

    RotaryLookAndFeel.h
    Created: 26 Oct 2023 8:56:10pm
    Author:  Marius Boucard Bocciarelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LookAndFeel  : public juce::LookAndFeel_V3
{
public:
    LookAndFeel()
    {
        // Constructor
    }
    
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                         float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
     
        // Calculate the angle for the slider position within the full angle range
        float angle = 1.5f * juce::MathConstants<float>::pi + rotaryStartAngle + (rotaryEndAngle - rotaryStartAngle) * sliderPos;

        // Calculate the knob's position
        float centerX = x + width / 2;
        float centerY = y + height / 2;
        float knobX = centerX + (width / 2 - 10) * std::cos(angle);
        float knobY = centerY + (height / 2 - 10) * std::sin(angle);

        // Set the colors for the knob and background
        juce::Colour knobColor = juce::Colours::red;
        juce::Colour backgroundColor = juce::Colours::darkgrey;
        juce::Colour insideCircleColor = juce::Colours::black;

        
        // Draw the background
        g.setColour(backgroundColor);
        g.fillEllipse(x, y, width, height);
        
        g.setColour(insideCircleColor);
        g.fillRect(centerX-120, centerY, 250.0, 100.0);
        
        g.setColour(insideCircleColor);
        g.fillEllipse(x+10,y+10, width-20, height-20);
        
        
        // Draw the knob as a filled circle
        g.setColour(knobColor);
        g.fillEllipse(knobX - 10, knobY - 10, 20, 20);
         const char* imageGalaxyData = BinaryData::galaxy_png;
        int imageGalaxySize = BinaryData::galaxy_pngSize;
        juce::Image galaxyImage = juce::ImageCache::getFromMemory(imageGalaxyData, imageGalaxySize);
                g.drawImage(galaxyImage, x, y, width, height,0,0, galaxyImage.getWidth(), galaxyImage.getHeight());

        
        // const char* imageData = BinaryData::lilwaynehead_png;
        // int imageSize = BinaryData::lilwaynehead_pngSize;
        // juce::Image myKnobImage = juce::ImageCache::getFromMemory(imageData, imageSize);
        
        // g.drawImage(myKnobImage, knobX-30, knobY-30, 50, 50, 0, 0, myKnobImage.getWidth(), myKnobImage.getHeight());
        
       
       
        
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeel)
};
