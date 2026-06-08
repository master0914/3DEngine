//
// Created by augus on 02.05.2026.
//

#ifndef INC_3DENGINE_FFT_H
#define INC_3DENGINE_FFT_H


#endif //INC_3DENGINE_FFT_H

#pragma once

#include "audioData.h"
#include "pffft/pffft.hpp"


std::vector<float> computeSpectrum(const AudioData& audio) {
    const size_t fftSize = 1024;
    if (audio.samples.size() < fftSize) return {};
    pffft::Fft<float> fft = {fftSize};




    return {};
}