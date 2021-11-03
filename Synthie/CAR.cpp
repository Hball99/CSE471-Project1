#include "pch.h"
#include "CAR.h"

CAR::CAR() {
	attack = 0.05;
	release = 0.05;
	time = 0.0;
}

void CAR::Start() {
}

bool CAR::Generate(double duration) {
    // Read the component's sample and make it our resulting frame.
    if (time < attack) {
        m_frame[0] = source->Frame(0) * time / attack;
        m_frame[1] = source->Frame(1) * time / attack;
    }
    else if (time > (duration - release)) {
        m_frame[0] = source->Frame(0) * (duration - time) / release;
        m_frame[1] = source->Frame(1) * (duration - time) / release;
    }
    else {
        m_frame[0] = source->Frame(0);
        m_frame[1] = source->Frame(1);
    }
   

    // Update time
    time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return time < duration;
}


bool CAR::Generate() {
    return false;
}
void CAR::SetSource(CAudioNode* sourcefile) {
	source = sourcefile;
}