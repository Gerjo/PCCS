// foldertoproject.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

string g_ProjectFile;
string g_FilterFile;
string g_UnfilteredFile;

vector<string> directory_list(string searchPath) {
    searchPath += "/*";
    WIN32_FIND_DATAA directoryData;
    HANDLE directoriesFound = FindFirstFileA(searchPath.c_str(), &directoryData);

    vector<string> directories;
    do {
        if(strncmp(directoryData.cFileName, ".", 2) == 0 || strncmp(directoryData.cFileName, "..", 3) == 0) {
            continue;
        }
        if(directoryData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            directories.push_back(directoryData.cFileName);
        }

    } while(FindNextFileA(directoriesFound, &directoryData) != 0);

    FindClose(directoriesFound);

    return directories;
}

vector<string> file_list(string searchPath) {
    searchPath += "/*";

    WIN32_FIND_DATAA fileData;
    HANDLE filesFound = FindFirstFileA(searchPath.c_str(), &fileData);

    vector<string> files;
    do {
        if(strncmp(fileData.cFileName, ".", 2) == 0 || strncmp(fileData.cFileName, "..", 3) == 0) {
            continue;
        }
        if(fileData.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) {
            files.push_back(fileData.cFileName);
        }
    } while (FindNextFileA(filesFound, &fileData) != 0);

    FindClose(filesFound);

    return files;
}

void readfile(string *path, string *location) {
    FILE *file;
    fopen_s(&file, path->c_str(), "r");

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    char *buffer = new char[size + 1];
    size = fread_s(buffer, size + 1, sizeof(char), size + 1, file);
    buffer[size] = '\0';

    fclose(file);
    *location += buffer;

    delete [] buffer;
}

void writefile(string *path, string *data) {
    FILE *file;
    fopen_s(&file, path->c_str(), "w");
    fwrite(data->c_str(), 1, data->length(), file);
    fclose(file);
}

void iterate_filter_directory(string path, string prevFilterName) {
    vector<string> directories = directory_list(path);

    for(string dir : directories) {
        string filterpath;
        if(prevFilterName != "")
            filterpath = prevFilterName + "\\" + dir;
        else
            filterpath = dir;
        g_FilterFile += "    <Filter Include=\"" + filterpath + "\">\n      <Extensions>cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx;h;hpp;hxx;hm;inl;inc;xsd</Extensions>\n    </Filter>\n";
    }

    for(string dir : directories) {
        if(prevFilterName != "") {
            iterate_filter_directory(path + "\\" + dir, prevFilterName + "\\" + dir);
        }
        else {
            iterate_filter_directory(path + "\\" + dir, dir);
        }
    }
}

void iterate_source_directory(string path, string prevFilterName) {
    vector<string> allfiles = file_list(path);
    vector<string> files;

    for(string s : allfiles) {
        if(s.find(".h") != string::npos || s.find(".cpp") != string::npos || s.find(".inl") != string::npos) {
            files.push_back(s);
        }
    }

    if(!files.empty()) {
        g_ProjectFile += "  <ItemGroup>\n";
        for (string s : files) {
            if (s.find(".h") != string::npos || s.find(".inl") != string::npos)
                g_ProjectFile += "   <ClInclude Include=\"" + path + "\\" + s + "\" />\n";
            else if (s.find("pch.cpp") != string::npos || s.find("stdafx.cpp") != string::npos) {
                g_ProjectFile += "   <ClCompile Include=\"" + path + "\\" + s + "\">\n      <PrecompiledHeader>Create</PrecompiledHeader>\n    </ClCompile>\n";
            } else {
                g_ProjectFile += "   <ClCompile Include=\"" + path + "\\" + s + "\" />\n";
            }
            
        }
        g_ProjectFile += "  </ItemGroup>\n";

        for (string s : files) {
            if (prevFilterName != "") {
                if (s.find(".h") != string::npos || s.find(".inl") != string::npos) {
                    g_FilterFile += "    <ClInclude Include=\"" + path + "\\" + s + "\">\n";
                    g_FilterFile += "      <Filter>" + prevFilterName + "</Filter>\n";
                    g_FilterFile += "    </ClInclude>\n";
                }
                else {
                    g_FilterFile += "    <ClCompile Include=\"" + path + "\\" + s + "\">\n";
                    g_FilterFile += "      <Filter>" + prevFilterName + "</Filter>\n";
                    g_FilterFile += "    </ClCompile>\n";
                }
            }
            else {
                if (s.find(".h") != string::npos || s.find(".inl") != string::npos)
                    g_UnfilteredFile += "    <ClInclude Include=\"" + path + "\\" + s + "\" />\n";
                else
                    g_UnfilteredFile += "    <ClCompile Include=\"" + path + "\\" + s + "\" />\n";
            }
        }
    }

    vector<string> directoryEntries = directory_list(path);
    for (string s : directoryEntries) {
        if (prevFilterName != "")
            iterate_source_directory(path + "\\" + s, prevFilterName + "\\" + s);
        else
            iterate_source_directory(path + "\\" + s, s);
    }
}

int main(int argc, char* argv[])
{
    if(argc == 0) {
        printf("Syntax: \"src\" \"src\" \"projectfile\"");
        return 0;
    }

    string *targetSourceDirectory = new string[argc-2];
    int totalSourceDirectories = 0;
    for(int i = 0; i < argc - 2; ++i) {
        targetSourceDirectory[i] = string(argv[i+1]);
        ++totalSourceDirectories;
    }

    string projectfilelocation = string(argv[argc-1]);
    string::size_type i = projectfilelocation.find_last_of("\\");
    string projectfilepath = projectfilelocation.substr(0, i);

    readfile(&(projectfilepath + string("\\pf0.xml")), &g_ProjectFile);
    g_ProjectFile += '\n';
    g_FilterFile += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n";
    g_FilterFile += "  <ItemGroup>\n";

    for(int i = 0; i < totalSourceDirectories; ++i) {
        iterate_filter_directory(targetSourceDirectory[i], "");
    }

    g_FilterFile += "  </ItemGroup>\n";
    g_FilterFile += "  <ItemGroup>\n";

    for(int i = 0; i < totalSourceDirectories; ++i) {
        iterate_source_directory(targetSourceDirectory[i], "");
    }

    g_FilterFile += g_UnfilteredFile;
    g_FilterFile += "  </ItemGroup>\n</Project>";

    readfile(&(projectfilepath + string("\\pf1.xml")), &g_ProjectFile);

    writefile(&projectfilelocation, &g_ProjectFile);
    writefile(&(projectfilelocation + ".filters"), &g_FilterFile);


    delete [] targetSourceDirectory;
    return 0;
}

