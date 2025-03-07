#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Структура для хранения данных пациента
struct Patient
{
    string lastName;         // Фамилия
    string firstName;        // Имя
    string patronymic;       // Отчество
    string address;          // Домашний адрес
    int medicalCardNumber{}; // Номер медицинской карты
    long long insuranceNumber{}; // Номер страхового полиса
};




// Прототипы функций
Patient* InputPatient();
void WritePatient(ofstream& file, const Patient& patient);
bool ReadPatient(ifstream& file, Patient& patient);
bool CreateInitialFile(const string& filename);
void PrintFile(const string& filename);
bool DeletePatient(const string& filename, int medicalCardNumber);
bool AddTwoPatientsToStart(const string& filename);

#endif // PATIENT_H