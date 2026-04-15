//
// Created by lkwhe on 15/04/2026.
//

#ifndef PROGRAMMING_COURSEWORK_WAVEFORM_H
#define PROGRAMMING_COURSEWORK_WAVEFORM_H

double compute_rms(double [], int);

double compute_peak_to_peak(double [], int);

double compute_dc_offset(double [], int);

int count_clipped(double [], int, double);

int check_compliance(double, double);

#endif //PROGRAMMING_COURSEWORK_WAVEFORM_H
