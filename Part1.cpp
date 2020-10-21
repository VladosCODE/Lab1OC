#include <iostream>
#include <windows.h>
#include <vector>
#include <bitset>
#define ENG_ALPH 26

using namespace std;



void OutputListDisk(vector<string> b)
{
	int j = 0;
	for (vector<string>::iterator i = b.begin(); i != b.end(); i++)
		cout << ++j << ") Диск " << *i << endl;
}

void FindTypeDisk(UINT d)
{
	switch (d)
	{
	case DRIVE_CDROM:
		cout << "CD-ROM ";
		break;
	case DRIVE_RAMDISK:
		cout << "RAM";
	case DRIVE_REMOVABLE:
		cout << "Съемный";
		break;
	case DRIVE_REMOTE:
		cout << "Удаленный";
		break;
	case DRIVE_FIXED:
		cout << "Фиксированный";
		break;
	case DRIVE_UNKNOWN:
		cout << "Тип данного диска неизвестен";
		break;
	case DRIVE_NO_ROOT_DIR:
		cout << "Неверный путь";
		break;
	}
}
void AllInFoAboutDisk(LPCTSTR d)
{
	CHAR NameFileSystem[MAX_PATH + 1];
	char NameBuf[MAX_PATH + 1];
	DWORD SerialNumber, MaxLengthFile, FileSystemOptions;
	cout << "Тип диска: ";
	FindTypeDisk(GetDriveType(d));
	cout << endl;

	BOOL b = GetVolumeInformation(d, NameBuf, MAX_PATH, &SerialNumber, &MaxLengthFile, &FileSystemOptions, NameFileSystem, MAX_PATH);
	if (b) {
		cout << "Имя раздела: ";
		for (int i = 0; i < MAX_PATH; i++)
		{
			if (NameBuf[i] != '\0')
				cout << NameBuf[i];
			else
				break;
		}
		cout << endl;
		cout << "Файловая система: ";
		for (int i = 0; i < MAX_PATH; i++)
		{
			if (NameFileSystem[i] != '\0')
				cout << NameFileSystem[i];
			else
				break;
		}
		cout << endl;
		cout << "Максимальная длина файла: " << MaxLengthFile << endl;
		cout << "Опции файловой системы: " << FileSystemOptions << endl;
		cout << "Серийный номер раздела: " << SerialNumber << endl;
	}
	else
		cout << "\n Возникла ошибка: " << GetLastError << endl;
	cout << endl;

	DWORD NumberSectors, ByteInEverySector, freeCl, AllNumberCl;

	b = GetDiskFreeSpace(d, &NumberSectors, &ByteInEverySector, &freeCl, &AllNumberCl);
	if (b != false)
	{
		cout << "Количество секторов в каждом кластере: " << NumberSectors << endl;
		cout << "Количество байтов в каждом секторе: " << ByteInEverySector << endl;
		cout << "Количество свободных кластеров: " << freeCl << endl;
		cout << "Общее количество кластеров: " << AllNumberCl << endl;
		cout << "Количество доступного места " << (long double(ByteInEverySector) / 1024.0 / 1024.0 / 1024.) * freeCl * NumberSectors << " GB" << " из " << (long double(ByteInEverySector) / 1024.0 / 1024.0 / 1024.) * AllNumberCl * NumberSectors << " GB" << endl;
	}
	else cout << "\nПроизошла ошибка: " << GetLastError() << endl;

}
void ChoiceDisk(vector <string> b)
{
	unsigned int c;
	cout << "\nВыберете диск:\n" << endl;
	OutputListDisk(b);
	cin >> c;
	if (c <= b.size())
	{
		vector<string>::iterator k = b.begin();
		for (unsigned int i = 1; i != c; i++)
			k++;
		AllInFoAboutDisk(string((*k).begin(), (*k).end()).c_str());
	}
	else {
		cout << "Данный диск отсутствует";
	}
}
void BuffD(vector<string>& b, DWORD DD)
{

	int n;
	for (int i = 0; i < 26; i++)
	{
		n = ((DD >> i) & 0x00000001);
		if (n == 1)
		{
			char c = i + 65;
			b.push_back(string() + c + ":" + "\\" + "\0");
		}
	}
}
void menuCopyAndMove()
{
	cout << "1 - Копирование файла" << endl;
	cout << "2 - Перемещение файла между каталами" << endl;
	cout << "3 - Выход" << endl;
}

