//
// Created by lkwhe on 15/04/2026.
//

#ifndef PROGRAMMING_COURSEWORK_IO_H
#define PROGRAMMING_COURSEWORK_IO_H

typedef struct {
    float timestamp[1000];
    float phase_A_voltage[1000];
    float phase_B_voltage[1000];
    float phase_C_voltage[1000];
    float line_current[1000];
    float frequency[1000];
    float power_factor[1000];
    float thd_percent[1000];
}waveform_data;

waveform_data read_file();

#endif //PROGRAMMING_COURSEWORK_IO_H
