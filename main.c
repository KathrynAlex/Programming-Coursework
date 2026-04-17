//
// Created by lkwhe on 17/04/2026.
//
#include <stdio.h>
#include "io.h"
#include "waveform.h"

int main(void) {
    double voltage_limit = 324.9;
    double nominal_voltage = 230;
    waveform_data wave_data = read_file();

    double RMS_A = compute_rms(wave_data.phase_A_voltage, sizeof(wave_data.phase_A_voltage)/sizeof(wave_data.phase_A_voltage[0]));
    double RMS_B = compute_rms(wave_data.phase_B_voltage, sizeof(wave_data.phase_B_voltage)/sizeof(wave_data.phase_B_voltage[0]));
    double RMS_C = compute_rms(wave_data.phase_C_voltage, sizeof(wave_data.phase_C_voltage)/sizeof(wave_data.phase_C_voltage[0]));
    double RMS_values[] = {RMS_A, RMS_B, RMS_C};

    double Vpp_A = compute_peak_to_peak(wave_data.phase_A_voltage, sizeof(wave_data.phase_A_voltage)/sizeof(wave_data.phase_A_voltage[0]));
    double Vpp_B = compute_peak_to_peak(wave_data.phase_B_voltage, sizeof(wave_data.phase_B_voltage)/sizeof(wave_data.phase_B_voltage[0]));
    double Vpp_C = compute_peak_to_peak(wave_data.phase_C_voltage, sizeof(wave_data.phase_C_voltage)/sizeof(wave_data.phase_C_voltage[0]));
    double Vpp_values[] = {Vpp_A, Vpp_B, Vpp_C};

    double dc_offset_A = compute_dc_offset(wave_data.phase_A_voltage, sizeof(wave_data.phase_A_voltage)/sizeof(wave_data.phase_A_voltage[0]));
    double dc_offset_B = compute_dc_offset(wave_data.phase_B_voltage, sizeof(wave_data.phase_B_voltage)/sizeof(wave_data.phase_B_voltage[0]));
    double dc_offset_C = compute_dc_offset(wave_data.phase_C_voltage, sizeof(wave_data.phase_C_voltage)/sizeof(wave_data.phase_C_voltage[0]));
    double dc_offset_values[] = {dc_offset_A, dc_offset_B, dc_offset_C};

    int clip_count_A = count_clipped(wave_data.phase_A_voltage, sizeof(wave_data.phase_A_voltage)/sizeof(wave_data.phase_A_voltage[0]), voltage_limit);
    int clip_count_B = count_clipped(wave_data.phase_B_voltage, sizeof(wave_data.phase_B_voltage)/sizeof(wave_data.phase_B_voltage[0]), voltage_limit);
    int clip_count_C = count_clipped(wave_data.phase_C_voltage, sizeof(wave_data.phase_C_voltage)/sizeof(wave_data.phase_C_voltage[0]), voltage_limit);
    int clip_count_values[] = {clip_count_A, clip_count_B, clip_count_C};

    int compliance_A = check_compliance(RMS_A, nominal_voltage);
    int compliance_B = check_compliance(RMS_B, nominal_voltage);
    int compliance_C = check_compliance(RMS_C, nominal_voltage);
    int compliance_values[] = {compliance_A, compliance_B, compliance_C};

    write_file(RMS_values, Vpp_values, dc_offset_values, clip_count_values, compliance_values);
    return 0;
}
