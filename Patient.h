#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <fstream>
#include <windows.h>

// Константы для максимальной длины полей
const int MAX_NAME_LENGTH = 50;
const int MAX_ADDRESS_LENGTH = 100;

// Структура для хранения данных пациента
struct Patient
{
    char lastName[MAX_NAME_LENGTH];      // Фамилия
    char firstName[MAX_NAME_LENGTH];     // Имя
    char patronymic[MAX_NAME_LENGTH];    // Отчество
    char address[MAX_ADDRESS_LENGTH];    // Домашний адрес
    int medicalCardNumber;               // Номер медицинской карты
    long long insuranceNumber;           // Номер страхового полиса
};

// Прототипы функций
Patient* InputPatient();
void WritePatient(std::ofstream& file, const Patient& patient);
bool ReadPatient(std::ifstream& file, Patient& patient);
bool CreateInitialFile(const char* filename);
void PrintFile(const char* filename);
bool DeletePatient(const char* filename, int medicalCardNumber);
bool AddTwoPatientsToStart(const char* filename);

#endif // PATIENT_H