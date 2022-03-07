#ifndef FILES_IN_DIRECTORY_F
#define FILES_IN_DIRECTORY_F

#include <vector>
#include <string>
#include <algorithm>
#include <dirent.h>

std::vector<std::string> files_in_directory(std::string directory)
{
    std::vector<std::string> files;

    // open directory
    DIR *dir;
    dir = opendir(directory.c_str());
    if (dir == NULL)
        return files;

    // get file names
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL)
        files.push_back(ent->d_name);
    closedir(dir);

    // delete current and parent directories
    files.erase(std::find(files.begin(), files.end(), "."));
    files.erase(std::find(files.begin(), files.end(), ".."));

    // sort in alphabetical order
    std::sort(files.begin(), files.end());

    return files;
}

#endif