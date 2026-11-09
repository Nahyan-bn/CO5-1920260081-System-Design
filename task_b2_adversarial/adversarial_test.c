#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safe_read_name(char *dest, size_t max_len, const char *raw_input) {
    /* Using bounded copying to prevent buffer overflow */
    strncpy(dest, raw_input, max_len - 1);
    dest[max_len - 1] = '\0';
}

int main(int argc, char *argv[]) {
    printf("=== Adversarial Input & Robustness Test ===\n");

    /* 1. Missing data file test using perror() */
    FILE *fp = fopen("missing_blood_records.dat", "rb");
    if (fp == NULL) {
        perror("[Robustness Test] fopen failed as expected");
    } else {
        fclose(fp);
    }

    /* 2. Buffer overflow mitigation test */
    char safe_buffer[16];
    const char *oversized_input = "Dr. Alexander Bartholomew Montgomery III";
    printf("\nAttempting to store oversized input (%zu chars) in 16-byte buffer:\n", strlen(oversized_input));
    safe_read_name(safe_buffer, sizeof(safe_buffer), oversized_input);
    printf("Truncated Safe String: \"%s\"\n", safe_buffer);

    /* 3. Command-line argument validation */
    printf("\n=== CLI Arguments Validation ===\n");
    if (argc < 2) {
        printf("[Notice] No command-line arguments provided. Defaulting to audit mode.\n");
        printf("Usage: ./adversarial_test <BLOOD_GROUP>\n");
    } else {
        const char *valid_groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        int valid = 0;
        for (int i = 0; i < 8; i++) {
            if (strcmp(argv[1], valid_groups[i]) == 0) {
                valid = 1;
                break;
            }
        }
        if (valid) {
            printf("Valid blood group supplied: %s\n", argv[1]);
        } else {
            printf("[ERROR] Invalid blood group entered: \"%s\". Valid groups are A+, B+, O+, AB+, etc.\n", argv[1]);
        }
    }

    return 0;
}