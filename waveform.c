//
// Created by lkwhe on 15/04/2026.
//
#include <math.h>
#include <stdio.h>

double compute_rms(double *samples, int sample_size, int interval) {
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i*interval]*samples[i*interval];
    };
    double RMS = sqrt(sum/sample_size);
    return RMS;
};

double compute_peak_to_peak(double *samples, int sample_size, int interval) {
    double max = samples[0];
    double min = samples[0];
    for (int i = 1; i < sample_size; i++) {
        if (samples[i*interval] > max) {
            max = samples[i*interval];
        } else if (samples[i*interval] < min) {
            min = samples[i*interval];
        };
    };
    double Vpp = max-min;
    return Vpp;
};

double compute_dc_offset(double samples[], int sample_size, int interval) {
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i*interval];
    };
    double dc_offset = sum/sample_size;
    return dc_offset;
};

int count_clipped(double *samples, int sample_size, int interval, double limit) {
    int clip_count = 0;
    for (int i = 0; i < sample_size; i++) {
        if (samples[i*interval] > limit || samples[i*interval] < limit*(-1)) {
            clip_count += 1;
        };
    };
    return clip_count;
};

int check_compliance(double RMS, double nominal) {
    int compliant = 1;
    if (RMS > nominal * 1.1 || RMS < nominal * 0.9) {
        compliant = 0;
    };
    return compliant;
};