
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

bool print_traversed_file = false;
bool count_valid_lines = false;
bool tansfer_tab2space = false;
bool delete_tail_space = false;

void func_count_valid_lines(string &file_path);
void func_tansfer_tab2space(string &file_path);
void func_delete_tail_space(string &file_path);

vector<string> search_file_suffix = {};
vector<string> default_file_suffix =
{
    "cpp",
    "hpp",
    "c",
    "h",
    "inl",
    "txt",
};

void iterate_file(string file_path)
{
    if (print_traversed_file)
    {
        cout << file_path << " <<<< traversed." << endl;
    }

    if (count_valid_lines)
    {
        func_count_valid_lines(file_path);
    }

    if (tansfer_tab2space)
    {
        func_tansfer_tab2space(file_path);
    }

    if (delete_tail_space)
    {
        func_delete_tail_space(file_path);
    }
}

bool examSuffix(string &file_path);
void iterate_folder(string folder_path)
{
    string pattern = folder_path + '*';
    WIN32_FIND_DATA wfd;

    auto handle = FindFirstFile(pattern.c_str(), &wfd);
    while (handle != INVALID_HANDLE_VALUE)
    {
        if (strcmp(wfd.cFileName, ".") == 0 || strcmp(wfd.cFileName, "..") == 0)
        {
            ;
        }
        else if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            //# new subfolder
            iterate_folder(folder_path + wfd.cFileName + '\\');
        }
        else if (wfd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
        {
            string file_path = folder_path + wfd.cFileName;
            if (examSuffix(file_path))
            {
                //# new objective file
                iterate_file(file_path);
            }
        }
        else
        {
            //# abnormal file type, not disposed
            cout << "abnormal file type :" << folder_path + wfd.cFileName << endl;
        }

        if (FindNextFile(handle, &wfd) == FALSE)
        {
            break;
        }
    }
    FindClose(handle);
}

unordered_set<string> search_suffix_set;
bool examSuffix(string &file_path)
{
    int idx = file_path.size() - 1;
    while (idx >= 0)
    {
        if (file_path[idx] == '\\')
        {
            return false;
        }
        else if (file_path[idx] == '.')
        {
            if (idx == file_path.size() - 1)
            {
                return false;
            }
            return search_suffix_set.count(file_path.substr(idx + 1)) != 0;
        }
        --idx;
    }
    return false;
}

void func_count_valid_lines(string &file_path)
{
    ;
}

string yearStr = "2020";
void func_update_copyright(string &file_path)
{
    static char char_buf[1024];

    string tmp_path = file_path + "xtmp";
    MoveFile(file_path.c_str(), tmp_path.c_str());

    auto *f_new = fopen(file_path.c_str(), "w");
    auto *f_old = fopen(tmp_path.c_str(), "r");

    int line = 0; //# line NO. start from 0
    memset(char_buf, 0, sizeof(char_buf));
    fgets(char_buf, sizeof(char_buf) - 1, f_old);

    bool copyright_updated = false;

    while (!feof(f_old))
    {
        if (copyright_updated || line > 5)
        {
            goto L_next_line;
        }

        for (int i = 0; i < 30; ++i)
        {
            int j = i;
            if (char_buf[j++] == 'C' &&
                char_buf[j++] == 'o' &&
                char_buf[j++] == 'p' &&
                char_buf[j++] == 'y' &&
                char_buf[j++] == 'r' &&
                char_buf[j++] == 'i' &&
                char_buf[j++] == 'g' &&
                char_buf[j++] == 'h' &&
                char_buf[j++] == 't')
            {
                copyright_updated = true;
                string str(char_buf);
                int first_digit = -1, last_digit = -1;
                for (int k = 0; k < str.size(); ++k)
                {
                    if (str[k] >= '0' && str[k] <= '9')
                    {
                        if (first_digit == -1)
                        {
                            first_digit = k;
                        }
                        last_digit = k;
                    }
                }
                if (first_digit == -1)
                {
                    goto L_next_line;
                }
                if (str.substr(last_digit - 4 + 1, 4) == yearStr)
                {
                    goto L_next_line;
                }
                if (last_digit - first_digit + 1 < 4)
                {
                    goto L_next_line;
                }
                if (last_digit - first_digit + 1 == 4)
                {
                    string tmp = "";
                    tmp = str.substr(0, last_digit + 1) + " - " + yearStr;
                    if (last_digit + 1 < str.size())
                    {
                        tmp += str.substr(last_digit + 1);
                    }
                    str = tmp;
                }
                else
                {
                    str[last_digit] = yearStr[3];
                    str[last_digit - 1] = yearStr[2];
                    str[last_digit - 2] = yearStr[1];
                    str[last_digit - 3] = yearStr[0];
                }
                for (int k = 0; k < str.size(); ++k)
                {
                    char_buf[k] = str[k];
                }
                char_buf[str.size()] = '\0';
                goto L_next_line;
            }
        }

    L_next_line:
        //# next line
        fputs(char_buf, f_new);
        memset(char_buf, 0, sizeof(char_buf));
        fgets(char_buf, sizeof(char_buf) - 1, f_old);
        ++line;
    }
    fclose(f_new);
    fclose(f_old);

    DeleteFile(tmp_path.c_str());
}

