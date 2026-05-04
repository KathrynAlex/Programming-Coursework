//
// Created by lkwhe on 15/04/2026.
//

#ifndef PROGRAMMING_COURSEWORK_IO_H
#define PROGRAMMING_COURSEWORK_IO_H

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
}waveform_data;

waveform_data *read_file();

int write_file(double[], double[], double[], int[], int[]);

#endif //PROGRAMMING_COURSEWORK_IO_H