void CopyAndMoveFile()
{
	CHAR PathCurrentFile[MAX_PATH + 1];
	CHAR PathNewFile[MAX_PATH + 1];
	int ch;
	BOOL flag = 0;
	do {
		menuCopyAndMove();
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			cout << "Введите путь до текущего файла" << endl;
			cin >> PathCurrentFile;
			cout << "Введите путь до нового файла" << endl;
			cin >> PathNewFile;
			flag = 0;
			flag = CopyFile(PathCurrentFile, PathNewFile, FALSE);
			if (flag == 0)
				cout << "Произошла ошибка " << GetLastError() << " при копировании файла" << endl;
			else
				cout << "Файл успешно cкопирован" << endl;
			break;

		case 2:
			system("cls");
			cout << "Введите путь до текущего файла" << endl;
			cin >> PathCurrentFile;
			cout << "Введите путь до нового файла" << endl;
			cin >> PathNewFile;
			flag = 0;
			flag = MoveFile(PathCurrentFile, PathNewFile);
			if (flag == 0)
				flag = MoveFileEx(PathCurrentFile, PathNewFile, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
			if (flag == 0)
				cout << "Произошла ошибка " << GetLastError() << " при перемещении файла" << endl;
			else
				cout << "Файл успешно перемещён" << endl;
			break;
		case 3:
			system("cls");
			cout << "Выход ...\n" << endl;
			break;
		default:
			cout << "Такого пункта нет" << endl;
			break;
		}
	} while (ch == 3);
}
void ChoiceAttr()
{
	cout << "Введите номера атрибутов для установление в данный файл: " << endl;
	cout << "1 - Архивный" << endl;
	cout << "2 - Сжатый" << endl;
	cout << "3 - Зарезервирован, но не используется" << endl;
	cout << "4 - Дескриптор идентифицирует каталог" << endl;
	cout << "5 - Зашифрованный" << endl;
	cout << "6 - Скрытый" << endl;
	cout << "7 - Не имеет других установленных атрибутов" << endl;
	cout << "8 - Не будет индексирован содержащим индексы модулем обслуживания" << endl;
	cout << "9 - Данные файла были физически перемещены, чтобы сохраняться автономно" << endl;
	cout << "10 - Только для чтения" << endl;
	cout << "11 - Имеет связанную точку повторной обработки." << endl;
	cout << "12 - Разреженный" << endl;
	cout << "13 - Частично или исключительно использует  операционную систему" << endl;
	cout << "14 - Временного хранения" << endl;
	cout << "15 - Выход" << endl;
}

