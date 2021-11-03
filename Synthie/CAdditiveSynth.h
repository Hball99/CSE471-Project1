#pragma once
#include "CInstrument.h"
#include "CSineWave.h"
#include "CAR.h"
#include "vector"

class CAdditiveSynth :
    public CInstrument
{
public:
    CAdditiveSynth();

    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f);
    void SetAmplitude(std::vector<std::wstring>);
    void SetVibrato(std::vector<std::wstring>);
    void SetDuration(double d) { m_duration = d; }
    void SetNote(CNote* note);
    void SetSecPerBeat(double t) { m_secperbeat = t; }

private:
    std::vector<CSineWave>   m_sinewaves;
    std::vector<CAR>         m_ars;

    double      m_duration;
    double      m_time;
    double      m_secperbeat;
    };

