#include "Patient.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
 
    const string filename = "patients.dat";

    // Создание файла с начальными данными
    if (!CreateInitialFile(filename))
    {
        return 1;
    }
    PrintFile(filename);

    // Удаление пациента по номеру медицинской карты
    int cardToDelete;
    cout << "\nВведите номер медицинской карты для удаления: ";
    cin >> cardToDelete;

    if (DeletePatient(filename, cardToDelete))
    {
        cout << "Пациент успешно удален\n";
    }
    else
    {
        cout << "Пациент с таким номером карты не найден\n";
    }
    PrintFile(filename);

    // Добавление двух новых пациентов в начало
    if (AddTwoPatientsToStart(filename))
    {
        cout << "Два пациента успешно добавлены в начало файла\n";
    }
    PrintFile(filename);

    return 0;
}