void func_tansfer_tab2space(string &file_path)
{
    static char char_buf[1024];

    string tmp_path = file_path + "xtmp";
    MoveFile(file_path.c_str(), tmp_path.c_str());

    auto *f_new = fopen(file_path.c_str(), "w");
    auto *f_old = fopen(tmp_path.c_str(), "r");

    int line = 0; //# line NO. start from 0
    memset(char_buf, 0, sizeof(char_buf));
    fgets(char_buf, sizeof(char_buf) - 1, f_old);

    bool file_changed = false;

    while (!feof(f_old) || char_buf[0] != '\0')
    {
        string str = "";
        int end = 0;
        while (end < sizeof(char_buf))
        {
            char c = char_buf[end];
            if (c == '\0')
            {
                break;
            }
            if (c == '\t')
            {
                file_changed = true;
                str += "    "; //# add 4 space
            }
            else
            {
                str += c;
            }
            ++end;
        }

        fputs(str.c_str(), f_new);

        if (feof(f_old))
        {
            break;
        }

        //# next line
        memset(char_buf, 0, sizeof(char_buf));
        fgets(char_buf, sizeof(char_buf) - 1, f_old);
        ++line;
    }

    fclose(f_new);
    fclose(f_old);

    DeleteFile(tmp_path.c_str());

    if (file_changed)
    {
        func_update_copyright(file_path);
    }
}

void func_delete_tail_space(string &file_path)
{
    static char char_buf[1024];

    string tmp_path = file_path + "xtmp";
    MoveFile(file_path.c_str(), tmp_path.c_str());

    auto *f_new = fopen(file_path.c_str(), "w");
    auto *f_old = fopen(tmp_path.c_str(), "r");

    int line = 0; //# line NO. start from 0
    memset(char_buf, 0, sizeof(char_buf));
    fgets(char_buf, sizeof(char_buf) - 1, f_old);

    bool file_changed = false;

    while (!feof(f_old) || char_buf[0] != '\0')
    {
        int end = 0;
        while (end < sizeof(char_buf))
        {
            if (char_buf[end] == '\0')
            {
                break;
            }
            ++end;
        }
        int r_first_non_space = end - 1;
        if (r_first_non_space >= 0 && char_buf[r_first_non_space] == '\n')
        {
            --r_first_non_space;
        }
        while (r_first_non_space >= 0)
        {
            if (char_buf[r_first_non_space] != ' ')
            {
                break;
            }
            --r_first_non_space;
        }
        //# add tail CR
        char_buf[r_first_non_space + 1] = '\n';
        char_buf[r_first_non_space + 2] = '\0';
        fputs(char_buf, f_new);

        if (r_first_non_space + 2 != end)
        {
            file_changed = true;
        }

        if (feof(f_old))
        {
            break;
        }

        //# next line
        memset(char_buf, 0, sizeof(char_buf));
        fgets(char_buf, sizeof(char_buf) - 1, f_old);
        ++line;
    }

    fclose(f_new);
    fclose(f_old);

    DeleteFile(tmp_path.c_str());

    if (file_changed)
    {
        func_update_copyright(file_path);
    }
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
    cout << "Please input file suffix, separated by space :" << endl;
    getline(cin, input);
    input += " ";

    i = -1;
    string tmp_suffix = "";

    while (++i < input.size())
    {
        if ((input[i] >= 'a' && input[i] <= 'z') ||
            (input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= '0' && input[i] <= '9') ||
            (input[i] == '_'))
        {
            tmp_suffix += input[i];
        }
        else
        {
            if (tmp_suffix.size() > 0)
            {
                search_file_suffix.push_back(tmp_suffix);
                tmp_suffix.clear();
            }
        }
    }

    if (search_file_suffix.size() == 0)
    {
        search_file_suffix = default_file_suffix;
        cout << "No designated file suffix input, use default suffix formats." << endl;
    }

    cout << "Search for files formats :" << endl;
    for (auto &s : search_file_suffix)
    {
        search_suffix_set.insert(s);
        cout << "    ." << s << endl;
    }

    cout << endl;

    //# input whether enable Print Traversed File
    input.clear();
    cout << "Do you want \"Print Traversed File\" operation ?" << " enter Y/N :";
    getline(cin, input);
    if (input == "Y" || input == "y")
    {
        print_traversed_file = true;
        cout << "\"Print Traversed File\" ENABLED." << endl;
    }
    else
    {
        print_traversed_file = false;
        cout << "\"Print Traversed File\" DISABLED." << endl;
    }

    cout << endl;

    //# input whether enable Count Valid Lines
    input.clear();
    cout << "Do you want \"Count Valid Lines\" operation ?" << " enter Y/N :";
    getline(cin, input);
    if (input == "Y" || input == "y")
    {
        count_valid_lines = true;
        cout << "\"Count Valid Lines\" ENABLED." << endl;
    }
    else
    {
        count_valid_lines = false;
        cout << "\"Count Valid Lines\" DISABLED." << endl;
    }

    cout << endl;

    //# input whether enable Transfer Tab to Spaces
    input.clear();
    cout << "Do you want \"Transfer Tab to Spaces\" operation ?" << " enter Y/N :";
    getline(cin, input);
    if (input == "Y" || input == "y")
    {
        tansfer_tab2space = true;
        cout << "\"Transfer Tab to Spaces\" ENABLED." << endl;
    }
    else
    {
        tansfer_tab2space = false;
        cout << "\"Transfer Tab to Spaces\" DISABLED." << endl;
    }

    cout << endl;

    //# input whether enable Delete Tail Spaces
    input.clear();
    cout << "Do you want \"Delete Tail Spaces\" operation ?" << " enter Y/N :";
    getline(cin, input);
    if (input == "Y" || input == "y")
    {
        delete_tail_space = true;
        cout << "\"Delete Tail Spaces\" ENABLED." << endl;
    }
    else
    {
        delete_tail_space = false;
        cout << "\"Delete Tail Spaces\" DISABLED." << endl;
    }

    cout << endl;

    iterate_folder(execute_folder_path);
    system("pause");
    return 0;
}

