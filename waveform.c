//
// Created by lkwhe on 15/04/2026.
//
#include <math.h>
#include <stdio.h>

double compute_rms(double *samples, int sample_size, int interval) {
    // Computes the RMS value for a waveform
    // Returns the RMS value
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i*interval]*samples[i*interval];
    };
    double RMS = sqrt(sum/sample_size);
    return RMS;
};

double compute_peak_to_peak(double *samples, int sample_size, int interval) {
    // Computes the peak to peak voltage of a waveform by finding the
    // difference between the maximum and minimum readings
    // Returns the peak to peak voltage
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
    // Computes the DC offset of a waveform by calculating the mean of the samples
    // Returns the DC offset value
    double sum = 0;
    for (int i = 0; i < sample_size; i++) {
        sum += samples[i*interval];
    };
    double dc_offset = sum/sample_size;
    return dc_offset;
};

int count_clipped(double *samples, int sample_size, int interval, double limit) {
    // Counts how many values in a waveform sample are outside of the given sensor limit
    // Returns the number of clipped values
    int clip_count = 0;
    for (int i = 0; i < sample_size; i++) {
        if (samples[i*interval] > limit || samples[i*interval] < limit*(-1)) {
            clip_count += 1;
        };
    };
    return clip_count;
};

int check_compliance(double RMS, double nominal) {
    // Checks whether the RMS is within 10% of the expected value
    // Returns a 1 if the RMS is compliant or a 0 if it is not
    int compliant = 1;
    if (RMS > nominal * 1.1 || RMS < nominal * 0.9) {
        compliant = 0;
    };
    return compliant;
};