#include <JuceHeader.h>
#include "HorizontalLineSource.h"
class MyCompressorVisualizer : public juce::Component
{
public:
    MyCompressorVisualizer()
    {
        // Create your HorizontalLineSource
        horizontalLineSource = std::make_unique<HorizontalLineSource>();
        
        // Create a label for displaying text
        labelText = std::make_unique<juce::Label>("TextLabel", "Your Text Here");
        addAndMakeVisible(*labelText);
    }

    void resized() override
    {
        // Set the bounds of your components
        auto bounds = getLocalBounds();
        
        // horizontalLineSource->setBounds(bounds.removeFromTop(plotHeight));
        labelText->setBounds(bounds);
    }

private:
    std::unique_ptr<HorizontalLineSource> horizontalLineSource;
    std::unique_ptr<juce::Label> labelText;
    int plotHeight = 100; // Adjust the height of the plot as needed
};