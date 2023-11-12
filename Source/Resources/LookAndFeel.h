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
class LookAndFeel  : public juce::LookAndFeel_V4
{
public:
    LookAndFeel()
    {
        // Constructor
    }
    
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                         float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
     

          auto radius = width/2.0f-10.0f;
        // Draw the knob as a filled circle
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        auto outlineThickness = radius * 0.3f;
        // fill
        juce::ColourGradient grad(juce::Colours::lightcyan, 0.0f, 0.0f, juce::Colours::darkcyan, radius * 2.0f, radius * 2.0f, true);
        g.setGradientFill(grad);
        g.fillEllipse(rx, ry, radius * 2.0f, radius * 2.0f);
        // outline
                juce::ColourGradient gradient(juce::Colours::orchid, 0.0f, 0.0f, juce::Colours::darkorchid, radius * 2.0f, radius * 2.0f, true);
        g.setGradientFill(gradient);
        g.drawEllipse(rx, ry, radius * 2.0f, radius * 2.0f, outlineThickness);

        // Draw lines on the ellipse, splitting it into 6 parts
        g.setColour(juce::Colours::black);
        auto littleLineThickness = outlineThickness * 0.1f;
        auto nbSplit = 8;
        for (int i = 0; i <= nbSplit; ++i) {
          auto angle =  i * (rotaryEndAngle - rotaryStartAngle) / nbSplit + rotaryStartAngle - juce::MathConstants<float>::halfPi;
          auto x1 = centreX + (radius + outlineThickness/2.0f) * std::cos(angle);
          auto y1 = (centreY + (radius  + outlineThickness/2.0f) * std::sin(angle));
          auto x2 = centreX + (radius - outlineThickness/2.0f ) * std::cos(angle);
          auto y2 = (centreY + (radius - outlineThickness/2.0f) * std::sin(angle));
          g.drawLine(x1, y1, x2, y2, littleLineThickness);
        }
       
        juce::Path p;
        auto halfThickness = outlineThickness * 0.5f;
        p.addTriangle(0.0f ,
                       -(radius+0.5f*outlineThickness),
                      halfThickness,
                      -(radius-halfThickness),
                      -halfThickness,
                     -(radius-halfThickness));
                                       
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colours::black);
        g.fillPath(p);
         g.setColour(juce::Colours::white);
        g.setFont(10.0f);
        // Create the string with two decimal places and the unit "ms"
        juce::String sliderPosString = juce::String::formatted("%.2f ms", sliderPos);

        slider.setTextValueSuffix(" ms");
        // g.drawFittedText(sliderPosString, 0,-10, 100, 50, juce::Justification::centred, 1);

        // const char* imageData = BinaryData::lilwaynehead_png;
        // int imageSize = BinaryData::lilwaynehead_pngSize;
        // juce::Image myKnobImage = juce::ImageCache::getFromMemory(imageData, imageSize);
        
        // g.drawImage(myKnobImage, knobX-30, knobY-30, 50, 50, 0, 0, myKnobImage.getWidth(), myKnobImage.getHeight());
        
        
// void drawLabel (juce::Graphics& g, juce::Label& label) 
// {
//   // Call the base class implementation first
//   LookAndFeel::drawLabel (g, label);

//   // Customize the label's appearance
//   g.setColour (juce::Colours::white);
//   g.setFont (150.0f);

//   // Draw the label's text
//   g.drawFittedText (label.getText(), label.getLocalBounds(), juce::Justification::centred, 1);
// }
       
        
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeel)
};
