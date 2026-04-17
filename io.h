//
// Created by lkwhe on 15/04/2026.
//

#ifndef PROGRAMMING_COURSEWORK_IO_H
#define PROGRAMMING_COURSEWORK_IO_H

typedef struct {
    double timestamp[1000];
    double phase_A_voltage[1000];
    double phase_B_voltage[1000];
    double phase_C_voltage[1000];
    double line_current[1000];
    double frequency[1000];
    double power_factor[1000];
    double thd_percent[1000];
}waveform_data;

waveform_data read_file();

int write_file(double[], double[], double[], int[], int[]);

#endif //PROGRAMMING_COURSEWORK_IO_H
