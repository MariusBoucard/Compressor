#include <JuceHeader.h>


class HorizontalLineSource : public foleys::MagicAnalyser
{
public:
    float yPosition = 0.0f;
    HorizontalLineSource() : yPosition(0.0f) {}
    ~HorizontalLineSource() override{} ;
    // TODO MAKE WAY TO MUCH CALCULATION
    // void prepareToPlay (double sampleRate, int samplesPerBlockExpected) override{} ;

    // void pushSamples (const juce::AudioBuffer<float>& buffer)   override{} ;

    float calcHeight(juce::Rectangle<float> bounds){
        auto lineHeight = bounds.getHeight()*yPosition;
        return lineHeight;
        
    }
    void createPlotPaths (juce::Path& path, juce::Path& filledPath, juce::Rectangle<float> bounds, foleys::MagicPlotComponent&) override
    {
        path.clear();

        path.startNewSubPath(bounds.getX(), (calcHeight(bounds)));
        path.lineTo(bounds.getRight(), (calcHeight(bounds)));
    //     filledPath = path;
    //       filledPath.lineTo (bounds.getBottomRight());
    // filledPath.lineTo (bounds.getBottomLeft());
    filledPath.closeSubPath();

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