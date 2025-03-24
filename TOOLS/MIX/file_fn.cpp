#include <sstream>
#include <cstring>

#include "mixfile.h"

void fnmerge(char *dest, const char *drive, const char *path, const char *file, const char *ext) {
    std::ostringstream oss;

    if (drive && *drive) {
        oss << drive;
        if (*(drive + strlen(drive) - 1) != ':') {
            oss << ':';
        }
    }

    if (path && *path) {
        oss << path;
        if (*(path + strlen(path) - 1) != '/' && *(path + strlen(path) - 1) != '\\') {
            oss << '/';
        }
    }

    if (file && *file) {
        oss << file;
    }

    if (ext && *ext) {
        if (*ext != '.') {
            oss << '.';
        }
        oss << ext;
    }

    std::string result = oss.str();
    strcpy(dest, result.c_str());
}

void fnsplit(const char *path, char *drive, char *dir, char *fname, char *ext) {
    std::string p(path);
    std::string::size_type pos1 = p.find(':');
    std::string::size_type pos2 = p.find_last_of("/\\");
    std::string::size_type pos3 = p.find_last_of('.');

    if (pos1 != std::string::npos) {
        if (drive) {
            strncpy(drive, p.substr(0, pos1 + 1).c_str(), MAXDRIVE);
        }
        pos1++;
    } else {
        pos1 = 0;
    }

    if (pos2 != std::string::npos) {
        if (dir) {
            strncpy(dir, p.substr(pos1, pos2 - pos1 + 1).c_str(), MAXDIR);
        }
        pos2++;
    } else {
        pos2 = pos1;
        if (dir) {
            dir[0] = '\0';
        }
    }

    if (pos3 != std::string::npos && pos3 > pos2) {
        if (fname) {
            strncpy(fname, p.substr(pos2, pos3 - pos2).c_str(), MAXFILE);
        }
        if (ext) {
            strncpy(ext, p.substr(pos3).c_str(), MAXEXT);
        }
    } else {
        if (fname) {
            strncpy(fname, p.substr(pos2).c_str(), MAXFILE);
        }
        if (ext) {
            ext[0] = '\0';
        }
    }
}

