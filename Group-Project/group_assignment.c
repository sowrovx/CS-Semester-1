/*
 * Title: Monthly Stipend Tracker for Scholarship Students
 * Course: CCC1123 - Problem Solving and Programming Fundamental
 * Project: Mini Programming Project
 * Description: Command-line application to help scholarship students track stipend spending
 * Features: Input collection, expense calculation, balance tracking, file storage
 * Date: January 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- GLOBAL CONSTANTS ---------- */
#define MAX_RECORDS 12      /* Maximum monthly records (1 year) */
#define MAX_NAME_LENGTH 50  /* Maximum student name length */
#define FILENAME "stipend_records.txt" /* File to store records */

/* ---------- STRUCTURE DEFINITION ---------- */
typedef struct {
    char month[20];         /* Month name (e.g., "January") */
    float stipend;          /* Monthly stipend amount */
    float food_expenses;    /* Food expenses */
    float other_expenses;   /* Other essential expenses */
    float total_expenses;   /* Calculated total expenses */
    float balance;          /* Remaining balance */
    float food_percentage;  /* Percentage spent on food */
    float other_percentage; /* Percentage spent on other expenses */
} StipendRecord;

/* ---------- FUNCTION PROTOTYPES ---------- */
void displayMenu();
void inputData(StipendRecord records[], int *count);
void calculateExpenses(StipendRecord *record);
void displaySummary(StipendRecord records[], int count);
void saveToFile(StipendRecord records[], int count);
void loadFromFile(StipendRecord records[], int *count);
void displayMonthlyReport(StipendRecord records[], int count);
float calculateTotalStipend(StipendRecord records[], int count);
float calculateAverageExpenses(StipendRecord records[], int count);

/* ---------- MAIN FUNCTION ---------- */
int main() {
    StipendRecord records[MAX_RECORDS]; /* Array to store records */
    int recordCount = 0;                 /* Number of records stored */
    int choice;
    
    /* Load existing records from file */
    loadFromFile(records, &recordCount);
    
    /* Welcome message */
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║    MONTHLY STIPEND TRACKER FOR SCHOLARSHIP STUDENTS  ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    
    /* Main program loop */
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (recordCount < MAX_RECORDS) {
                    inputData(records, &recordCount);
                } else {
                    printf("\n⚠️ Maximum records (%d) reached!\n", MAX_RECORDS);
                }
                break;
                
            case 2:
                if (recordCount > 0) {
                    displaySummary(records, recordCount);
                } else {
                    printf("\n⚠️ No records available. Please add records first.\n");
                }
                break;
                
            case 3:
                if (recordCount > 0) {
                    displayMonthlyReport(records, recordCount);
                } else {
                    printf("\n⚠️ No records available. Please add records first.\n");
                }
                break;
                
            case 4:
                if (recordCount > 0) {
                    saveToFile(records, recordCount);
                } else {
                    printf("\n⚠️ No records to save.\n");
                }
                break;
                
            case 5:
                printf("\n📊 Overall Statistics:\n");
                printf("=======================\n");
                if (recordCount > 0) {
                    printf("Total Months Tracked: %d\n", recordCount);
                    printf("Total Stipend Received: RM %.2f\n", calculateTotalStipend(records, recordCount));
                    printf("Average Monthly Expenses: RM %.2f\n", calculateAverageExpenses(records, recordCount));
                } else {
                    printf("No data available for statistics.\n");
                }
                break;
                
            case 6:
                printf("\n✅ Program exited. Your data has been auto-saved.\n");
                saveToFile(records, recordCount); /* Auto-save on exit */
                break;
                
            default:
                printf("\n❌ Invalid choice! Please enter 1-6.\n");
        }
        
    } while (choice != 6);
    
    return 0;
}

/* ---------- FUNCTION DEFINITIONS ---------- */

/* Display main menu */
void displayMenu() {
    printf("\n──────────────────────────────────────────\n");
    printf("              MAIN MENU                   \n");
    printf("──────────────────────────────────────────\n");
    printf("1. 📝 Add Monthly Stipend Record\n");
    printf("2. 📋 View Expense Summary\n");
    printf("3. 📈 View Monthly Report\n");
    printf("4. 💾 Save Records to File\n");
    printf("5. 📊 View Statistics\n");
    printf("6. 🚪 Exit Program\n");
    printf("──────────────────────────────────────────\n");
}

/* Input data for a new monthly record */
void inputData(StipendRecord records[], int *count) {
    StipendRecord newRecord;
    
    printf("\n─────── ADD MONTHLY RECORD ───────\n");
    
    /* Input month */
    printf("Enter month (e.g., January): ");
    scanf("%s", newRecord.month);
    
    /* Input stipend amount */
    printf("Enter monthly stipend amount (RM): ");
    scanf("%f", &newRecord.stipend);
    
    /* Input food expenses */
    printf("Enter food expenses (RM): ");
    scanf("%f", &newRecord.food_expenses);
    
    /* Input other expenses */
    printf("Enter other essential expenses (RM): ");
    scanf("%f", &newRecord.other_expenses);
    
    /* Calculate all values */
    calculateExpenses(&newRecord);
    
    /* Add to records array */
    records[*count] = newRecord;
    (*count)++;
    
    printf("\n✅ Record for %s added successfully!\n", newRecord.month);
}

