/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 02110-1301, USA.
 */

/**
 * Bias.cpp
 * Bias
 *
 * Martin Dittus 2013-10-26
 * @dekstop
 */

#include "Bias.h"

/**
 * Processing.
 */

void Bias::prepareToPlay(double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
}

void Bias::processBlock(AudioSampleBuffer& buffer, int numInputChannels,
                                 int numOutputChannels, MidiBuffer& midiMessages){
    // Atm we're assuming matching input/output channel counts
    jassert(numInputChannels==numOutputChannels);
    
    float bias = getBias(getParameterValue(PARAMETER_BIAS));
    float dryWetMix = getParameterValue(PARAMETER_DRYWET);
    
    for (int channel=0; channel<numInputChannels; channel++)
    {
        float *buf = buffer.getSampleData(channel);
        for (int i=0; i<buffer.getNumSamples(); i++) {
            float v =
                powf(fabs(buf[i]), bias) *  // bias
                (buf[i] < 0 ? -1 : 1);      // sign
            buf[i] =
                v * dryWetMix +
                buf[i] * (1 - dryWetMix);
        }
    }
}

void Bias::reset() { }

// Mapping p1 parameter ranges so that:
// - full-left (0) is "low bias"
// - centre (0.5) is "no bias"
// - full-right (1.0) is "high bias"
float Bias::getBias(float p1){
    p1 = 1 - p1;
    if (p1 < 0.5)
    { // min .. med
        p1 = p1 * 2; // [0..1] range
        return p1*p1 * (MED_BIAS-MIN_BIAS) + MIN_BIAS;
    } else
    { // med .. max
        p1 = (p1 - 0.5) * 2; // [0..1] range
        return p1*p1 * (MAX_BIAS-MED_BIAS) + MED_BIAS;
    }
}


/**
 * Parameters.
 */

const String Bias::getParameterName(int index){
    if (index >= 0 && index < getNumParameters())
        return parameterNames[index];
    return String::empty;
}

float Bias::getParameterValue(int index){
    if (index >= 0 && index < getNumParameters())
        return parameterValues[index];
    return 0.0f;
}

void Bias::setParameterValue(int index, float value){
    if (index >= 0 && index < getNumParameters())
        parameterValues[index] = value;
}


/**
 * State
 */

XmlElement Bias::getStateInformation(){
    XmlElement state("BiasState");
    for (int i=0; i<getNumParameters(); i++)
        state.setAttribute(String::formatted("parameter%d", i), getParameterValue(i));
    //    state.setAttribute(getParameterName(i), getParameterValue(i));
    return state;
}

void Bias::setStateInformation(ScopedPointer<XmlElement> state){
    if (state->hasTagName("BiasState"))
    {
        for (int i=0; i<getNumParameters(); i++)
            setParameterValue(i, (float)state->getDoubleAttribute(String::formatted("parameter%d", i), getParameterValue(i)));
        //      setParameterValue(i, (float)state->getDoubleAttribute(getParameterName(i), getParameterValue(i)));
    }
}
