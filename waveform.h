//
// Created by lkwhe on 15/04/2026.
//

#ifndef PROGRAMMING_COURSEWORK_WAVEFORM_H
#define PROGRAMMING_COURSEWORK_WAVEFORM_H

float compute_rms(float [], int);

float compute_peak_to_peak(float [], int);

float compute_dc_offset(float [], int);

int count_clipped(float [], int, float);

int check_compliance(float, float);

#endif //PROGRAMMING_COURSEWORK_WAVEFORM_H
