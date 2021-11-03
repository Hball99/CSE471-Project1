#include "pch.h"
#include "CSineWave.h"

CSineWave::CSineWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
    vibrato_freq = 0.0;
    vibrato_amp = 0.0;
    vibrato_phase = 0.0;
}

void CSineWave::InitVibrato(double frequency, double amplitude) {
    vibrato_freq = frequency;
    vibrato_amp = amplitude;
}

void CSineWave::Start()
{
    m_phase = 0;
}

bool CSineWave::Generate()
{
    double vibrato = vibrato_amp * sin(vibrato_phase + m_phase * 2 * PI);
    m_frame[0] = m_amp * sin(m_phase * 2 * PI) + vibrato;
    m_frame[1] = m_frame[0];

    m_phase += m_freq * GetSamplePeriod();
    vibrato_phase += vibrato_freq * GetSamplePeriod();

    return true;
}
