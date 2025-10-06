/*
===============================================================================
          ARR HOSPITAL CARE SYSTEM  🏥
===============================================================================

   Project Title   : ARR Hospital Care System
   Language Used   : C Programming
   IDE/Compiler    : Code::Blocks
   Duration        : November 2022 - December 2022
   Developed By    :
                     1. A. Agnes Swetha
                     2. Rhithika K
                     3. Riventhiga S

   Description     :
   -----------------
   This project is a simple console-based Hospital Management System created
   as part of our 1st Year, 1st Semester C programming mini project.

   It allows users to:
   - Admit and discharge patients
   - Register and view doctor details
   - Store data locally using file handling concepts

   Concepts Used   : Structures, File Handling, Functions, Loops, and Time functions
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to store patient information
struct PatientInfo {
    int patientID;
    char name[50];
    char address[100];
    char illness[50];
    char admitDate[15];
} patient;

// Structure to store doctor details
struct DoctorInfo {
    int doctorID;
    char name[50];
    char location[100];
    char department[50];
    char joinDate[15];
} doctor;

FILE *file;

// Function Declarations
void admitNewPatient();
void displayPatients();
void releasePatient();
void registerDoctor();
void displayDoctors();

// Main function
int main() {
    int choice;

    while (1) {
        system("cls"); // Clear screen each time menu shows
        printf("====================================================\n");
        printf("          *** ARR HOSPITAL CARE SYSTEM ***\n");
        printf("====================================================\n");
        printf("1. Admit New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Discharge Patient\n");
        printf("4. Register Doctor\n");
        printf("5. View Doctors List\n");
        printf("0. Exit\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                admitNewPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                releasePatient();
                break;
            case 4:
                registerDoctor();
                break;
            case 5:
                displayDoctors();
                break;
            case 0:
                system("cls");
                printf("\nThank you for using ARR Hospital Care System!\n");
                exit(0);
            default:
                printf("\nInvalid option! Please enter again.\n");
        }

        printf("\n\nPress Enter to continue...");
        getchar(); // to pause
        getchar(); // wait for user input
    }
    return 0;
}

// Function to admit a new patient
void admitNewPatient() {
    system("cls");
    char today[15];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(today, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(patient.admitDate, today);

    file = fopen("patients_data.txt", "ab");

    printf("\n<=== Admit New Patient ===>\n");
    printf("Enter Patient ID: ");
    scanf("%d", &patient.patientID);
    fflush(stdin);

    printf("Enter Patient Name: ");
    fgets(patient.name, sizeof(patient.name), stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;

    printf("Enter Patient Address: ");
    fgets(patient.address, sizeof(patient.address), stdin);
    patient.address[strcspn(patient.address, "\n")] = 0;

    printf("Enter Disease/Illness: ");
    fgets(patient.illness, sizeof(patient.illness), stdin);
    patient.illness[strcspn(patient.illness, "\n")] = 0;

    fwrite(&patient, sizeof(patient), 1, file);
    fclose(file);

    printf("\n Patient admitted successfully on %s.\n", patient.admitDate);
}

// Function to display all patients
void displayPatients() {
    system("cls");
    printf("<=== Patient Records ===>\n\n");

    file = fopen("patients_data.txt", "rb");

    if (!file) {
        printf("No patient records found!\n");
        return;
    }

    printf("%-8s %-25s %-30s %-20s %-12s\n", "ID", "Name", "Address", "Disease", "Admit Date");
    printf("------------------------------------------------------------------------------------------------------\n");

    while (fread(&patient, sizeof(patient), 1, file)) {
        printf("%-8d %-25s %-30s %-20s %-12s\n",
               patient.patientID, patient.name, patient.address,
               patient.illness, patient.admitDate);
    }

    fclose(file);
}

// Function to discharge a patient
void releasePatient() {
    system("cls");
    int id, found = 0;
    FILE *tempFile;

    file = fopen("patients_data.txt", "rb");
    tempFile = fopen("temp_data.txt", "wb");

    if (!file) {
        printf("No patient records available!\n");
        return;
    }

    printf("<=== Discharge Patient ===>\n\n");
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &id);

    while (fread(&patient, sizeof(patient), 1, file)) {
        if (patient.patientID == id) {
            found = 1;
        } else {
            fwrite(&patient, sizeof(patient), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("patients_data.txt");
    rename("temp_data.txt", "patients_data.txt");

    if (found)
        printf("\n Patient with ID %d has been successfully discharged.\n", id);
    else
        printf("\n Patient ID not found.\n");
}

// Function to register a doctor
void registerDoctor() {
    system("cls");
    char today[15];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(today, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(doctor.joinDate, today);

    file = fopen("doctor_data.txt", "ab");

    printf("\n<=== Register New Doctor ===>\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &doctor.doctorID);
    fflush(stdin);

    printf("Enter Doctor Name: ");
    fgets(doctor.name, sizeof(doctor.name), stdin);
    doctor.name[strcspn(doctor.name, "\n")] = 0;

    printf("Enter Doctor Location: ");
    fgets(doctor.location, sizeof(doctor.location), stdin);
    doctor.location[strcspn(doctor.location, "\n")] = 0;

    printf("Enter Department/Specialization: ");
    fgets(doctor.department, sizeof(doctor.department), stdin);
    doctor.department[strcspn(doctor.department, "\n")] = 0;

    fwrite(&doctor, sizeof(doctor), 1, file);
    fclose(file);

    printf("\n Doctor registered successfully on %s.\n", doctor.joinDate);
}

// Function to display all doctors
void displayDoctors() {
    system("cls");
    printf("<=== Doctor Details ===>\n\n");

    file = fopen("doctor_data.txt", "rb");

    if (!file) {
        printf("No doctor records found!\n");
        return;
    }

    printf("%-8s %-25s %-30s %-25s %-12s\n", "ID", "Name", "Location", "Department", "Join Date");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&doctor, sizeof(doctor), 1, file)) {
        printf("%-8d %-25s %-30s %-25s %-12s\n",
               doctor.doctorID, doctor.name, doctor.location,
               doctor.department, doctor.joinDate);
    }

    fclose(file);
}
