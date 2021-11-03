#pragma once
#include "msxml2.h"
#include <list>
#include <vector>
#include "CInstrument.h"
#include <string>
#include "CNote.h"
#include "CAR.h"
#include "CEffects.h"


class CSynthesizer
{
public:
    //! Constructor
    CSynthesizer();

    //! Destructor
    ~CSynthesizer();

    //! Number of audio channels
    int GetNumChannels() { return m_channels; }

    //! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

    //! Seconds per Beat
    double GetSecPerBeat() { return m_secperbeat; }

    //! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Get the time since we started generating audio
    double GetTime() { return m_time; }

    //! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

    //! Clear all instruments
    void Clear();

    //! Open score file
    void OpenScore(CString& filename);

    void XmlLoadScore(IXMLDOMNode* xml);

    void XmlLoadInstrument(IXMLDOMNode* xml);

    void XmlLoadEffect(IXMLDOMNode* xml);

    void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);

    //! Start the synthesizer
    void Start();

    //! Generate one audio frame
    bool Generate(double* frame);

private:
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;
    double  m_time;
    double  m_bpm;                  //!< Beats per minute
    int     m_beatspermeasure;  //!< Beats per measure
    double  m_secperbeat;        //!< Seconds per beat
    std::vector<CNote> m_notes;

private:
    std::list<CInstrument*>  m_instruments;
    CEffects effects;
    int m_currentNote;          //!< The current note we are playing
    int m_measure;              //!< The current measure
    double m_beat;              //!< The current beat within the measure
};

#pragma comment(lib, "msxml2.lib")