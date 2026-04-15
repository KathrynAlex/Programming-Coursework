//
// Created by lkwhe on 15/04/2026.
//
#include <math.h>

float compute_rms(float samples[], int sample_size) {
    float sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i]*samples[i];
    };
    float RMS = sqrt(sum/sample_size);
    return RMS;
};

float compute_peak_to_peak(float samples[], int sample_size) {
    float max = samples[0];
    float min = samples[0];
    for (int i = 1; i < sample_size; i++) {
        if (samples[i] > max) {
            max = samples[i];
        } else if (samples[i] < min) {
            min = samples[i];
        };
    };
    float Vpp = max-min;
    return Vpp;
};

float compute_dc_offset(float samples[], int sample_size) {
    float sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i];
    };
    float dc_offset = sum/sample_size;
    return dc_offset;
};

int count_clipped(float samples[], int sample_size, float limit) {
    int clip_count = 0;
    for (int i = 0; i < sample_size; i++) {
        if (samples[i] > limit || samples[i] < limit*(-1)) {
            clip_count += 1;
        };
    };
    return clip_count;
};

int check_compliance(float Vpp, float nominal) {
    int compliant = 1;
    if (Vpp > nominal*1.1 || Vpp < nominal * 0.9) {
        compliant = 0;
    };
    return compliant;
};