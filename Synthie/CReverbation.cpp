#include "pch.h"
#include "CReverbation.h"

CReverbation::CReverbation() {
    reverbation_queue_0.resize(100000);
    reverbation_queue_1.resize(100000);
    output_queue_0.resize(100000);
    output_queue_1.resize(100000);
    m_wrloc = 0;
    reverbation_rate = 0;
    reverbation = false;
}

CReverbation::~CReverbation() {

}

void CReverbation::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    if (effect == L"reverbation") {
        reverbation = true;
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

            if (name == "rate")
            {
                reverbation_rate = std::stod(value.bstrVal);
            }
        }
    }
}

void CReverbation::ProcessStream(double* in_frame, int channels) {
    assert(reverbation && channels == 2);
    
    m_wrloc = (m_wrloc + 1) % 100000;

    reverbation_queue_0[(m_wrloc)] = in_frame[0];
    reverbation_queue_1[(m_wrloc)] = in_frame[1];

    int factor = 1;
    for (int i = 2; i < int(max((reverbation_rate / 7),10)); i++) {
        int rdloc = int(m_wrloc + 100000 - reverbation_rate * i * (sample_rate / 10000)) % 100000;
        in_frame[0] += reverbation_queue_0[rdloc] * 1/i;
        in_frame[1] += reverbation_queue_1[rdloc] * 1/i;
        factor += 1 / i;
    }
    
    in_frame[0] /= factor;
    in_frame[1] /= factor;
    
}