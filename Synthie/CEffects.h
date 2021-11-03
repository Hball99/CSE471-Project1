#pragma once
#include <string>
#include <vector>
class CEffects
{
public:
	CEffects();
	~CEffects();
	void ProcessStream(double*, int);
	void XmlLoad(IXMLDOMNode*, std::wstring&);
	void SetSampleRate(double s) { sample_rate = s; };

private:
	double in_frame[2];
	double out_frame[2];

	double sample_rate;

	bool chorus;
	double chorus_delay;
	double chorus_range;
	double chorus_rate;
	double chorus_wet;
	double chorus_dry;
	int m_wrloc;
	std::vector<double> chorus_queue;
};

