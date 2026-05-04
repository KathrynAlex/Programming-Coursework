//
// Created by lkwhe on 15/04/2026.
//
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    // Stores the data for one row of the power_quality_log csv file
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
}waveform_data;

waveform_data *read_file() {
    // Reads in the data from the csv file and sorts it into an array of instances of waveform_data
    // Returns a pointer to the first element of the array

    // Allocating memory for the data to be stored in and checking whether successful
    waveform_data *wave_data = malloc(1000*64);
    if (wave_data == NULL) {
        printf("Memory allocation failed\n");
    };

    // Opening the csv file
    char filename[] = "C:\\Users\\lkwhe\\OneDrive - UWE Bristol\\Programming for Engineers\\Coursework\\Programming-Coursework\\power_quality_log.csv";
    printf("%s \n", filename);
    FILE *fptr = fopen(filename, "r");

    // Checks if file was opened successfully
    if (fptr == NULL) {
        printf("File not found \n");
    } else {
        printf("File opened \n");

        // Retrieving the header row from the csv file
        char row[256];
        fgets(row, 256, fptr);
        char *token = strtok(row, ",");

        // Matching the column headers to variables in the waveform_data struct
        int i = 0;
        double *order[8];
        while(token != NULL) {
            if (strcmp(&token[strlen(token)-1], "\n") == 0) {
                token[strlen(token)-1] = 0;
            };
            if (strcmp(token, "timestamp") == 0) {
                order[i] = &wave_data[0].timestamp;
            } else if (strcmp(token, "phase_A_voltage") == 0) {
                order[i] = &wave_data[0].phase_A_voltage;
            } else if (strcmp(token, "phase_B_voltage") == 0) {
                order[i] = &wave_data[0].phase_B_voltage;
            } else if (strcmp(token, "phase_C_voltage") == 0) {
                order[i] = &wave_data[0].phase_C_voltage;
            } else if (strcmp(token, "frequency") == 0) {
                order[i] = &wave_data[0].frequency;
            } else if (strcmp(token, "line_current") == 0) {
                order[i] = &wave_data[0].line_current;
            } else if (strcmp(token, "power_factor") == 0) {
                order[i] = &wave_data[0].power_factor;
            } else if (strcmp(token, "thd_percent") == 0) {
                order[i] = &wave_data[0].thd_percent;
            } else {
                printf("%s \n", token);
            };
            token = strtok(NULL, ",");
            i += 1;
        };

        // Sorting each row of data into an instance of the waveform_data struct
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
                order[i][j*8] = value;
                token = strtok(NULL, ",");
                i += 1;
            };
            j += 1;
        };

        // Closing the file
        fclose(fptr);
        printf("File closed \n");
    };
    return wave_data;
};

int write_file(double RMS[], double Vpp[], double dc_offset[], int clip_count[], int compliance[]) {
    // Writes the calculated results into a text file
    // Returns 1 if successful or 0 if unsuccessful

    // Creating the text file
    FILE* fptr;
    char filename[] = "C:\\Users\\lkwhe\\OneDrive - UWE Bristol\\Programming for Engineers\\Coursework\\Programming-Coursework\\results.txt";
    fptr = fopen(filename, "w");
    int success = 0;

    // Checks if file was created successfully
    if (fptr == NULL) {
        printf("File could not be created\n");
    } else {
        success = 1;
        printf("File created successfully\n");

        // Printing the results to the text file in a table format
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
        printf("File closed \n");
    };
    return success;
};