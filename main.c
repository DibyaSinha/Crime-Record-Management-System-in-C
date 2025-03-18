#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[100];
    char crime_type[50];
    char date[20];
    char punishment_period[20];
} Criminal;

typedef struct {
    int id;
    char complainant_name[100];
    char incident_details[500];
    char date[20];
    char police_station[100];
    char status[20];
} Complaint;

// Function prototypes
void addCriminal();
void displayAllCriminals();
void searchCriminal();
void addComplaint();
void displayPendingComplaints();
void convertComplaintToFIR();
int getNextCriminalId();
int getNextComplaintId();
void criminalManagement();
void complaintManagement();

int main() {
    int choice;
    do {
        printf("\n*** Crime Record Management System ***\n");
        printf("1. Criminal Management\n");
        printf("2. Complaint Management\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                criminalManagement();
                break;
            case 2:
                complaintManagement();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}

void criminalManagement() {
    int choice;
    do {
        printf("\n*** Criminal Management ***\n");
        printf("1. Add Criminal\n");
        printf("2. View All Criminals\n");
        printf("3. Search Criminal\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addCriminal();
                break;
            case 2:
                displayAllCriminals();
                break;
            case 3:
                searchCriminal();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void complaintManagement() {
    int choice;
    do {
        printf("\n*** Complaint Management ***\n");
        printf("1. File a Complaint\n");
        printf("2. View Pending Complaints\n");
        printf("3. Convert Complaint to FIR\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addComplaint();
                break;
            case 2:
                displayPendingComplaints();
                break;
            case 3:
                convertComplaintToFIR();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

int getNextCriminalId() {
    FILE *fp = fopen("criminals.dat", "rb");
    Criminal c;
    int maxId = 0;
    if (fp != NULL) {
        while (fread(&c, sizeof(Criminal), 1, fp)) {
            if (c.id > maxId) maxId = c.id;
        }
        fclose(fp);
    }
    return maxId + 1;
}

int getNextComplaintId() {
    FILE *fp = fopen("complaints.dat", "rb");
    Complaint comp;
    int maxId = 0;
    if (fp != NULL) {
        while (fread(&comp, sizeof(Complaint), 1, fp)) {
            if (comp.id > maxId) maxId = comp.id;
        }
        fclose(fp);
    }
    return maxId + 1;
}

void addCriminal() {
    Criminal criminal;
    criminal.id = getNextCriminalId();

    printf("Enter Criminal Name: ");
    scanf(" %99[^\n]", criminal.name);
    printf("Enter Crime Type: ");
    scanf(" %49[^\n]", criminal.crime_type);
    printf("Enter Date (dd/mm/yyyy): ");
    scanf(" %19s", criminal.date);
    printf("Enter Punishment Period: ");
    scanf(" %19[^\n]", criminal.punishment_period);

    FILE *fp = fopen("criminals.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&criminal, sizeof(Criminal), 1, fp);
    fclose(fp);
    printf("Criminal added successfully with ID %d\n", criminal.id);
}

void displayAllCriminals() {
    FILE *fp = fopen("criminals.dat", "rb");
    if (fp == NULL) {
        printf("No criminal records found.\n");
        return;
    }

    Criminal c;
    printf("\n--- All Criminals ---\n");
    while (fread(&c, sizeof(Criminal), 1, fp)) {
        printf("ID: %d\n", c.id);
        printf("Name: %s\n", c.name);
        printf("Crime Type: %s\n", c.crime_type);
        printf("Date: %s\n", c.date);
        printf("Punishment: %s\n", c.punishment_period);
        printf("-------------------\n");
    }
    fclose(fp);
}

void searchCriminal() {
    int searchId;
    printf("Enter Criminal ID to search: ");
    scanf("%d", &searchId);
    getchar();

    FILE *fp = fopen("criminals.dat", "rb");
    if (fp == NULL) {
        printf("No criminal records found.\n");
        return;
    }

    Criminal c;
    int found = 0;
    while (fread(&c, sizeof(Criminal), 1, fp)) {
        if (c.id == searchId) {
            found = 1;
            printf("\nCriminal Found:\n");
            printf("ID: %d\n", c.id);
            printf("Name: %s\n", c.name);
            printf("Crime Type: %s\n", c.crime_type);
            printf("Date: %s\n", c.date);
            printf("Punishment: %s\n", c.punishment_period);
            break;
        }
    }
    fclose(fp);
    if (!found) printf("Criminal with ID %d not found.\n", searchId);
}

void addComplaint() {
    Complaint complaint;
    complaint.id = getNextComplaintId();
    strcpy(complaint.status, "Pending");

    printf("Enter Complainant Name: ");
    scanf(" %99[^\n]", complaint.complainant_name);
    printf("Enter Incident Details: ");
    scanf(" %499[^\n]", complaint.incident_details);
    printf("Enter Date (dd/mm/yyyy): ");
    scanf(" %19s", complaint.date);
    printf("Enter Police Station: ");
    scanf(" %99[^\n]", complaint.police_station);

    FILE *fp = fopen("complaints.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&complaint, sizeof(Complaint), 1, fp);
    fclose(fp);
    printf("Complaint filed successfully with ID %d\n", complaint.id);
}

void displayPendingComplaints() {
    FILE *fp = fopen("complaints.dat", "rb");
    if (fp == NULL) {
        printf("No complaints found.\n");
        return;
    }

    Complaint comp;
    int found = 0;
    printf("\n--- Pending Complaints ---\n");
    while (fread(&comp, sizeof(Complaint), 1, fp)) {
        if (strcmp(comp.status, "Pending") == 0) {
            found = 1;
            printf("ID: %d\n", comp.id);
            printf("Complainant: %s\n", comp.complainant_name);
            printf("Incident: %s\n", comp.incident_details);
            printf("Date: %s\n", comp.date);
            printf("Police Station: %s\n", comp.police_station);
            printf("-------------------\n");
        }
    }
    fclose(fp);
    if (!found) printf("No pending complaints.\n");
}

void convertComplaintToFIR() {
    FILE *fp = fopen("complaints.dat", "r+b");
    if (fp == NULL) {
        printf("No complaints found.\n");
        return;
    }

    Complaint complaint;
    int found = 0;
    int complaintId;

    printf("Enter Complaint ID to convert to FIR: ");
    scanf("%d", &complaintId);
    getchar();

    while (fread(&complaint, sizeof(Complaint), 1, fp)) {
        if (complaint.id == complaintId && strcmp(complaint.status, "Pending") == 0) {
            found = 1;
            strcpy(complaint.status, "Converted");
            fseek(fp, -sizeof(Complaint), SEEK_CUR);
            fwrite(&complaint, sizeof(Complaint), 1, fp);
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Complaint not found or already converted.\n");
        return;
    }

    Criminal criminal;
    printf("\nEnter Criminal Details:\n");
    criminal.id = getNextCriminalId();
    printf("Name: ");
    scanf(" %99[^\n]", criminal.name);
    printf("Crime Type: ");
    scanf(" %49[^\n]", criminal.crime_type);
    printf("Date (dd/mm/yyyy): ");
    scanf(" %19s", criminal.date);
    printf("Punishment Period: ");
    scanf(" %19[^\n]", criminal.punishment_period);

    FILE *criminalFile = fopen("criminals.dat", "ab");
    fwrite(&criminal, sizeof(Criminal), 1, criminalFile);
    fclose(criminalFile);

    printf("Complaint converted to FIR and Criminal added successfully.\n");
}