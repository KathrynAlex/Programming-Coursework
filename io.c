//
// Created by lkwhe on 15/04/2026.
//
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

waveform_data read_file() {
    waveform_data wave_data;
    char filename[] = "C:\\Users\\lkwhe\\OneDrive - UWE Bristol\\Programming for Engineers\\Coursework\\Programming-Coursework\\power_quality_log.csv";
    printf("%s \n", filename);
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("File not found \n");
    } else {
        printf("File opened \n");
        char row[256];
        fgets(row, 256, fptr);
        char *token = strtok(row, ",");
        int i = 0;
        double* order[8];
        while(token != NULL) {
            if (strcmp(&token[strlen(token)-1], "\n") == 0) {
                token[strlen(token)-1] = 0;
            };
            if (strcmp(token, "timestamp") == 0) {
                order[i] = wave_data.timestamp;
            } else if (strcmp(token, "phase_A_voltage") == 0) {
                order[i] = wave_data.phase_A_voltage;
            } else if (strcmp(token, "phase_B_voltage") == 0) {
                order[i] = wave_data.phase_B_voltage;
            } else if (strcmp(token, "phase_C_voltage") == 0) {
                order[i] = wave_data.phase_C_voltage;
            } else if (strcmp(token, "frequency") == 0) {
                order[i] = wave_data.frequency;
            } else if (strcmp(token, "line_current") == 0) {
                order[i] = wave_data.line_current;
            } else if (strcmp(token, "power_factor") == 0) {
                order[i] = wave_data.power_factor;
            } else if (strcmp(token, "thd_percent") == 0) {
                order[i] = wave_data.thd_percent;
            } else {
                printf("%s \n", token);
            };
//            printf("%p \n", order[i]);
            token = strtok(NULL, ",");
            i += 1;
        };
        int j = 0;
        double value;
        char *ptr;
        while (fgets(row, 256, fptr) != NULL) {
            token = strtok(row, ",");
            i = 0;
            while(token != NULL) {
                if (strcmp(&token[strlen(token)-1], "\n") == 0) {
                    token[strlen(token)-1] = 0;
                };
                value = strtod(token, &ptr);
                *(order[i]+j) = value;
                token = strtok(NULL, ",");
                i += 1;
            };
            j += 1;
        };
//        printf("%lf \n", wave_data.phase_C_voltage[100]);
        fclose(fptr);
        printf("File closed \n");
    };
    return wave_data;
};

int write_file(double RMS[], double Vpp[], double dc_offset[], int clip_count[], int compliance[]) {
    FILE* fptr;
    char filename[] = "C:\\Users\\lkwhe\\OneDrive - UWE Bristol\\Programming for Engineers\\Coursework\\Programming-Coursework\\results.txt";
    fptr = fopen(filename, "w");
    int success = 0;
    if (fptr == NULL) {
        printf("File could not be created");
    } else {
        success = 1;
        printf("File created successfully");
        fprintf(fptr, "          ~*~*~*~ WAVEFORM ANALYSIS RESULTS ~*~*~*~\n");
        fprintf(fptr, "===============================================================\n");
        fprintf(fptr, "|                      |  Source A  |  Source B  |  Source C  |\n");
        fprintf(fptr, "|-------------------------------------------------------------|\n");
        fprintf(fptr, "|      RMS Voltage     | %lf | %lf | %lf |\n", RMS[0], RMS[1], RMS[2]);
        fprintf(fptr, "|-------------------------------------------------------------|\n");
        fprintf(fptr, "| Peak to Peak Voltage | %lf | %lf | %lf |\n", Vpp[0], Vpp[1], Vpp[2]);
        fprintf(fptr, "|-------------------------------------------------------------|\n");
        fprintf(fptr, "|       DC Offset      | %lf  |  %lf  | %lf  |\n", dc_offset[0], dc_offset[1], dc_offset[2]);
        fprintf(fptr, "|-------------------------------------------------------------|\n");
        fprintf(fptr, "|      Clip Count      |     %d     |     %d     |     %d     |\n", clip_count[0], clip_count[1], clip_count[2]);
        fprintf(fptr, "|-------------------------------------------------------------|\n");
        fprintf(fptr, "|      Compliance      |     %d      |     %d      |     %d      |\n", compliance[0], compliance[1], compliance[2]);
        fprintf(fptr, "===============================================================\n");
        fclose(fptr);
    };
    return success;
};