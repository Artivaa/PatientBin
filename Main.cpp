#include "Patient.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const char* filename = "patients.dat";

    // Создание файла с начальными данными
    if (!CreateInitialFile(filename))
    {
        return 1;
    }
    PrintFile(filename);

    // Удаление пациента по номеру медицинской карты
    int cardToDelete;
    std::cout << "\nВведите номер медицинской карты для удаления: ";
    std::cin >> cardToDelete;

    if (DeletePatient(filename, cardToDelete))
    {
        std::cout << "Пациент успешно удален\n";
    }
    else
    {
        std::cout << "Пациент с таким номером карты не найден\n";
    }
    PrintFile(filename);

    // Добавление двух новых пациентов в начало
    if (AddTwoPatientsToStart(filename))
    {
        std::cout << "Два пациента успешно добавлены в начало файла\n";
    }
    PrintFile(filename);

    return 0;
}