/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BiasAudioProcessor::BiasAudioProcessor()
{
}

BiasAudioProcessor::~BiasAudioProcessor()
{
}

//==============================================================================
const String BiasAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int BiasAudioProcessor::getNumParameters()
{
    return bias.getNumParameters();
}

float BiasAudioProcessor::getParameter (int index)
{
    return bias.getParameterValue(index);
}

void BiasAudioProcessor::setParameter (int index, float newValue)
{
    bias.setParameterValue(index, newValue);
}

const String BiasAudioProcessor::getParameterName (int index)
{
    return bias.getParameterName(index);
}

const String BiasAudioProcessor::getParameterText (int index)
{
    return bias.getParameterName(index);
}

const String BiasAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String BiasAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool BiasAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool BiasAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool BiasAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BiasAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BiasAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

double BiasAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BiasAudioProcessor::getNumPrograms()
{
    return 0;
}

int BiasAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BiasAudioProcessor::setCurrentProgram (int index)
{
}

const String BiasAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void BiasAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BiasAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    bias.prepareToPlay(sampleRate, samplesPerBlock);
}

void BiasAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void BiasAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    bias.processBlock(buffer, getNumInputChannels(), getNumOutputChannels(), midiMessages);

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

void BiasAudioProcessor::reset()
{
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    bias.reset();
}

//==============================================================================
bool BiasAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BiasAudioProcessor::createEditor()
{
    return NULL;
}

//==============================================================================
void BiasAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    copyXmlToBinary(bias.getStateInformation(), destData);
}

void BiasAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
    {
        bias.setStateInformation(xmlState);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BiasAudioProcessor();
}
