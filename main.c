//
// Created by lkwhe on 17/04/2026.
//
#include <stdio.h>
#include "io.h"
#include "waveform.h"
#include "stdlib.h"

int main(void) {
    // Main function. Calls all other functions

    // Setting the values used for the voltage limit, nominal voltage, the sample size and
    // the distance in the array between consecutive values from a column of the csv
    double voltage_limit = 324.9;
    double nominal_voltage = 230;
    int sample_size = 1000;
    int interval = 8;

    // Calling the read_file function to retrieve the data from the csv
    waveform_data *wave_data = read_file();

    // Calculating the RMS value for each waveform
    double RMS_A = compute_rms(&wave_data[0].phase_A_voltage, sample_size, interval);
    double RMS_B = compute_rms(&wave_data[0].phase_B_voltage, sample_size, interval);
    double RMS_C = compute_rms(&wave_data[0].phase_C_voltage, sample_size, interval);
    double RMS_values[] = {RMS_A, RMS_B, RMS_C};

    // Calculating the peak to peak voltage for each waveform
    double Vpp_A = compute_peak_to_peak(&wave_data[0].phase_A_voltage, sample_size, interval);
    double Vpp_B = compute_peak_to_peak(&wave_data[0].phase_B_voltage, sample_size, interval);
    double Vpp_C = compute_peak_to_peak(&wave_data[0].phase_C_voltage, sample_size, interval);
    double Vpp_values[] = {Vpp_A, Vpp_B, Vpp_C};

    // calculating the DC offset for each waveform
    double dc_offset_A = compute_dc_offset(&wave_data[0].phase_A_voltage, sample_size, interval);
    double dc_offset_B = compute_dc_offset(&wave_data[0].phase_B_voltage, sample_size, interval);
    double dc_offset_C = compute_dc_offset(&wave_data[0].phase_C_voltage, sample_size, interval);
    double dc_offset_values[] = {dc_offset_A, dc_offset_B, dc_offset_C};

    // Calculating the number of times each waveform gave a value outside of the sensor imit
    int clip_count_A = count_clipped(&wave_data[0].phase_A_voltage, sample_size, interval, voltage_limit);
    int clip_count_B = count_clipped(&wave_data[0].phase_B_voltage, sample_size, interval, voltage_limit);
    int clip_count_C = count_clipped(&wave_data[0].phase_C_voltage, sample_size, interval, voltage_limit);
    int clip_count_values[] = {clip_count_A, clip_count_B, clip_count_C};

    // Checking whether the RMS value for each waveform is compliant with the standards given
    int compliance_A = check_compliance(RMS_A, nominal_voltage);
    int compliance_B = check_compliance(RMS_B, nominal_voltage);
    int compliance_C = check_compliance(RMS_C, nominal_voltage);
    int compliance_values[] = {compliance_A, compliance_B, compliance_C};

    // Freeing the memory allocated for the data
    free(wave_data);

    // Calling the write_file function to write the results to a text file
    write_file(RMS_values, Vpp_values, dc_offset_values, clip_count_values, compliance_values);
    return 0;
}