DWORD AttrsInfo()
{
	int ch;
	DWORD Attr = NULL;
	do {
		ChoiceAttr();
		cin >> ch;
		switch (ch)
		{
		case 1:
			Attr = Attr | FILE_ATTRIBUTE_ARCHIVE;
			break;
		case 2:
			Attr = Attr | FILE_ATTRIBUTE_COMPRESSED;
			break;
		case 3:
			Attr = Attr | FILE_ATTRIBUTE_DEVICE;
			break;
		case 4:
			Attr = Attr | FILE_ATTRIBUTE_DIRECTORY;
			break;
		case 5:
			Attr = Attr | FILE_ATTRIBUTE_ENCRYPTED;
			break;
		case 6:
			Attr = Attr | FILE_ATTRIBUTE_HIDDEN;
			break;
		case 7:
			Attr = Attr | FILE_ATTRIBUTE_NORMAL;
			break;
		case 8:
			Attr = Attr | FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
			break;
		case 9:
			Attr = Attr | FILE_ATTRIBUTE_OFFLINE;
			break;
		case 10:
			Attr = Attr | FILE_ATTRIBUTE_READONLY;
			break;
		case 11:
			Attr = Attr | FILE_ATTRIBUTE_REPARSE_POINT;
			break;
		case 12:
			Attr = Attr | FILE_ATTRIBUTE_SPARSE_FILE;
			break;
		case 13:
			Attr = Attr | FILE_ATTRIBUTE_SYSTEM;
			break;
		case 14:
			Attr = Attr | FILE_ATTRIBUTE_TEMPORARY;
			break;
		case 15:
			cout << "Выход ..." << endl;
			break;
		default:
			cout << "Такого пункта меню нет\n" << endl;
			break;
		}
	} while (ch != 15);

	return Attr;

}
void AttributesFile(DWORD AttrF)
{
	cout << "Этот файл: " << endl;
	if (AttrF & FILE_ATTRIBUTE_ARCHIVE)
		cout << "Архивный" << endl;
	if (AttrF & FILE_ATTRIBUTE_COMPRESSED)
		cout << "Сжатый" << endl;
	if (AttrF & FILE_ATTRIBUTE_DEVICE)
		cout << "Зарезервирован; не используется." << endl;
	if (AttrF & FILE_ATTRIBUTE_DIRECTORY)
		cout << "Дескриптор идентифицирует каталог." << endl;
	if (AttrF & FILE_ATTRIBUTE_ENCRYPTED)
		cout << "Зашифрованный" << endl;
	if (AttrF & FILE_ATTRIBUTE_HIDDEN)
		cout << "Скрытый" << endl;
	if (AttrF & FILE_ATTRIBUTE_NORMAL)
		cout << "Не имеет других установленных атрибутов" << endl;
	if (AttrF & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
		cout << "Не будет индексирован содержащим индексы модулем обслуживания." << endl;
	if (AttrF & FILE_ATTRIBUTE_OFFLINE)
		cout << "Данные файла были физически перемещены, чтобы сохраняться автономно" << endl;
	if (AttrF & FILE_ATTRIBUTE_READONLY)
		cout << "Только для чтения" << endl;
	if (AttrF & FILE_ATTRIBUTE_REPARSE_POINT)
		cout << "Имеет связанную точку повторной обработки." << endl;
	if (AttrF & FILE_ATTRIBUTE_SPARSE_FILE)
		cout << "Разреженный файл." << endl;
	if (AttrF & FILE_ATTRIBUTE_SYSTEM)
		cout << "Частично или исключительно используется  операционной системой.\n" << endl;
	if (AttrF & FILE_ATTRIBUTE_TEMPORARY)
		cout << "Используется для временного хранения" << endl;
}

void FileInf(BY_HANDLE_FILE_INFORMATION lpFileInf)
{
	SYSTEMTIME time;
	BOOL flag = 0;
	AttributesFile(lpFileInf.dwFileAttributes);
	cout << "---------------------------------------" << endl;
	cout << "Серийный номер диска, на котором находится файл: " << &(lpFileInf.dwVolumeSerialNumber) << endl;
	cout << "Старшее слово размера файла: " << &(lpFileInf.nFileSizeHigh) << endl;
	cout << "Младшее слово размера файла: " << &(lpFileInf.nFileSizeLow) << endl;
	cout << "Кол-во ссылок на файл в ФС: " << &(lpFileInf.nNumberOfLinks) << endl;
	cout << "Старшее слово уникального 64-битного идентификатора файла: " << &(lpFileInf.nFileIndexHigh) << endl;
	cout << "Младшее слово уникального 64-битного идентификатора файла: " << &(lpFileInf.nFileIndexLow) << endl;
}

void FileTime(HANDLE hf)
{
	SYSTEMTIME time;
	BOOL flag = 0;
	FILETIME lpCreationTime, lpLastAccessTime, lpLastWriteTime;
	flag = GetFileTime(hf, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	if (flag != 0) {
		flag = FileTimeToSystemTime(&lpCreationTime, &time);
		if (flag != 0)
			cout << "Время и дата создания файла: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "Произошла ошибка " << GetLastError() << " при получение времени и даты создания файла" << endl;
		flag = FileTimeToSystemTime(&lpLastAccessTime, &time);
		if (flag != 0)
			cout << "Дата последнего обращения: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "Произошла ошибка " << GetLastError() << " при получение даты последнего обращения" << endl;
		flag = FileTimeToSystemTime(&lpLastWriteTime, &time);
		if (flag != 0)
			cout << "Дата последней модификации: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "Произошла ошибка " << GetLastError() << " при получение даты последней модификации" << endl;
	}
	else
		cout << "Произошла ошибка " << GetLastError() << " при получение даты последней модификации" << endl;
}

void SetFileTime(HANDLE hf)
{
	FILETIME FileTime;
	SYSTEMTIME time;
	BOOL flag = 0;
	GetSystemTime(&time);
	flag = SystemTimeToFileTime(&time, &FileTime);
	if (flag != 0)
	{
		flag = SetFileTime(hf, &FileTime, &FileTime, &FileTime);
		if (flag == 0)
			cout << "Произошла ошибка " << GetLastError() << " при установлении времени, взаимодействия с файлом" << endl;
		else
			cout << "Текущее время является установленным временем взаимодействия с файлом" << endl;
	}
	else
		cout << "Произошла ошибка " << GetLastError() << " при установлении времени, взаимодействия с файлом" << endl;


}
void menuRemoveAttr()
{
	cout << "1 - Извлечение установленных атрибутов в файле" << endl;
	cout << "2 - Изменить атрибуты файла" << endl;
	cout << "3 - Вывод информации о файле" << endl;
	cout << "4 - Вывод информации о временном взаимодействии с файлом" << endl;
	cout << "5 - Изменение времени взаимодействия с файлом на текущее время" << endl;
	cout << "6 - Выйти" << endl;
}
void WorkWithFile()
{
	CHAR PathCurrentFile[MAX_PATH + 1];
	HANDLE FileHandle;
	int ch;
	BY_HANDLE_FILE_INFORMATION lpFileInf;
	DWORD GetAttr;
	cout << "Введите путь файл с именем и расширинием" << endl;
	cin >> PathCurrentFile;
	FileHandle = CreateFile(PathCurrentFile, GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_WRITE_ATTRIBUTES, NULL);
	if (FileHandle != INVALID_HANDLE_VALUE) {

		do {
			menuRemoveAttr();
			cin >> ch;
			switch (ch)
			{
			case 1:
				system("cls");
				AttributesFile(GetFileAttributes(PathCurrentFile));
				break;
			case 2:
				system("cls");
				GetAttr = AttrsInfo();

				if (SetFileAttributes(PathCurrentFile, GetAttr) != 0)
					AttributesFile(GetAttr);
				else
					cout << "Произошла ошибка " << GetLastError() << " при установке атрибутов " << endl;
				break;
			case 3:
				system("cls");
				if (GetFileInformationByHandle(FileHandle, &lpFileInf) != 0)
					FileInf(lpFileInf);
				else
					cerr << "Произошла ошибка " << GetLastError() << "при получении информации о файле" << endl;
				break;
			case 4:
				system("cls");
				FileTime(FileHandle);
				break;
			case 5:
				system("cls");
				SetFileTime(FileHandle);
				break;
			case 6:
				cout << "Выход ..." << endl;
				CloseHandle(FileHandle);
				break;
			default:
				cout << "Такого пункта меню нет" << endl;
				break;
			}
		} while (ch != 6);
	}
	else cout << "Произошла ошибка " << GetLastError << " при открытии файл" << endl;
}

void CreateNewFile()
{
	CHAR NameFile[MAX_PATH + 1];
	HANDLE FileHandle;
	cout << "Введите путь нового файла с именем и расширинием" << endl;
	cin >> NameFile;
	FileHandle = CreateFile(NameFile, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, NULL, CREATE_NEW, NULL, NULL);
	if (FileHandle != INVALID_HANDLE_VALUE)
		cout << "Файл создан" << endl;
	else
		cout << "Произошла ошибка, файл не создан из-за ошибки " << GetLastError() << endl;
	CloseHandle(FileHandle);
}
void WorkWithDirectory()
{
	cout << "1 - Создание заданного каталога" << endl;
	cout << "2 - Удаление заданного каталога" << endl;
	cout << "3 - Выход" << endl;
}
void CreatAndRemoveDirectory()
{
	int ch;
	BOOL flag = 0;
	CHAR BN[MAX_PATH + 1];
	do {
		WorkWithDirectory();
		cin >> ch;
		switch (ch)
		{
		case 1:
			flag = 0;
			cout << "Введите путь нового каталога" << endl;
			cin >> BN;
			flag = CreateDirectory(BN, NULL);
			if (flag == 0)
				cout << "Не удалось создать каталог " << GetLastError() << endl;
			else
				cout << "Каталог успешно создан" << endl;
			cout << endl;
			break;
		case 2:
			flag = 0;
			cout << "Введите путь существующего каталога" << endl;
			cin >> BN;
			flag = RemoveDirectory(BN);
			if (flag == 0)
				cout << "Не удалось удалить каталог " << GetLastError() << endl;
			else
				cout << "Каталог удалён успешно!" << endl;
			cout << endl;
			break;
		case 3:
			cout << "Выход ...\n" << endl;
			cout << endl;
			break;
		default:
			cout << "Такого пункта нет" << endl;
			break;
		}
	} while (ch == 0);


}


void menu()
{
	cout << "1 - Вывод списка дисков" << endl;
	cout << "2 - Вывод информацию о диске и размера свободного пространства(GetVolumeInformation)" << endl;
	cout << "3 - Создание/Удаление заданных каталогов(CreateDirectory and RemoveDirectory)" << endl;
	cout << "4 - Создание файлов в новых каталогах(CreateFile)" << endl;
	cout << "5 - Копирование/перемещение файлов между каталогами(CopyFile,MoveFile,MoveFileEx)" << endl;
	cout << "6 - Анализ и изменение атрибутов файлов(GetFileAttributes, SetFileAttributes, GetFileInformationByHandle,GetFileTime, SetFileTime)" << endl;
	cout << "7 - Выход" << endl;
}



int main()
{
	DWORD DD;
	vector<string> b = {};
	int ch;
	system("chcp 1251");
	system("cls");
	DD = GetLogicalDrives();
	BuffD(b, DD);
	do
	{
		menu();
		cin >> ch;
		cout << endl;
		switch (ch)
		{

		case 1:
			system("cls");
			OutputListDisk(b);
			break;
		case 2:
			system("cls");
			ChoiceDisk(b);
			break;
		case 3:
			system("cls");
			CreatAndRemoveDirectory();
			break;
		case 4:
			system("cls");
			CreateNewFile();
			break;
		case 5:
			system("cls");
			CopyAndMoveFile();
			break;
		case 6:
			system("cls");
			WorkWithFile();
			break;
		case 7:
			system("cls");
			cout << "Выходим..." << endl;
			break;
		default:
			system("cls");
			cout << "В данном меню такого пункта нет\n" << endl;
			break;

		}
	} while (ch != 7);

	return 0;
}