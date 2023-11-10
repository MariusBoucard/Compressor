#include <JuceHeader.h>

class InputVolumeDisplay : public juce::Component, public juce::Timer
{
public:
    InputVolumeDisplay(foleys::MagicProcessorState& magicState)
        : state(magicState)
    {
        addAndMakeVisible(volumeLabel);
        startTimerHz(30); // update 30 times per second
    }

    void timerCallback() override
    {
        auto inputVolume = state.getPropertyAsValue("inputVolume").getValue();
        volumeLabel.setText(inputVolume, juce::dontSendNotification);
    }

    void resized() override
    {
        volumeLabel.setBounds(getLocalBounds());
    }

private:
    foleys::MagicProcessorState& state;
    juce::Label volumeLabel;
};