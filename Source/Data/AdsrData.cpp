/*
  ==============================================================================

    AdsrData.cpp
    Created: 1 Apr 2024 2:59:24pm
    Author:  admin

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateParameters(const float attack, const float decay, const float sustain, const float release) 
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}