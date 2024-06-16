#include <stdio.h> // Операції введення та виведення, оголошення функцій і типів
#include <iostream> // Введення та виведення тексту
#include <fstream> // Файлове введення та виведення 
#include <string> // Взаємодія з рядком
#include <cctype> // Класифікація тексту
#include <windows.h> // Затримка часу, локалізація та шифрування

// Максимальна дозволена кількість символів в імені та номеру телефону
const int MAX_IMYA = 50;
const int MAX_PHONES = 15;

struct Contact
{
	std::string name; // Введення імені
	std::string phone; // Введення номеру телефону

	Contact()
	{
		name = "";
		phone = "";
	}
	Contact(const std::string& n, const std::string& p) {
		name = n.substr(0, MAX_IMYA);  // Обмеження на довжину імені
		phone = p.substr(0, MAX_PHONES);  // Обмеження на довжину номеру телефону
	}

};

// Назва файлу телефонного довідника
const std::string TELEFONNIYDOVIDNIK = "dovidniktext.txt";

// Читання файлу
// kilkist - Кількість людей
void Chitannya(Contact ludi[], int& kilkist)
{
	std::ifstream file;
	file.open(TELEFONNIYDOVIDNIK.c_str(), std::ios::app); // відкриття файлу для запису
	if (!file.is_open())
	{
		std::cout << "Не вдалося вiдкрити файл. " << TELEFONNIYDOVIDNIK << std::endl; // повідомлення про помилку відкриття файлу
		return;
	}

	int i = 0;
	while (getline(file, ludi[i].name) && getline(file, ludi[i].phone))
	{
		i++;
		if (i >= MAX_IMYA) break; // Обмеження на довжину імені
	}

	kilkist = i;
	file.close();
}

// Запис файлу
// contact - людина про яку додається інформація
void Zapisfile(Contact contact)
{
	std::ofstream file;
	file.open(TELEFONNIYDOVIDNIK.c_str(), std::ios::app);
	if (!file.is_open())
	{
		std::cout << "Не вдалося вiдкрити файл. " << TELEFONNIYDOVIDNIK << std::endl; // повідомлення про помилку відкриття файлу
		return;
	}

	file << contact.name << std::endl;
	file << contact.phone << std::endl;
	file.close();
}

// Зберігає всіх людей для запису файлу
void Zberezhennya(const Contact ludi[], int kilkist)
{
	std::ofstream first;
	first.open(TELEFONNIYDOVIDNIK.c_str());

	for (int i = 0; i < kilkist; i++) {
		first << ludi[i].name << std::endl;
		first << ludi[i].phone << std::endl;
	}
	first.close();
}

// Додавання контакту
void Dodati(Contact ludi[], int& kilkist)
{
	Contact contact;

	std::cout << "\nВведiть iм'я: ";
	getline(std::cin, contact.name);
	contact.name = contact.name.substr(0, MAX_IMYA);

	std::string phone;
	bool Nomer = false; // Логіка

	while (!Nomer) {
		std::cout << "Введiть номер телефону: ";
		getline(std::cin, phone);
		phone = phone.substr(0, MAX_PHONES);

		Nomer = true;

		// Перевірка, чи містить номер лише цифри та знак +
		for (char c : phone) {
			if (!isdigit(c) && c != '+') {
				Nomer = false;
				std::cout << "Неправильний ввід номеру, для вводу використовуйте тільки цифри.\n";
				break;
			}
		}
	}

	contact.phone = phone;

	ludi[kilkist] = contact; // Додати новий контакт до масиву
	kilkist++;

	Zapisfile(contact);
	system("cls");
	std::cout << "\nКонтакт додано. " << std::endl;
}

//Список контактів
void Spisok(const Contact ludi[], int kilkist)
{
	system("cls");
	std::cout << "--------------------\n";
	std::cout << "Список контактiв:\n";
	std::cout << "--------------------\n";
	for (int i = 0; i < kilkist; i++)
		std::cout << i + 1 << ". " << ludi[i].name << " — " << ludi[i].phone << std::endl;
}

// Видалення контакту
void Vydalennya(Contact ludi[], int& kilkist)
{
	std::string vidalennya;
	std::cout << "Введiть iм'я контакту який потрiбно видалити: ";
	getline(std::cin, vidalennya);

	int nNaVidalennya = -1;
	for (int i = 0; i < kilkist; ++i)
	{
		if (ludi[i].name == vidalennya)
		{
			nNaVidalennya = i;
			break;
		}
	}

	if (nNaVidalennya != -1)
	{
		for (int i = nNaVidalennya; i < kilkist - 1; ++i)
		{
			ludi[i] = ludi[i + 1];
		}

		kilkist--;
		Zberezhennya(ludi, kilkist);
		system("cls");
		std::cout << "Контакт успiшно видалено.\n" << std::endl;
	}
	else
	{
		system("cls");
		std::cout << "Контакт не знайдено.\n" << std::endl;
	}
}

