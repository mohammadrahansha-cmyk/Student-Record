#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3, total;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter 3 Subject Marks: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Marks: %.2f %.2f %.2f\n",
               s.roll, s.name, s.m1, s.m2, s.m3);
    }

    fclose(fp);
}

void rankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100];
    int i = 0, j, n = 0;

    while (fread(&s[n], sizeof(s[n]), 1, fp)) {
        s[n].total = s[n].m1 + s[n].m2 + s[n].m3;
        n++;
    }

    fclose(fp);

    // Sorting (Descending)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i].total < s[j].total) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < n; i++) {
        printf("Rank %d: %s (Total = %.2f)\n",
               i + 1, s[i].name, s[i].total);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Student\n2. Display Students\n3. Rank List\n4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}
