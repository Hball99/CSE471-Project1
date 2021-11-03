#include "pch.h"
#include "CEffects.h"

CEffects::CEffects() {
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
        CChorus* chorus = new CChorus();
        chorus->SetSampleRate(sample_rate);
        chorus->XmlLoad(xml, effect);
        effects.push_back(chorus);
    }
}

void CEffects::ProcessStream(double* in_frame, int channels) {
    for (std::vector<CEffect*>::iterator it = effects.begin(); it != effects.end(); ++it) {
        (*it)->ProcessStream(in_frame, channels);
    }
}