#include "Patient.h"

using namespace std;

// Функция ввода данных одного пациента с клавиатуры
Patient* InputPatient()
{
    Patient* patient = new Patient;

    cout << "Введите фамилию: ";
    getline(cin, patient->lastName);

    cout << "Введите имя: ";
    getline(cin, patient->firstName);

    cout << "Введите отчество: ";
    getline(cin, patient->patronymic);

    cout << "Введите домашний адрес: ";
    getline(cin, patient->address);

    cout << "Введите номер медицинской карты: ";
    cin >> patient->medicalCardNumber;
    cin.ignore(10000, '\n');

    cout << "Введите номер страхового полиса: ";
    cin >> patient->insuranceNumber;
    cin.ignore(10000, '\n');

    return patient;
}

// Вспомогательная функция для записи строки в файл
static void WriteStringToFile(ofstream& file, const string& str) {
    size_t size = str.length();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(str.c_str(), static_cast<std::streamsize>(size));
}

// Функция записи данных пациента в бинарный файл
void WritePatient(ofstream& file, const Patient& patient)
{
    WriteStringToFile(file, patient.lastName);
    WriteStringToFile(file, patient.firstName);
    WriteStringToFile(file, patient.patronymic);
    WriteStringToFile(file, patient.address);

    file.write(reinterpret_cast<const char*>(&patient.medicalCardNumber), sizeof(patient.medicalCardNumber));
    file.write(reinterpret_cast<const char*>(&patient.insuranceNumber), sizeof(patient.insuranceNumber));
}

// Вспомогательная функция для чтения строки из файла
static bool ReadStringFromFile(ifstream& file, string& str) {
    size_t size = 0;
    if (!file.read(reinterpret_cast<char*>(&size), sizeof(size))) {
        return false;
    }
    str.resize(size);
    if (size > 0) {
        file.read(str.data(), static_cast<std::streamsize>(size));
    }
    return true;
}

// Функция чтения данных пациента из бинарного файла
bool ReadPatient(ifstream& file, Patient& patient)
{
    if (!ReadStringFromFile(file, patient.lastName)) return false;
    if (!ReadStringFromFile(file, patient.firstName)) return false;
    if (!ReadStringFromFile(file, patient.patronymic)) return false;
    if (!ReadStringFromFile(file, patient.address)) return false;

    if (!file.read(reinterpret_cast<char*>(&patient.medicalCardNumber), sizeof(patient.medicalCardNumber))) return false;
    if (!file.read(reinterpret_cast<char*>(&patient.insuranceNumber), sizeof(patient.insuranceNumber))) return false;

    return true;
}

// Функция создания файла с начальными данными (3 пациента)
bool CreateInitialFile(const string& filename)
{
    ofstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Ошибка: Не удалось создать файл " << filename << endl;
        return false;
    }

    cout << "Введите данные для 3 пациентов:\n";
    for (int i = 1; i <= 3; ++i)
    {
        cout << "\nПациент " << i << ":\n";
        Patient* patient = InputPatient();
        if (patient)
        {
            WritePatient(file, *patient);
            delete patient;
        }
    }

    file.close();
    return true;
}

// Функция вывода содержимого файла на экран
void PrintFile(const string& filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Ошибка: Не удалось открыть файл " << filename << " для чтения" << endl;
        return;
    }

    cout << "\nСодержимое файла " << filename << ":\n";
    cout << "----------------------------------------\n";

    Patient patient;
    int patientCount = 0;

    while (ReadPatient(file, patient))
    {
        patientCount++;
        cout << "Пациент " << patientCount << ":\n";
        cout << "ФИО: " << patient.lastName << " "
            << patient.firstName << " "
            << patient.patronymic << endl;
        cout << "Адрес: " << patient.address << endl;
        cout << "Номер мед. карты: " << patient.medicalCardNumber << endl;
        cout << "Номер страховки: " << patient.insuranceNumber << endl;
        cout << "----------------------------------------\n";
    }

    if (patientCount == 0)
    {
        cout << "Файл пуст\n";
    }

    file.close();
}

// Функция удаления пациента по номеру медицинской карты
bool DeletePatient(const string& filename, int medicalCardNumber)
{
    string tempFilename = "temp.dat";
    ifstream inFile(filename, ios::binary);
    ofstream outFile(tempFilename, ios::binary);

    if (!inFile.is_open() || !outFile.is_open())
    {
        cerr << "Ошибка: Не удалось открыть файлы для операции удаления" << endl;
        return false;
    }

    bool found = false;
    Patient patient;

    while (ReadPatient(inFile, patient))
    {
        if (patient.medicalCardNumber != medicalCardNumber)
        {
            WritePatient(outFile, patient);
        }
        else
        {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    if (remove(filename.c_str()) != 0) {
        cerr << "Ошибка при удалении исходного файла " << filename << endl;
        return false;
    }
    if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка при переименовании временного файла в " << filename << endl;
        return false;
    }

    return found;
}

// Функция добавления двух пациентов в начало файла
bool AddTwoPatientsToStart(const string& filename)
{
    string tempFilename = "temp.dat";
    ofstream tempFile(tempFilename, ios::binary);
    if (!tempFile.is_open())
    {
        cerr << "Ошибка: Не удалось создать временный файл" << endl;
        return false;
    }

    // Ввод и запись двух новых пациентов
    cout << "\nДобавление первого пациента:\n";
    Patient* patient1 = InputPatient();
    if (patient1)
    {
        WritePatient(tempFile, *patient1);
        delete patient1;
    }

    cout << "\nДобавление второго пациента:\n";
    Patient* patient2 = InputPatient();
    if (patient2)
    {
        WritePatient(tempFile, *patient2);
        delete patient2;
    }

    // Копирование существующих данных из исходного файла
    ifstream originalFile(filename, ios::binary);
    if (originalFile.is_open())
    {
        Patient patient;
        while (ReadPatient(originalFile, patient))
        {
            WritePatient(tempFile, patient);
        }
        originalFile.close();
    }

    tempFile.close();
    if (remove(filename.c_str()) != 0) {
        cerr << "Ошибка при удалении исходного файла " << filename << endl;
        return false;
    }
    if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка при переименовании временного файла в " << filename << endl;
        return false;
    }

    return true;
}