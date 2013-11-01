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

#ifndef Bias_Bias_h
#define Bias_Bias_h

#include "../JuceLibraryCode/JuceHeader.h"

enum ParameterId {
    PARAMETER_BIAS = 0,
    PARAMETER_DRYWET
};

const float MIN_BIAS = 0.1;
const float MED_BIAS = 1;
const float MAX_BIAS = 6;

class Bias {
public:
    
    Bias() {
        parameterNames.add("Bias");
        parameterNames.add("Dry/Wet");
        
        parameterValues.resize(parameterNames.size());
        //    for (int i=0; i<parameterNames.size(); i++) {
        //      parameterValues.push_back(0.5f);
        //    }
    }
    
    // Processing
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(AudioSampleBuffer& buffer, int numInputChannels,
                      int numOutputChannels, MidiBuffer& midiMessages);
    void reset();
    
    // Parameters
    const float getNumParameters(){return parameterNames.size();};
    const String getParameterName(int index);
    float getParameterValue(int index);
    void setParameterValue(int index, float value);
    
    // State
    XmlElement getStateInformation();
    void setStateInformation(ScopedPointer<XmlElement> state);
    
private:
    float getBias(float p1);
    void processChannelBlock(int size, float* buf, float* delayBuf, int delayBufIdx);
    
private:
    StringArray parameterNames;
    std::vector<float> parameterValues;
    
    float sampleRate;
};

#endif
