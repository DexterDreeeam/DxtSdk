#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

string get_new_split_name(string &split_file_path, string &suffix, int id)
{
    return split_file_path.substr(0, split_file_path.size() - suffix.size()) + '_' + to_string(id) + suffix;
}

void split(string &split_file_path, int section_lines)
{
    string suffix = "";

    for (int i = split_file_path.size() - 1; i >= 0; --i)
    {
        if (split_file_path[i] == '.')
        {
            suffix = split_file_path.substr(i);
            break;
        }
        else if (split_file_path[i] == '\\' || split_file_path[i] == '/')
        {
            break;
        }
    }

    //char buf[2048];
    char buf[1024];
    auto *f_ori = fopen(split_file_path.c_str(), "r");

    int lines = 0;
    int file_idx = 0;
    auto *f_new = fopen(get_new_split_name(split_file_path, suffix, file_idx).c_str(), "w");

    while (!feof(f_ori))
    {
        //memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf) - 1, f_ori);

        if (lines == section_lines)
        {
            fclose(f_new);
            lines = 0;
            ++file_idx;

            f_new = fopen(get_new_split_name(split_file_path, suffix, file_idx).c_str(), "w");
        }

        fputs(buf, f_new);
        ++lines;
    }
    fclose(f_new);
    fclose(f_ori);
}

int main(int argc, const char *args[])
{
    string execute_path = args[0];
    unsigned int i = execute_path.size();
    while (i > 0 && execute_path[--i] != '\\')
    {
        ;
    }

    string execute_folder_path = execute_path.substr(0, i + 1);

    string input;
    cout << "Please input text file :" << endl;
    getline(cin, input);

    string split_file_path = execute_folder_path + input;

    int parts;
    int lines;
    auto *f_ori = fopen(split_file_path.c_str(), "r");
    if (!f_ori)
    {
        cout << "Not existing file." << endl;
        goto done;
    }

    {
        lines = 0;
        char buf[2048];
        cout << "Caculate file lines ... /";
        while (!feof(f_ori))
        {
            //memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf) - 1, f_ori);
            ++lines;
            if (lines % 300000 == 0)
            {
                cout << '\b';
                switch ((lines / 300000) % 3)
                {
                case 0:
                    cout << '\\';
                    break;
                case 1:
                    cout << '/';
                    break;
                case 2:
                    cout << '-';
                    break;
                }
            }
        }
        cout << endl;
    }

    cout << "========= This file has " << lines << " lines." << endl;
    fclose(f_ori);

    input.clear();
    while (input.size() == 0)
    {
        cout << "Please input partition parts number :" << endl;
        getline(cin, input);
    }

    parts = atoi(input.c_str());
    if (parts < 2 || parts > 100)
    {
        cout << "Invalid parts number." << endl;
        goto done;
    }

    split(split_file_path, (lines % parts) == 0 ? lines / parts : lines / parts + 1);
    cout << "Split complete." << endl;

done:
    system("pause");
    return 0;
}
