//
// Created by lkwhe on 15/04/2026.
//
#include <math.h>

double compute_rms(double samples[], int sample_size) {
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i]*samples[i];
    };
    double RMS = sqrt(sum/sample_size);
    return RMS;
};

double compute_peak_to_peak(double samples[], int sample_size) {
    double max = samples[0];
    double min = samples[0];
    for (int i = 1; i < sample_size; i++) {
        if (samples[i] > max) {
            max = samples[i];
        } else if (samples[i] < min) {
            min = samples[i];
        };
    };
    double Vpp = max-min;
    return Vpp;
};

double compute_dc_offset(double samples[], int sample_size) {
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i];
    };
    double dc_offset = sum/sample_size;
    return dc_offset;
};

int count_clipped(double samples[], int sample_size, double limit) {
    int clip_count = 0;
    for (int i = 0; i < sample_size; i++) {
        if (samples[i] > limit || samples[i] < limit*(-1)) {
            clip_count += 1;
        };
    };
    return clip_count;
};

int check_compliance(double Vpp, double nominal) {
    int compliant = 1;
    if (Vpp > nominal*1.1 || Vpp < nominal * 0.9) {
        compliant = 0;
    };
    return compliant;
};