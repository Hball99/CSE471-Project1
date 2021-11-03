#include "pch.h"
#include "CEffects.h"

CEffects::CEffects() {
	in_frame[0] = out_frame[0] = in_frame[1] = out_frame[1] = 0;
	chorus = false;
	chorus_delay = 0.0;
    chorus_rate = 0.0;
    chorus_range = 0.0;
    chorus_wet = 0.0;
    chorus_dry = 0.0;
    chorus_queue.resize(100000);
    m_wrloc = 0;
}

CEffects::~CEffects() {

}

void CEffects::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    if (effect == L"chorus") {
        chorus = true;
        // Loop over the list of attributes
        for (int i = 0; i < len; i++)
        {
            // Get attribute i
            CComPtr<IXMLDOMNode> attrib;
            attributes->get_item(i, &attrib);

            // Get the name of the attribute
            CComBSTR name;
            attrib->get_nodeName(&name);

            // Get the value of the attribute.  
            CComVariant value;
            attrib->get_nodeValue(&value);

            if (name == "delay")
            {
                chorus_delay = std::stod(value.bstrVal);
            }
            else if (name == "range")
            {
                chorus_range = std::stod(value.bstrVal);
            }
            else if (name == "rate")
            {
                chorus_rate = std::stod(value.bstrVal);
            }
            else if (name == "wet")
            {
                chorus_wet = std::stod(value.bstrVal);
            }
            else if (name == "dry")
            {
                chorus_dry = std::stod(value.bstrVal);
            }
        }
    }
}

void CEffects::ProcessStream(double* in_frame, int channels) {
    double original[2] = { in_frame[0], in_frame[1] };
    for (int c = 0; c < channels; c++)
	{
        if (chorus) {
            double delay = chorus_delay / 10000 + (chorus_range * chorus_delay / 10000) * sin(2 * PI * chorus_rate);
            int length = int((delay * sample_rate + 0.5)) * 2;

            m_wrloc = (m_wrloc + 1) % 100000;
            int rdloc = (m_wrloc + 100000 - length) % 100000;

            chorus_queue[m_wrloc] = in_frame[0];
       
            in_frame[c] = 0.5 * in_frame[c] + 0.5 * chorus_queue[rdloc];
            in_frame[c] *= chorus_wet;
          
            in_frame[c] += original[c] * chorus_dry;
        }
	}
}