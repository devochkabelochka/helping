// ConsoleApplicationCo.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;

struct person_data
{
	char login[20];
	int password;
};


void unarchieve(struct person_data* PersonData)
{
	FILE *fp;
	char *path = "C:/Users/student/Desktop/hash-function/base.txt";


	fp = fopen(path, "r+");
	if (fp == NULL)
	{
		cout << "file not opened, met an error\n";
		exit(1);
	}
	else
	{
		cout << "unarchiving...\n";
	}

	int count = fread(&PersonData, sizeof(struct person_data), 1, fp);
	cout << count << '\n';
}

int lenOfWord(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

int is_equal(char *str1, char *str2) {
	int len = lenOfWord(str1);
	for (int i; i < len; i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
		else {
			return 1;
		}
	}
}


void connection(char *str, char *stp)
{
	int i = 0;
	while (str[i] != '\0')
	{
	i++;
	}
	int j = 0;
	while (stp[j] != '\0')
	{
		str[j] = stp[j];
		j++;
	}
	str[j] = '\0';
}

int notes() {
	FILE *fp;
	char *path = "C:/Users/student/Desktop/hash-function/base.txt";
	fp = fopen(path, "r+");
	if (fp == NULL)
	{
		cout << "File not opened! Error!";
		return 0;
	}
	cout << "File opened!\n";
	fseek(fp, 0, SEEK_END);
	int a = ftell(fp) / sizeof(person_data);
	return a;
}

int in_db(char *login)
{
	struct person_data b;
	FILE *fp;
	char *path = "C:/Users/student/Desktop/hash-function/base.txt";
	fp = fopen(path, "r+");
	if (fp == NULL)
	{
		cout << "File not opened! Error!";
		return 0;
	}
	else
	{
		cout << "File opened!\n";
		fseek(fp, 0, SEEK_END);
		int len = notes();
		unarchieve(&b);
		return 1;
	}

}

int Hash(char *key)
{
	long long int hash, i = 0;

	while (key[i] != '\0')
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash % 100;
}


void archieve(struct person_data b)
{
	FILE *fp;
	char *path = "C:/Users/student/Desktop/hash-function/base.txt";

	fp = fopen(path, "r+");
	if (fp == NULL)
	{
		cout << "File not opened! Error!";
	}
	else
	{
		cout << "File opened!\n";
	}
	fseek(fp, 0, SEEK_END);
	fwrite(&b, sizeof(person_data), 1, fp);
}




void registration(char *login, int password)
{
	struct person_data personality;
	connection(personality.login, login);
	personality.password = password;


	archieve(personality);

	unarchieve(&personality);
}


void start_function()
{
	char login[30];
	char password_str[30];

	cout << "Enter login: ";
	cin >> login;

	if (in_db(login) != 1) {
	cout << "Some issues";
	}

	cout << "Enter password: ";
	cin >> password_str;

	//int lenOfPassword = lenOfWord(password_str);
	int password_hash = Hash(password_str);

	registration(login, password_hash);
}


int main()
{
	//    char *password = "f6f7fdfg8ds";
	//    int len = lenOfWord(password);
	//
	//    printf("%d\n", Hash(password, len));
	start_function();
	return 0;
}
