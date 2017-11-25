//
//  AKChowningReverbDSPKernel.hpp
//  AudioKit
//
//  Created by Aurelius Prochazka, revision history on Github.
//  Copyright © 2017 Aurelius Prochazka. All rights reserved.
//

#pragma once

#import "AKDspSoundPipe.hpp"

class AKChowningReverbDsp : public AKDspSoundpipeBase {
    sp_jcrev* _jcrev0;
    sp_jcrev* _jcrev1;

public:
    AKChowningReverbDsp() {}

    void init(int _channels, double _sampleRate) override {
        AKDspSoundpipeBase::init(_channels, _sampleRate);
        sp_jcrev_create(&_jcrev0);
        sp_jcrev_init(_sp, _jcrev0);
        sp_jcrev_create(&_jcrev1);
        sp_jcrev_init(_sp,  _jcrev1);
    }

    void destroy() {
        sp_jcrev_destroy(&_jcrev0);
        sp_jcrev_destroy(&_jcrev1);
        AKDspSoundpipeBase::destroy();
    }

    void processSample(int channel, float* in, float* out) override {
        if (channel == 0) {
            sp_jcrev_compute(_sp, _jcrev0, in, out);
        } else {
            sp_jcrev_compute(_sp, _jcrev1, in, out);
        }
    }
};