// Зміна номера контакту
void ZminituNomer(Contact ludi[], int kilkist)
{
	Contact contact;
	int count;

	std::cout << "Напишiть iм'я контакту: ";
	getline(std::cin, contact.name);
	std::cout << "--------------------\n";

	for (count = 0; count < kilkist; count++)
	{
		if (ludi[count].name == (contact.name))
		{
			std::cout << std::endl << ludi[count].name << std::endl;
			std::cout << "Поточний номер: " << ludi[count].phone;
			std::cout << "\nНовий номер: ";
			getline(std::cin, ludi[count].phone);
			ludi[count].phone = ludi[count].phone.substr(0, MAX_PHONES);
			Zberezhennya(ludi, kilkist);
			system("cls");
			std::cout << "--------------------\n";
			std::cout << "Контакт збережено.\n";

			return;

		}

	}

	if (count = kilkist)
		system("cls");
	std::cout << "--------------------\n";
	std::cout << "Контакт не знайдено.\n";
}

// Меню довідника
void zapProg(Contact ludi[], int& kilkist) {
	char choice;
	do {
		std::cout << "--------------------\n";
		std::cout << "\nМеню довiдника\n";
		std::cout << "--------------------\n";
		std::cout << "1. Додати контакт\n";
		std::cout << "2. Список контактiв\n";
		std::cout << "3. Змiнити номер контакту\n";
		std::cout << "4. Видалити контакт\n";
		std::cout << "5. Повернення в головне меню\n";
		std::cout << "--------------------\n";
		std::cout << "Введiть номер дiї: ";
		std::cin >> choice;
		std::cin.get();

		choice = toupper(choice); // Ігнорування регістру

		switch (choice) {
		case '1': Dodati(ludi, kilkist); break; // Додати контакт
		case '2': Spisok(ludi, kilkist); break; // Список контактів
		case '3': ZminituNomer(ludi, kilkist); break; // Змінити номер
		case '4': Vydalennya(ludi, kilkist); break; // Видалити контакт
		case '5': system("cls"); break; // Повернення до головного меню
		default: system("cls"); std::cout << "Немає такого пункту!\n"; break; // Повідомлення про неправильне введення номера пункту
		}
	} while (choice != '5');
}

// Головне меню
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Contact ludi[MAX_IMYA];
	int kilkist;
	// Читання файлу для роботи
	Chitannya(ludi, kilkist);

	char main_choice; // Основний вибір
	char run_choice; // Вибір в інструкції, запуск програми

	do {
		std::cout << "--------------------\n";
		std::cout << "\nГоловне меню\n";
		std::cout << "--------------------\n";
		std::cout << "1. Запуск програми\n";
		std::cout << "2. Iнструкцiя\n";
		std::cout << "3. Закрити програму\n";
		std::cout << "---------------------\n";
		std::cout << "Введiть номер дiї: ";
		std::cin >> main_choice;
		std::cin.get();

		switch (main_choice) {
		case '1':
			system("cls");
			zapProg(ludi, kilkist);
			break;
		case '2':
			std::cout << "--------------------\n";
			std::cout << "Телефонний довiдник - це программа, яка дозволяє зручно зберiгати, переглядати та редагувати контакти.\n";
			std::cout << "Щоб користуватися довiдником, потрібно ввести номер пункту який відображений вiдповiдно до потрiбної дiї.\n";
			std::cout << "--------------------\n";
			Sleep(2000);
			std::cout << "Запустити програму? (y/n): ";
			std::cin >> run_choice;
			std::cin.get();
			if (toupper(run_choice) == 'Y') {
				system("cls");
				zapProg(ludi, kilkist);
			}
			else if (toupper(run_choice) == 'N') {
				system("cls");
				break;
			}
			else {
				system("cls");
				std::cout << "Введена неправильна літера. Спробуйте ще раз.\n";
			}
			break;
		case '3':
			std::cout << "Вихiд з програми.\n";
			break;
		default:
			system("cls");
			std::cout << "--------------------\n";
			std::cout << "В меню немає такого пункту!\n";
			break;
		}
	} while (main_choice != '3');
	return 0;
}
