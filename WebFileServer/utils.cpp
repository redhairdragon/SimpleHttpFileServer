#include <curl/curl.h>
#include <sys/stat.h>

#include <string>

#include "exceptions.h"

using std::string;

long get_file_size(string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) == 0) return st.st_size;
    throw FileRelatedException("Cannot get file size");
}

string lowered_string(const string& str) {
    string lowered = string(str);
    for (size_t i = 0; i < lowered.length(); i++)
        lowered[i] = tolower(lowered[i]);
    return lowered;
}

string get_file_extension(const string& filename) {
    size_t found = filename.find_last_of(".");
    if (found == string::npos) return ("");
    return lowered_string(filename.substr(found + 1));
}

string get_file_type(const string& filename) {
    string ext = get_file_extension(filename);
    if (ext == "jpg") return string("image/jpeg");
    if (ext == "txt") return string("text/plain");
    if (ext == "htm" || ext == "html") return string("text/html");
    if (ext == "jpeg") return string("image/jpeg");
    if (ext == "gif") return string("image/gif");
    return string("application/octet-stream");
}

std::string unescape(const std::string& in) {
    CURL* curl = curl_easy_init();
    int outLen;
    char* cres = curl_easy_unescape(curl, in.c_str(), in.length(), &outLen);
    std::string unescapedString(cres, outLen);
    curl_free(cres);
    curl_easy_cleanup(curl);
    return unescapedString;
}