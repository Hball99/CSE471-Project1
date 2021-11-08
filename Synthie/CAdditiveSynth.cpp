#include "pch.h"
#include "CAdditiveSynth.h"
#include "Notes.h"
#include <sstream>

CAdditiveSynth::CAdditiveSynth(void)
{
    m_duration = 0.1;
    m_secperbeat = 0.1;
}

void CAdditiveSynth::SetFreq(double f) {
    for (int i = 1; i <= 8; i++) {
        if (f * i >= GetSampleRate() / 2) {
            break;
        }
        CSineWave sinewave;
        sinewave.SetFreq(f * i);
        m_sinewaves.push_back(sinewave);
    }
}
void CAdditiveSynth::SetAmplitude(std::vector<std::wstring> amplitudes) {
    std::vector<std::wstring>::iterator am = amplitudes.begin();
    double amplitude = 0;
    if (am != amplitudes.end()) {
        amplitude = std::stod(*am);
    }
    
    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->SetAmplitude(amplitude); 
        if (am != amplitudes.end()) {
            ++am;
        }
        if (am != amplitudes.end()) {
            amplitude = std::stod(*am);
        }
        else {
            amplitude = 0.0;
        }
        
    }
}

void CAdditiveSynth::SetVibrato(std::vector<std::wstring> vibrato) {
    
    double frequency = std::stod(vibrato[0]);
    double amplitude = std::stod(vibrato[1]);
    

    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->InitVibrato(frequency, amplitude / m_sinewaves.size());
    }
}

void CAdditiveSynth::Start()
{   
    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->SetSampleRate(GetSampleRate()); 
        it->Start();

        // Tell the AR object it gets its samples from 
        // the sine wave object.
        CEnvelope adsr;
        adsr.SetSource(&(*it));
        adsr.SetSampleRate(GetSampleRate());
        adsr.Start();

        m_adsrs.push_back(adsr);
    }

    m_time = 0;
}


bool CAdditiveSynth::Generate()
{
    // Tell the component to generate an audio sample
    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->Generate();
    }
    
    /*
    // Read the component's sample and make it our resulting frame.
    m_frame[0] = m_sinewave.Frame(0);
    m_frame[1] = m_sinewave.Frame(1);

    // Update time
    m_time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return m_time < m_duration;
    */
    bool valid;
    m_frame[0] = m_adsrs[0].Frame(0);
    m_frame[1] = m_adsrs[0].Frame(1);
    for (std::vector<CEnvelope>::iterator it = m_adsrs.begin()++; it != m_adsrs.end(); ++it) {
        valid = it->Generate(m_duration); //TODO: Different Amplitude for each harmonic
        m_frame[0] += it->Frame(0);
        m_frame[1] += it->Frame(1);
    }
    m_time += GetSamplePeriod();
    return valid;
}

void CAdditiveSynth::SetNote(CNote* note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for (int i = 0; i < len; i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            double duration = value.dblVal * m_secperbeat;
            SetDuration(duration);
        }
        else if (name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }
        else if (name == "harmonics")
        {
            std::wstring amplitudes = L"", temp;
            amplitudes = value.bstrVal;
            std::vector<std::wstring> parts;
            std::wstringstream wss(amplitudes);
            while (std::getline(wss, temp, L' '))
                parts.push_back(temp);
            SetAmplitude(parts); //TODO else if abfrage und einzelne amplituden eintragen
        }
        else if (name == "vibrato")
        {
            std::wstring amplitudes = L"", temp;
            amplitudes = value.bstrVal;
            std::vector<std::wstring> parts;
            std::wstringstream wss(amplitudes);
            while (std::getline(wss, temp, L' '))
                parts.push_back(temp);
            assert(parts.size() == 2);
            SetVibrato(parts); //TODO else if abfrage und einzelne amplituden eintragen
        }
        
    }

}