#include <JuceHeader.h>


class HorizontalLineSource : public foleys::MagicPlotSource
{
public:
    float yPosition = 0.0f;
    HorizontalLineSource() : yPosition(0.0f) {}
    ~HorizontalLineSource() override{} ;
    void prepareToPlay (double sampleRate, int samplesPerBlockExpected) override {}

    void pushSamples (const juce::AudioBuffer<float>& buffer) override {}

    void createPlotPaths (juce::Path& path, juce::Path& filledPath, juce::Rectangle<float> bounds, foleys::MagicPlotComponent&) override
    {
            
            // Set the background color of the plot component
            path.clear();
            path.startNewSubPath(bounds.getX(), bounds.getHeight() * (1.0f - yPosition));
            path.lineTo(bounds.getRight(), bounds.getHeight() * (1.0f - yPosition));
           float centerX = bounds.getCentreX();
    float centerY = bounds.getCentreY();
    float radius = bounds.getHeight() * 0.2f;
    juce::Colour circleColor = juce::Colours::black;
    juce::Path circlePath;
    circlePath.addEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);
    path.addPath(circlePath, juce::AffineTransform::identity);
    }


    void setYPosition(float newPosition)
    {
        yPosition = newPosition;
    }

    bool isActive() const { return active; }
    void setActive (bool shouldBeActive) { active = shouldBeActive; }

    juce::int64 getLastDataUpdate() const { return 0; }

    void resetLastDataFlag() { ; }
private:
bool active = true;

};