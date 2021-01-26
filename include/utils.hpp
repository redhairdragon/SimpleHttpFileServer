#ifndef UTILS_H
#define UTILS_H

#include <string>

using std::string;
long get_file_size(string filename);
string lowered_string(const string& str);
string get_file_extension(const string& filename);
string get_file_type(const string& filename);
std::string unescape(const std::string& in);

#endif
