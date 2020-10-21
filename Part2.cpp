#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>

#pragma comment(lib, "winmm.lib")

using namespace std;

HANDLE SourceFile, NewFile;
DWORD R,W,Re,FileSize,Size_block,NumPr;
CHAR** Cop;
OVERLAPPED* ProvData1,* ProvData2;

void SizeNum(DWORD SB,DWORD NO)
{
	cout << "Размер блока: " << SB << endl;
	cout << "Количество операций: " << NO << endl;
	cout << endl;
}
void SizeAndNumFile()
{
	if (FileSize % 1024 > 0)
		cout << "Размер файла: " << FileSize / 1024 + 1 << endl;
	else
		cout << "Размер файла: " << FileSize / 1024 + 0 << endl;
	if (FileSize % Size_block > 0)
	{
		Re = FileSize / Size_block + 1;
		cout << "Количество записей: " << Re << endl;
	}
	else
	{
		Re = FileSize / Size_block + 0;
		cout << "Количество записей: " << Re << endl;
	}
}
VOID CALLBACK CAW(DWORD Error, DWORD Bytes, LPOVERLAPPED p);
VOID CALLBACK CAR(DWORD Error, DWORD Bytes, LPOVERLAPPED p)
{
	if (Error == 0)
	{
		BOOL flag = 0;
		LARGE_INTEGER P;
		R++;
		DWORD k = (DWORD)(p->hEvent);
		P.LowPart = ProvData1[k].Offset;
		P.HighPart = ProvData1[k].OffsetHigh;
		ProvData2[k].Offset = ProvData1[k].Offset;
		ProvData2[k].OffsetHigh = ProvData1[k].OffsetHigh;
		if (WriteFileEx(NewFile, Cop[k], Size_block, &ProvData2[k], CAW) == 0)
			cout << "Ошибка " << GetLastError() <<" при записи файла"<< endl;
		P.QuadPart += Size_block * (LONGLONG)(NumPr);
		ProvData1[k].Offset = P.LowPart;
		ProvData1[k].OffsetHigh = P.HighPart;
	}
	return;
}



VOID CALLBACK CAW(DWORD Error, DWORD Bytes, LPOVERLAPPED p)
{
	if (Error == 0) {
		LARGE_INTEGER P;
		W++;
		DWORD k = (DWORD)(p->hEvent);
		P.LowPart = ProvData1[k].Offset;
		P.HighPart = ProvData1[k].OffsetHigh;
		if (P.QuadPart < FileSize)
			if (ReadFileEx(SourceFile, Cop[k], Size_block, &ProvData1[k], CAR) == 0)
				cout << "Ошибка "<< GetLastError() <<" при чтении файла" << endl;
	}
	return;

}
float Copy()
{	
	double t_begin, t_end;
	LARGE_INTEGER P;
	BOOL flag = 0;
	P.QuadPart = 0;
	ProvData1 = new OVERLAPPED[NumPr];
	ProvData2 = new OVERLAPPED[NumPr];
	Cop = new CHAR * [NumPr];
	for (DWORD j = 0;j < NumPr;j++)
		Cop[j] = new CHAR[Size_block];
	t_begin = timeGetTime();
	for (DWORD i = 0; i < NumPr; i++)
	{
		ProvData1[i].hEvent = (HANDLE)i;
		ProvData1[i].Offset = P.LowPart;
		ProvData1[i].OffsetHigh = P.HighPart;
		ProvData2[i].hEvent = (HANDLE)i;
		if (P.QuadPart < FileSize)
			if (ReadFileEx(SourceFile, Cop[i], Size_block, &ProvData1[i], CAR) == 0)
				cout << "Ошибка " << GetLastError << " при чтении файла" << endl;
		P.QuadPart = P.QuadPart + (LONGLONG)Size_block;
	}
	R = 0;
	while (R < Re)
		SleepEx(INFINITE, TRUE);
	SetFilePointer(NewFile, FileSize, NULL, FILE_BEGIN);
	SetEndOfFile(NewFile);
	t_end = timeGetTime();
	return (t_end - t_begin)/1000;
}
void menuNum()
{
	cout << "Выберите количество операций\n";
	cout << "1 - 1 операция"<<endl;
	cout << "2 - 2 операции" << endl;
	cout << "3 - 4 операции" << endl;
	cout << "4 - 8 операции" << endl;
	cout << "5 - 12 операций" << endl;
	cout << "6 - 16 операций" << endl;
	cout << endl;
}
void ChoiceNumPr()
{
	int k;
	do
	{
		menuNum();
		cin >> k;
		switch (k)
		{
		case 1:
			NumPr = 1;
			break;
		case 2:
			NumPr = 2;
			break;
		case 3:
			NumPr = 4;
			break;
		case 4:
			NumPr = 8;
			break;
		case 5:
			NumPr = 12;
			break;
		case 6:
			NumPr = 16;
			break;
		default:
			cout << "Такого пункта нет" << endl;
			break;
		}
	} while (k != 1 && k != 2 && k != 3 && k != 4 && k != 5 && k != 6);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	string File1 = "VirtualBox-6.1.12-139181-Win.exe\0";
	string File2 = "NewFile.exe\0";
	fstream MyFile;
	CHAR NameFirstFile[MAX_PATH + 1] = {};
	CHAR NameSecondFile[MAX_PATH + 1] = {};
	DWORD arr1 = 4096;
	DWORD arr2[] = {1,2,4,8,12,16};
	double TimeCopy;
	DWORD l = 0;
	MyFile.open("End.txt", ios::app | ios::out);
	copy(File1.begin(), File1.end(), NameFirstFile);
	copy(File2.begin(), File2.end(), NameSecondFile);
	SourceFile = CreateFile(NameFirstFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
	NewFile = CreateFile(NameSecondFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
	if (SourceFile != INVALID_HANDLE_VALUE && NewFile != INVALID_HANDLE_VALUE)
	{
		Size_block = arr1;
		ChoiceNumPr();
		SizeNum(Size_block, NumPr);
		FileSize = GetFileSize(SourceFile, NULL);
		SizeAndNumFile();
		TimeCopy = Copy();
		cout << "Время копирования файла " << TimeCopy << endl;
		cout << endl;
		CloseHandle(SourceFile);
		CloseHandle(NewFile);
		MyFile << TimeCopy << " ";
	}
	else
		cout << "Произошла ошибка " << GetLastError << " при открытии файла" << endl;
	MyFile.close();
	return 0;
}