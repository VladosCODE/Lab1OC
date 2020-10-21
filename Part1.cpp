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
		cout << ++j << ") ���� " << *i << endl;
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
		cout << "�������";
		break;
	case DRIVE_REMOTE:
		cout << "���������";
		break;
	case DRIVE_FIXED:
		cout << "�������������";
		break;
	case DRIVE_UNKNOWN:
		cout << "��� ������� ����� ����������";
		break;
	case DRIVE_NO_ROOT_DIR:
		cout << "�������� ����";
		break;
	}
}
void AllInFoAboutDisk(LPCTSTR d)
{
	CHAR NameFileSystem[MAX_PATH + 1];
	char NameBuf[MAX_PATH + 1];
	DWORD SerialNumber, MaxLengthFile, FileSystemOptions;
	cout << "��� �����: ";
	FindTypeDisk(GetDriveType(d));
	cout << endl;

	BOOL b = GetVolumeInformation(d, NameBuf, MAX_PATH, &SerialNumber, &MaxLengthFile, &FileSystemOptions, NameFileSystem, MAX_PATH);
	if (b) {
		cout << "��� �������: ";
		for (int i = 0; i < MAX_PATH; i++)
		{
			if (NameBuf[i] != '\0')
				cout << NameBuf[i];
			else
				break;
		}
		cout << endl;
		cout << "�������� �������: ";
		for (int i = 0; i < MAX_PATH; i++)
		{
			if (NameFileSystem[i] != '\0')
				cout << NameFileSystem[i];
			else
				break;
		}
		cout << endl;
		cout << "������������ ����� �����: " << MaxLengthFile << endl;
		cout << "����� �������� �������: " << FileSystemOptions << endl;
		cout << "�������� ����� �������: " << SerialNumber << endl;
	}
	else
		cout << "\n �������� ������: " << GetLastError << endl;
	cout << endl;

	DWORD NumberSectors, ByteInEverySector, freeCl, AllNumberCl;

	b = GetDiskFreeSpace(d, &NumberSectors, &ByteInEverySector, &freeCl, &AllNumberCl);
	if (b != false)
	{
		cout << "���������� �������� � ������ ��������: " << NumberSectors << endl;
		cout << "���������� ������ � ������ �������: " << ByteInEverySector << endl;
		cout << "���������� ��������� ���������: " << freeCl << endl;
		cout << "����� ���������� ���������: " << AllNumberCl << endl;
		cout << "���������� ���������� ����� " << (long double(ByteInEverySector) / 1024.0 / 1024.0 / 1024.) * freeCl * NumberSectors << " GB" << " �� " << (long double(ByteInEverySector) / 1024.0 / 1024.0 / 1024.) * AllNumberCl * NumberSectors << " GB" << endl;
	}
	else cout << "\n��������� ������: " << GetLastError() << endl;

}
void ChoiceDisk(vector <string> b)
{
	unsigned int c;
	cout << "\n�������� ����:\n" << endl;
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
		cout << "������ ���� �����������";
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
	cout << "1 - ����������� �����" << endl;
	cout << "2 - ����������� ����� ����� ��������" << endl;
	cout << "3 - �����" << endl;
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
			cout << "������� ���� �� �������� �����" << endl;
			cin >> PathCurrentFile;
			cout << "������� ���� �� ������ �����" << endl;
			cin >> PathNewFile;
			flag = 0;
			flag = CopyFile(PathCurrentFile, PathNewFile, FALSE);
			if (flag == 0)
				cout << "��������� ������ " << GetLastError() << " ��� ����������� �����" << endl;
			else
				cout << "���� ������� c���������" << endl;
			break;

		case 2:
			system("cls");
			cout << "������� ���� �� �������� �����" << endl;
			cin >> PathCurrentFile;
			cout << "������� ���� �� ������ �����" << endl;
			cin >> PathNewFile;
			flag = 0;
			flag = MoveFile(PathCurrentFile, PathNewFile);
			if (flag == 0)
				flag = MoveFileEx(PathCurrentFile, PathNewFile, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
			if (flag == 0)
				cout << "��������� ������ " << GetLastError() << " ��� ����������� �����" << endl;
			else
				cout << "���� ������� ���������" << endl;
			break;
		case 3:
			system("cls");
			cout << "����� ...\n" << endl;
			break;
		default:
			cout << "������ ������ ���" << endl;
			break;
		}
	} while (ch == 3);
}
void ChoiceAttr()
{
	cout << "������� ������ ��������� ��� ������������ � ������ ����: " << endl;
	cout << "1 - ��������" << endl;
	cout << "2 - ������" << endl;
	cout << "3 - ��������������, �� �� ������������" << endl;
	cout << "4 - ���������� �������������� �������" << endl;
	cout << "5 - �������������" << endl;
	cout << "6 - �������" << endl;
	cout << "7 - �� ����� ������ ������������� ���������" << endl;
	cout << "8 - �� ����� ������������ ���������� ������� ������� ������������" << endl;
	cout << "9 - ������ ����� ���� ��������� ����������, ����� ����������� ���������" << endl;
	cout << "10 - ������ ��� ������" << endl;
	cout << "11 - ����� ��������� ����� ��������� ���������." << endl;
	cout << "12 - �����������" << endl;
	cout << "13 - �������� ��� ������������� ����������  ������������ �������" << endl;
	cout << "14 - ���������� ��������" << endl;
	cout << "15 - �����" << endl;
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
			cout << "����� ..." << endl;
			break;
		default:
			cout << "������ ������ ���� ���\n" << endl;
			break;
		}
	} while (ch != 15);

	return Attr;

}
void AttributesFile(DWORD AttrF)
{
	cout << "���� ����: " << endl;
	if (AttrF & FILE_ATTRIBUTE_ARCHIVE)
		cout << "��������" << endl;
	if (AttrF & FILE_ATTRIBUTE_COMPRESSED)
		cout << "������" << endl;
	if (AttrF & FILE_ATTRIBUTE_DEVICE)
		cout << "��������������; �� ������������." << endl;
	if (AttrF & FILE_ATTRIBUTE_DIRECTORY)
		cout << "���������� �������������� �������." << endl;
	if (AttrF & FILE_ATTRIBUTE_ENCRYPTED)
		cout << "�������������" << endl;
	if (AttrF & FILE_ATTRIBUTE_HIDDEN)
		cout << "�������" << endl;
	if (AttrF & FILE_ATTRIBUTE_NORMAL)
		cout << "�� ����� ������ ������������� ���������" << endl;
	if (AttrF & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
		cout << "�� ����� ������������ ���������� ������� ������� ������������." << endl;
	if (AttrF & FILE_ATTRIBUTE_OFFLINE)
		cout << "������ ����� ���� ��������� ����������, ����� ����������� ���������" << endl;
	if (AttrF & FILE_ATTRIBUTE_READONLY)
		cout << "������ ��� ������" << endl;
	if (AttrF & FILE_ATTRIBUTE_REPARSE_POINT)
		cout << "����� ��������� ����� ��������� ���������." << endl;
	if (AttrF & FILE_ATTRIBUTE_SPARSE_FILE)
		cout << "����������� ����." << endl;
	if (AttrF & FILE_ATTRIBUTE_SYSTEM)
		cout << "�������� ��� ������������� ������������  ������������ ��������.\n" << endl;
	if (AttrF & FILE_ATTRIBUTE_TEMPORARY)
		cout << "������������ ��� ���������� ��������" << endl;
}

void FileInf(BY_HANDLE_FILE_INFORMATION lpFileInf)
{
	SYSTEMTIME time;
	BOOL flag = 0;
	AttributesFile(lpFileInf.dwFileAttributes);
	cout << "---------------------------------------" << endl;
	cout << "�������� ����� �����, �� ������� ��������� ����: " << &(lpFileInf.dwVolumeSerialNumber) << endl;
	cout << "������� ����� ������� �����: " << &(lpFileInf.nFileSizeHigh) << endl;
	cout << "������� ����� ������� �����: " << &(lpFileInf.nFileSizeLow) << endl;
	cout << "���-�� ������ �� ���� � ��: " << &(lpFileInf.nNumberOfLinks) << endl;
	cout << "������� ����� ����������� 64-������� �������������� �����: " << &(lpFileInf.nFileIndexHigh) << endl;
	cout << "������� ����� ����������� 64-������� �������������� �����: " << &(lpFileInf.nFileIndexLow) << endl;
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
			cout << "����� � ���� �������� �����: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "��������� ������ " << GetLastError() << " ��� ��������� ������� � ���� �������� �����" << endl;
		flag = FileTimeToSystemTime(&lpLastAccessTime, &time);
		if (flag != 0)
			cout << "���� ���������� ���������: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "��������� ������ " << GetLastError() << " ��� ��������� ���� ���������� ���������" << endl;
		flag = FileTimeToSystemTime(&lpLastWriteTime, &time);
		if (flag != 0)
			cout << "���� ��������� �����������: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour + 3 << ":" << time.wMinute << endl;
		else
			cout << "��������� ������ " << GetLastError() << " ��� ��������� ���� ��������� �����������" << endl;
	}
	else
		cout << "��������� ������ " << GetLastError() << " ��� ��������� ���� ��������� �����������" << endl;
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
			cout << "��������� ������ " << GetLastError() << " ��� ������������ �������, �������������� � ������" << endl;
		else
			cout << "������� ����� �������� ������������� �������� �������������� � ������" << endl;
	}
	else
		cout << "��������� ������ " << GetLastError() << " ��� ������������ �������, �������������� � ������" << endl;


}
void menuRemoveAttr()
{
	cout << "1 - ���������� ������������� ��������� � �����" << endl;
	cout << "2 - �������� �������� �����" << endl;
	cout << "3 - ����� ���������� � �����" << endl;
	cout << "4 - ����� ���������� � ��������� �������������� � ������" << endl;
	cout << "5 - ��������� ������� �������������� � ������ �� ������� �����" << endl;
	cout << "6 - �����" << endl;
}
void WorkWithFile()
{
	CHAR PathCurrentFile[MAX_PATH + 1];
	HANDLE FileHandle;
	int ch;
	BY_HANDLE_FILE_INFORMATION lpFileInf;
	DWORD GetAttr;
	cout << "������� ���� ���� � ������ � �����������" << endl;
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
					cout << "��������� ������ " << GetLastError() << " ��� ��������� ��������� " << endl;
				break;
			case 3:
				system("cls");
				if (GetFileInformationByHandle(FileHandle, &lpFileInf) != 0)
					FileInf(lpFileInf);
				else
					cerr << "��������� ������ " << GetLastError() << "��� ��������� ���������� � �����" << endl;
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
				cout << "����� ..." << endl;
				CloseHandle(FileHandle);
				break;
			default:
				cout << "������ ������ ���� ���" << endl;
				break;
			}
		} while (ch != 6);
	}
	else cout << "��������� ������ " << GetLastError << " ��� �������� ����" << endl;
}

