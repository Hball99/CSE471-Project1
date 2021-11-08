#include "pch.h"
#include "CEnvelope.h"

CEnvelope::CEnvelope() {
	attack_ratio = 0.1;
	release_ratio = 0.1;
    decay_ratio = 0.4;
	time = 0.0;
    sustain_level = 0.7;
}

void CEnvelope::Start() {
}

bool CEnvelope::Generate(double duration) {
    // Read the component's sample and make it our resulting frame.
    double attack = attack_ratio * duration;
    double release = release_ratio * duration;
    double decay = decay_ratio * duration;
    if (time < attack) {
        //Attack
        m_frame[0] = source->Frame(0) * time / attack;
        m_frame[1] = source->Frame(1) * time / attack;
    }
    else if (time >= attack && time < (attack + decay)) {
        //Decay
        m_frame[0] = source->Frame(0) * sustain_level + 
            source->Frame(0) * (1 - sustain_level) *(decay + attack - time) / decay;
        m_frame[1] = source->Frame(1) * sustain_level +
            source->Frame(1) * (1 - sustain_level) * (decay + attack - time) / decay;
    }
    else if (time > (duration - release)) {
        //Release
        m_frame[0] = sustain_level * source->Frame(0) * (duration - time) / release;
        m_frame[1] = sustain_level * source->Frame(1) * (duration - time) / release;
    }
    else {
        //Sustain
        m_frame[0] = sustain_level * source->Frame(0);
        m_frame[1] = sustain_level * source->Frame(1);
    }
   

    // Update time
    time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return time < duration;
}


bool CEnvelope::Generate() {
    return false;
}
void CEnvelope::SetSource(CAudioNode* sourcefile) {
	source = sourcefile;
}