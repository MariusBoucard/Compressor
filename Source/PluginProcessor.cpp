/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LookAndFeel.h"

//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : foleys::MagicProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
     )
#endif
 ,parameters(*this, nullptr, juce::Identifier("Compressor"),
    {
 std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "inputVolume",  1 },"Input Volume",0.0f,100.0f,50.0),
       std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "threshold",  1 },"Threshold",-40.0f,0.0f,0.0f),
       std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "attack",  1 },"Attack",0.0f,100.0f,50.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "release",  1 },"Release",0.0f,100.0f,50.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ratio",  1 },"Ratio",0.0f,100.0f,50.0f)

    }) {
analyser = magicState.createAndAddObject<foleys::MagicAnalyser>("input");
analyserOutput = magicState.createAndAddObject<foleys::MagicAnalyser>("output");
//  auto thresholdLineSource = std::make_unique<ThresholdLineSource>(-20.0f); // Replace -20.0f with your actual threshold value
//     magicState.createAndAddObject<foleys::MagicPlotSource>("thresholdLine", std::move(thresholdLineSource));
// // Add a threshold line at -20 dBFS

magicState.createAndAddObject<foleys::MagicLevelSource>("inputVolume");

    FOLEYS_SET_SOURCE_PATH(__FILE__);
    FOLEYS_ENABLE_BINARY_DATA;

    compressorParameters.attack = 0.95f;
    compressorParameters.release = 0.5f;
    compressorParameters.ratio = 0.9f;
    compressorParameters.threshold = 0.5f;
    compressor.setAttack(0.95f);
    compressor.setRelease(0.5f);   
    compressor.setRatio(0.9f);
    compressor.setThreshold(0.5f);
    // Set the GUI file
    // Load the XML file
    juce::File file = juce::File::getCurrentWorkingDirectory().getChildFile("magic.xml");
    std::unique_ptr<juce::XmlElement> xml = juce::parseXML(file);

    // Convert the XML to a ValueTree

    // magicState.setGuiValueTree(*xml);
}

CompressorAudioProcessor::~CompressorAudioProcessor()
{
}
void CompressorAudioProcessor::initialiseBuilder(foleys::MagicGUIBuilder& builder)
{
   builder.registerJUCEFactories();
   builder.registerJUCELookAndFeels();

    // std::unique_ptr<juce::LookAndFeel> lookAndFeel = std::make_unique<juce::LookAndFeel>(LookAndFeel());

   builder.registerLookAndFeel("slide", std::make_unique<LookAndFeel>());
}

//==============================================================================
const juce::String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
          juce::dsp::ProcessSpec spec;

       spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32> (getTotalNumOutputChannels());
analyser->prepareToPlay (sampleRate, samplesPerBlock);
analyserOutput->prepareToPlay (sampleRate, samplesPerBlock);

    compressor.prepare(spec);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

 
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    //Getting Volume :
       float sum = 0.0f;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            sum += std::pow(buffer.getSample(channel, sample), 2);
        }
    }
    inputVolume = std::sqrt(sum / (buffer.getNumChannels() * buffer.getNumSamples()));
analyser->pushSamples (buffer);

    std::cout << "Hello, world!" << std::endl;

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    updateCompressorParameters();

    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    compressor.process(context);
   analyserOutput->pushSamples (buffer);

}

void CompressorAudioProcessor::updateCompressorParameters() {
    compressorParameters.threshold = *parameters.getRawParameterValue("threshold") ;
    compressorParameters.attack = *parameters.getRawParameterValue("attack")*0.01f;
    compressorParameters.release = *parameters.getRawParameterValue("release");
    compressorParameters.ratio = *parameters.getRawParameterValue("ratio") ;
    *parameters.getRawParameterValue("inputVolume") = compressorParameters.ratio;

    // Debug output
    std::cout << "Threshold: " << compressorParameters.threshold << std::endl;
    std::cout << "Attack: " << compressorParameters.attack << std::endl;
    std::cout << "Release: " << compressorParameters.release << std::endl;
    std::cout << "Ratio: " << compressorParameters.ratio << std::endl;
    compressor.setAttack(compressorParameters.attack);
    compressor.setRelease(compressorParameters.release);
    compressor.setRatio(compressorParameters.ratio);
       compressor.setThreshold(compressorParameters.threshold);
}

//SUPPR HASEDITORS

//

//juce::AudioProcessorEditor* CompressorAudioProcessor::createEditor()
//{
//   return new CompressorAudioProcessorEditor (*this);
//}

//==============================================================================
void CompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}
