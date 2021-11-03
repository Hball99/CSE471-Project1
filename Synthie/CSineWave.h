#pragma once
#include "CAudioNode.h"
class CSineWave :
    public CAudioNode
{
public:
    //! Constructor
    CSineWave();
    
    //! Start audio generation
    virtual void Start();

    //! Generate one frame of audio
    virtual bool Generate();

    //! Set the sine wave frequency
    void SetFreq(double f) { m_freq = f; }

    //! Set the sine wave amplitude
    void SetAmplitude(double a) { m_amp = a; }

    void InitVibrato(double frequency, double amplitude);

private:
    double m_freq;
    double m_amp;
    double m_phase;
    double vibrato_freq;
    double vibrato_amp;
    double vibrato_phase;
};