void CreateNewFile()
{
	CHAR NameFile[MAX_PATH + 1];
	HANDLE FileHandle;
	cout << "������� ���� ������ ����� � ������ � �����������" << endl;
	cin >> NameFile;
	FileHandle = CreateFile(NameFile, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, NULL, CREATE_NEW, NULL, NULL);
	if (FileHandle != INVALID_HANDLE_VALUE)
		cout << "���� ������" << endl;
	else
		cout << "��������� ������, ���� �� ������ ��-�� ������ " << GetLastError() << endl;
	CloseHandle(FileHandle);
}
void WorkWithDirectory()
{
	cout << "1 - �������� ��������� ��������" << endl;
	cout << "2 - �������� ��������� ��������" << endl;
	cout << "3 - �����" << endl;
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
			cout << "������� ���� ������ ��������" << endl;
			cin >> BN;
			flag = CreateDirectory(BN, NULL);
			if (flag == 0)
				cout << "�� ������� ������� ������� " << GetLastError() << endl;
			else
				cout << "������� ������� ������" << endl;
			cout << endl;
			break;
		case 2:
			flag = 0;
			cout << "������� ���� ������������� ��������" << endl;
			cin >> BN;
			flag = RemoveDirectory(BN);
			if (flag == 0)
				cout << "�� ������� ������� ������� " << GetLastError() << endl;
			else
				cout << "������� ����� �������!" << endl;
			cout << endl;
			break;
		case 3:
			cout << "����� ...\n" << endl;
			cout << endl;
			break;
		default:
			cout << "������ ������ ���" << endl;
			break;
		}
	} while (ch == 0);


}


void menu()
{
	cout << "1 - ����� ������ ������" << endl;
	cout << "2 - ����� ���������� � ����� � ������� ���������� ������������(GetVolumeInformation)" << endl;
	cout << "3 - ��������/�������� �������� ���������(CreateDirectory and RemoveDirectory)" << endl;
	cout << "4 - �������� ������ � ����� ���������(CreateFile)" << endl;
	cout << "5 - �����������/����������� ������ ����� ����������(CopyFile,MoveFile,MoveFileEx)" << endl;
	cout << "6 - ������ � ��������� ��������� ������(GetFileAttributes, SetFileAttributes, GetFileInformationByHandle,GetFileTime, SetFileTime)" << endl;
	cout << "7 - �����" << endl;
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
			cout << "�������..." << endl;
			break;
		default:
			system("cls");
			cout << "� ������ ���� ������ ������ ���\n" << endl;
			break;

		}
	} while (ch != 7);

	return 0;
}