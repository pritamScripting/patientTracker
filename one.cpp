#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Patient
{
private:
    char name[20];
    int age;
    char gender[20];
    int phone_number;
    char disease[20];
    char medicines_given[20];
    char notes[50];

public:
    void searchPatientPrescription(string patientName)
    {
        ifstream fin;
        fin.open("patients.txt", ios::in | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (patientName == name)
            {
                viewPrescription();
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }

    // to initialize the object
    void enterData()
    {
        cout << "Enter the first name of the patient: ";
        // cin.ignore();
        cin.getline(name, 19);
        cout << "Enter the patient age: ";
        cin >> age;
        cout << "Enter the patient gender: ";
        cin.ignore();
        cin.getline(gender, 19);
        cout << "Enter the patient phone number: ";
        cin >> phone_number;
        cout << "Enter the disease, the patient has been diagnosed: ";
        cin.ignore();
        cin.getline(disease, 19);
        cout << "Enter the medicines given to the patient: ";
        // cin.ignore();
        cin.getline(medicines_given, 19);
        cout << "Enter the advice note, to be given to the patient: ";
        // cin.ignore();
        cin.getline(notes, 49);
    }

    // login function
    bool login(string patient_name)
    {
        int success = 0;
        ifstream fin;
        fin.open("patients.txt", ios::in | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (patient_name == name)
            {
                success = 1;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();

        if (success == 1)
        {
            cout << "Login successful" << endl;
            return true;
        }
        else
        {
            cout << "Wrong credential entered" << endl;
            return false;
        }
    }

    void viewPrescription()
    {
        cout << "The name of the patient is: " << name << endl;
        cout << "The age of the patient is: " << age << endl;
        cout << "The gender of the patient is: " << gender << endl;
        cout << "The phone number of the patient is: " << phone_number << endl;
        cout << "The disease that has been diagoned is: " << disease << endl;
        cout << "The medicines given are: " << medicines_given << endl;
        cout << "The medical advice given are: " << notes << endl;
    }

    // logout function
    void logout()
    {
        int timer = 0;
        if (timer == 0)
            cout << "Logout successful" << endl;
        else
            cout << "Timeout" << endl;
    }

    void searchAllPatients()
    {
        ifstream fin;
        fin.open("patients.txt", ios::in | ios::binary);
        if (!fin)
            cout << "File not open" << endl;
        else
        {
            fin.read((char *)this, sizeof(*this));
            while (!fin.eof())
            {
                viewPrescription();
                fin.read((char *)this, sizeof(*this));
            }
            fin.close();
        }
    }
};

// we will assume only one doctor is present in the clinic
class Doctor
{
public:
    // enterPatientData;
    void enterPatientData()
    {
        Patient p1;
        p1.enterData(); // initialize the patient

        // now store the patient in the file
        ofstream fout;
        fout.open("patients.txt", ios::app | ios::binary);
        fout.write((char *)&p1, sizeof(p1));
        fout.close();
    }

    void viewAllPatients()
    {
        Patient p;
        p.searchAllPatients();
    }

    void viewPresecriptionOfPatient(string patient_name)
    {
        Patient p;
        p.searchPatientPrescription(patient_name);
    }
};

int main()
{
    Doctor d1; // assume only one doctor is present in the clinic
    // d1.enterPatientData(); // patient pritam entry
    // d1.enterPatientData(); // patient akshay entry
    // d1.viewAllPatients();
    // d1.viewPresecriptionOfPatient("pritam");

    Patient p;
    string patient_name;
    cout << "Enter the first name of patient to be searched: ";
    cin >> patient_name;
    bool patientFound = p.login(patient_name);
    if (patientFound)
    {
        p.searchPatientPrescription(patient_name);
        p.logout();
    }
    else
    {
        cout << "Patient not found in the database" << endl;
    }
}