/* Calculate expenses, balance, and percentages */
void calculateExpenses(StipendRecord *record) {
    /* Calculate total expenses */
    record->total_expenses = record->food_expenses + record->other_expenses;
    
    /* Calculate balance */
    record->balance = record->stipend - record->total_expenses;
    
    /* Calculate percentages */
    if (record->total_expenses > 0) {
        record->food_percentage = (record->food_expenses / record->total_expenses) * 100;
        record->other_percentage = (record->other_expenses / record->total_expenses) * 100;
    } else {
        record->food_percentage = 0;
        record->other_percentage = 0;
    }
}

/* Display summary of all records */
void displaySummary(StipendRecord records[], int count) {
    printf("\n════════════════════════════════════════════════════════════════════════════════════\n");
    printf("                                EXPENSE SUMMARY                                      \n");
    printf("════════════════════════════════════════════════════════════════════════════════════\n");
    printf("Month       Stipend    Food      Other     Total     Balance   Food%%   Other%%\n");
    printf("──────────────────────────────────────────────────────────────────────────────────\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10s  %7.2f  %7.2f  %7.2f  %7.2f  %7.2f  %5.1f%%  %6.1f%%\n",
               records[i].month,
               records[i].stipend,
               records[i].food_expenses,
               records[i].other_expenses,
               records[i].total_expenses,
               records[i].balance,
               records[i].food_percentage,
               records[i].other_percentage);
    }
    printf("════════════════════════════════════════════════════════════════════════════════════\n");
}

/* Save records to file */
void saveToFile(StipendRecord records[], int count) {
    FILE *file = fopen(FILENAME, "w");
    
    if (file == NULL) {
        printf("\n❌ Error: Cannot open file for writing.\n");
        return;
    }
    
    /* Write each record to file */
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
                records[i].month,
                records[i].stipend,
                records[i].food_expenses,
                records[i].other_expenses,
                records[i].total_expenses,
                records[i].balance,
                records[i].food_percentage,
                records[i].other_percentage);
    }
    
    fclose(file);
    printf("\n✅ %d records saved to '%s' successfully.\n", count, FILENAME);
}

/* Load records from file */
void loadFromFile(StipendRecord records[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    
    if (file == NULL) {
        /* File doesn't exist yet - that's okay */
        *count = 0;
        return;
    }
    
    *count = 0;
    
    /* Read records until EOF or max records reached */
    while (*count < MAX_RECORDS && 
           fscanf(file, "%s %f %f %f %f %f %f %f",
                  records[*count].month,
                  &records[*count].stipend,
                  &records[*count].food_expenses,
                  &records[*count].other_expenses,
                  &records[*count].total_expenses,
                  &records[*count].balance,
                  &records[*count].food_percentage,
                  &records[*count].other_percentage) == 8) {
        (*count)++;
    }
    
    fclose(file);
    
    if (*count > 0) {
        printf("\n📂 Loaded %d records from file.\n", *count);
    }
}

/* Display detailed monthly report */
void displayMonthlyReport(StipendRecord records[], int count) {
    int monthChoice;
    
    printf("\n─────── MONTHLY REPORT ───────\n");
    printf("Select month (1-%d): ", count);
    scanf("%d", &monthChoice);
    
    if (monthChoice < 1 || monthChoice > count) {
        printf("\n❌ Invalid month selection.\n");
        return;
    }
    
    int index = monthChoice - 1;
    StipendRecord *r = &records[index];
    
    printf("\n════════════════════════════════════════════════════\n");
    printf("           MONTHLY REPORT FOR %s                    \n", r->month);
    printf("════════════════════════════════════════════════════\n");
    printf("Monthly Stipend:      RM %10.2f\n", r->stipend);
    printf("Food Expenses:        RM %10.2f (%5.1f%%)\n", r->food_expenses, r->food_percentage);
    printf("Other Expenses:       RM %10.2f (%5.1f%%)\n", r->other_expenses, r->other_percentage);
    printf("────────────────────────────────────────────────────\n");
    printf("Total Expenses:       RM %10.2f\n", r->total_expenses);
    printf("Remaining Balance:    RM %10.2f\n", r->balance);
    printf("════════════════════════════════════════════════════\n");
    
    /* Check for overspending */
    if (r->balance < 0) {
        printf("\n⚠️  WARNING: You have overspent by RM %.2f this month!\n", -r->balance);
    } else if (r->balance < (r->stipend * 0.2)) {
        printf("\n⚠️  NOTE: You have less than 20%% of stipend remaining.\n");
    } else {
        printf("\n✅ Good job! You are within budget.\n");
    }
}

/* Calculate total stipend received */
float calculateTotalStipend(StipendRecord records[], int count) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += records[i].stipend;
    }
    return total;
}

/* Calculate average monthly expenses */
float calculateAverageExpenses(StipendRecord records[], int count) {
    if (count == 0) return 0;
    
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += records[i].total_expenses;
    }
    return total / count;
}