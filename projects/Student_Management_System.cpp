
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;

void menu();
void view();
void new_rec();
void update();
void search();
void delete_rec();

// Structure for students
struct Students
{
    char name[100];
    int rollno;
    char class_name[50];
    char mobile[50];
    char batch[50];
};

// Main
int main()
{
    menu();
    cout << "Press Any Key To continue...";
    getch();
    return 0;
}

// Function Definitions
void menu()
{
    system("cls");

    int input;

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- MENU -->  \n";
    cout << "\n  1. View Record\n";
    cout << "  2. Create New Record\n";
    cout << "  3. Update Record\n";
    cout << "  4. Search Record\n";
    cout << "  5. Delete Record\n";
    cout << "  6. Close Menu\n";

    cout << "\n\nEnter Number for respective tasks...\t";
    cin >> input;

    switch (input)
    {
    case 1:
        view();
        break;
    case 2:
        new_rec();
        break;
    case 3:
        update();
        break;
    case 4:
        search();
        break;
    case 5:
        delete_rec();
        break;
    case 6:
        exit(0);
    default:
        cout << "\nInvalid Input :(\n";
        break;
    }
}

void new_rec()
{
    system("cls");

    Students *stu;
    int n;

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- ADDING RECORDS -->  \n\n";
    cout << "How Many Student Records You Want to Enter? ";
    cin >> n;

    stu = (Students *)calloc(n, sizeof(Students));

    FILE *ptr = fopen("record.txt", "w");
    if (ptr == NULL)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        system("cls");

        cout << "\n\nEnter " << (i + 1) << " Student's Data: \n";

        cout << "\nEnter Roll No.: ";
        cin >> stu[i].rollno;
        cin.ignore();

        cout << "\nEnter Name: ";
        cin.getline(stu[i].name, 100);

        cout << "\nEnter Mobile No.: ";
        cin.getline(stu[i].mobile, 100);
        // cin >> stu[i].mobile;

        cout << "\nEnter Class: ";
        cin >> stu[i].class_name;

        cout << "\nEnter Batch: ";
        cin >> stu[i].batch;

        fwrite(&stu[i], sizeof(Students), 1, ptr);
    }

    fclose(ptr);

    cout << "Press Any Key to Return to main menu...";
    getch();
    menu();
}

void view()
{
    system("cls");

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- VIEWING RECORDS -->  \n\n";
    cout << "\n      Roll No.          Name                          Mobile no.        Class      Batch\n";
    cout << "  ----------------------------------------------------------------------------------------------\n";

    Students stu;
    FILE *ptr = fopen("record.txt", "r");

    if (ptr == NULL)
    {
        cout << "No Record Found..." << endl;
        cout << "\n\n\nPress any key to Return to main menu... ";
        getch();
        menu();
    }

    while (fread(&stu, sizeof(Students), 1, ptr) != 0)
    {
        cout << "\t";
        cout << left << setw(15) << stu.rollno;
        cout << left << setw(30) << stu.name;
        cout << left << setw(20) << stu.mobile;
        cout << left << setw(11) << stu.class_name;
        cout << left << setw(10) << stu.batch << endl;
    }

    fclose(ptr);

    cout << "\n\n\nPress any key to Return to main menu... ";
    getch();
    menu();
}

void update()
{
    system("cls");

    Students *stu;
    int n;

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- UPDATING EXISTING RECORDS -->  \n\n";
    cout << "How Many Student Records You Want to Enter? ";
    cin >> n;

    stu = (Students *)calloc(n, sizeof(Students));

    FILE *ptr = fopen("record.txt", "a");

    for (int i = 0; i < n; i++)
    {
        system("cls");

        cout << "\n\nEnter " << (i + 1) << " Student's Data: \n";

        cout << "\nEnter Roll No.: ";
        cin >> stu[i].rollno;
        cin.ignore();

        cout << "\nEnter Name: ";
        cin.getline(stu[i].name, 100);

        cout << "\nEnter Mobile No.: ";
        cin.getline(stu[i].mobile, 100);
        // cin >> stu[i].mobile;

        cout << "\nEnter Class: ";
        cin >> stu[i].class_name;

        cout << "\nEnter Batch: ";
        cin >> stu[i].batch;

        fwrite(&stu[i], sizeof(Students), 1, ptr);
    }

    fclose(ptr);

    cout << "Press Any Key to Return to main menu...";
    getch();
    menu();
}

void search()
{
    system("cls");

    Students stu;
    int rollno;

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- SEARCHING EXISTING RECORD -->  \n\n";

    FILE *ptr = fopen("record.txt", "r");

    if (ptr == NULL)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    cout << "\n\nEnter Student's rollno to search: ";
    cin >> rollno;

    bool found = false;

    while (fread(&stu, sizeof(Students), 1, ptr) != 0)
    {
        if (rollno == stu.rollno)
        {
            found = true;
            cout << "\n      Roll No.          Name                          Mobile no.        Class      Batch\n";
            cout << "  ----------------------------------------------------------------------------------------------\n";
            cout << "\t";
            cout << left << setw(15) << stu.rollno;
            cout << left << setw(30) << stu.name;
            cout << left << setw(20) << stu.mobile;
            cout << left << setw(11) << stu.class_name;
            cout << left << setw(10) << stu.batch << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "\nRecord Not Found\n";
    }

    fclose(ptr);

    cout << "\n\nPress Any Key to Return to main menu...";
    getch();
    menu();
}

void delete_rec()
{
    system("cls");

    Students stu;
    int rollno;

    cout << "\t\t\t STUDENT MANAGEMENT SYSTEM";

    cout << "\n\n   <-- DELETING EXISTING RECORD -->  \n\n";

    FILE *ptr = fopen("record.txt", "r");
    FILE *ptr1 = fopen("record1.txt", "w");

    if (ptr == NULL || ptr1 == NULL)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    cout << "\n\nEnter Student's rollno to delete: ";
    cin >> rollno;

    while (fread(&stu, sizeof(Students), 1, ptr) != 0)
    {
        if (rollno != stu.rollno)
        {
            fwrite(&stu, sizeof(Students), 1, ptr1);
        }
    }

    fclose(ptr);
    fclose(ptr1);

    remove("record.txt");
    rename("record1.txt", "record.txt");

    cout << "Press Any Key to Return to main menu...";
    getch();
    menu();
}