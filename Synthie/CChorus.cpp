#include "pch.h"
#include "CChorus.h"


CChorus::CChorus() {
    chorus = false;
    chorus_delay = 0.0;
    chorus_wet = 0.0;
    chorus_dry = 0.0;
    chorus_queue_0.resize(100000);
    chorus_queue_1.resize(100000);
    m_wrloc = 0;
}

CChorus::~CChorus(){

}


void CChorus::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {
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

void CChorus::ProcessStream(double* in_frame, int channels) {

    assert(chorus && channels == 2);
    double original[2] = { in_frame[0], in_frame[1] };
    int length = int((chorus_delay * sample_rate + 0.5));

    m_wrloc = (m_wrloc + 1) % 100000;
    int rdloc = (m_wrloc + 100000 - length) % 100000;

    chorus_queue_0[m_wrloc] = in_frame[0];
    chorus_queue_1[m_wrloc] = in_frame[1];

    in_frame[0] = 0.5 * in_frame[0] + 0.5 * chorus_queue_0[rdloc] * chorus_wet + original[0] * chorus_dry;
    in_frame[1] = 0.5 * in_frame[1] + 0.5 * chorus_queue_1[rdloc] * chorus_wet + original[1] * chorus_dry;      
}