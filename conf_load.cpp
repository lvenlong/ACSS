#include <iostream>
#include <fstream>
#include <string>
#include "conf_load.h"
#include "conf_unit.h"
#include "string_util.h"
#include "exception.h"
#include <stdio.h>

namespace bigpipe {
/*bool ConfLoader::load_conf(const std::string& conf_file, ConfUnit& conf_unit)
{
    if (conf_file.empty()) {
        std::cerr << "error:load_conf:conf filename cann't be empty" << std::endl;
        return false;
    }

    if (!conf_unit.is_group()) {
        std::cerr << "error: load_conf: The 3rd argument need to be (bigpipe::ConfUnit::UT_GROUP)" << std::endl;
        return false;
    }

    try {
        ConfLoader conf_parser;
        conf_parser.parse(conf_file, conf_unit);
    } catch (bigpipe::ConfigurationException& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}*/

const int32_t ConfLoader::MAX_LINE_LEN = 512;

ConfUnit* ConfLoader::load_conf(const char* conf_filename)
{
    std::ifstream conf_file(conf_filename, std::ifstream::in);
    if (conf_file.fail()) {
        return NULL;
    }

    char line[MAX_LINE_LEN];
    ConfUnit* root = new(std::nothrow) ConfUnit(ConfUnit::UT_GROUP);
    if (NULL != root) {
        ConfUnit* current = root;
        while (conf_file.good()) {
            conf_file.getline(line, MAX_LINE_LEN);

            if (bigpipe::ConfLoader::is_white_line(line) || bigpipe::ConfLoader::is_comment_line(line)) {
                continue;
            }

            if (0 != bigpipe::ConfLoader::handle_line(line, root, current)) {
                delete root;
                root = NULL;
                break;
            }
        }
    }

    conf_file.close();
    return root;
}


/*void ConfLoader::parse(const std::string& conf_filename, ConfUnit& conf_unit)
{
    _filename = conf_filename;
    std::ifstream conf_file(conf_filename.c_str());

    if (!conf_file) {
        throw bigpipe::ConfigurationException("failed to open conf file: " + conf_filename);
    }

    parse(conf_file, conf_unit);
    conf_file.close();
}*/

/*void ConfLoader::parse(std::ifstream& conf_file, ConfUnit& conf_unit)
{
    if (conf_file.fail()) {
        throw bigpipe::ConfigurationException("failed to parse conf file: " + _filename);
    }

    char line[MAX_LINE_LEN];
    ConfUnit* current = &conf_unit;

    while (conf_file.good()) {
        conf_file.getline(line, MAX_LINE_LEN);

        if (is_white_line(line) || is_comment_line(line)) {
            continue;
        }

        if (0 != handle_line(&line, conf_unit, current)) {
            break;
        }
    }
}*/

bool ConfLoader::is_white_line(const char* line)
{
    if (NULL == line) {
        return false;
    } else {
        return bigpipe::StringUtil::trim(line).empty();
    }
}

bool ConfLoader::is_comment_line(const char* line)
{
    if (NULL == line) {
        return false;
    } else {
        std::string line_trimed = bigpipe::StringUtil::ltrim(line);
        return !line_trimed.empty() && ('#' == line_trimed[0]);
    }
}

int32_t ConfLoader::handle_line(const char* line, ConfUnit* root, ConfUnit*& current)
{
    if (NULL == root || NULL == current) {
        return -1;
    }
    std::vector<std::string> paths;
    std::string key;
    std::string value;

    if (0 == handle_as_section(line, paths)) {
        if (0 == paths.size()) {
            return -1;
        }
        current = push_section(root, paths);
        if (NULL == current) {
            return -1;
        }
    } else if (0 == handle_as_item(line, key, value)) {
        if (0 != push_item(current, key, value)) {
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

int32_t ConfLoader::handle_as_section(const char* line, std::vector<std::string>& paths)
{
    paths.clear();
    std::string line_trimed = bigpipe::StringUtil::trim(line);
    int32_t size = (int32_t)line_trimed.size();
    if (size < 2 || '[' != line_trimed[0] || ']' != line_trimed[size - 1]) {
        return -1;
    }

    line_trimed = line_trimed.substr(1, size - 2);
    size -= 2;

    std::vector<std::string> v;
    bigpipe::StringUtil::split_string(line_trimed, ".", v, false);
    if (0 == v.size()) {
        return -1;
    }

    std::vector<std::string>::iterator itr;
    for (itr = v.begin(); itr != v.end(); ++itr) {
        std::string s = bigpipe::StringUtil::trim(*itr);
        if (s.empty()) {
            return -1;
        } else {
            paths.push_back(s);
        }
    }

    std::vector<std::string>::reverse_iterator ritr;
    ritr = paths.rbegin();
    if (ritr != paths.rend()) {
    ++ritr;
    while (ritr != paths.rend()) {
            if ('@' == (*ritr)[0]) {
                paths.clear();
                return -1;
            }
            ++ritr;
        }
    }
    return 0;
}

int32_t ConfLoader::handle_as_item(const char* line, std::string& key, std::string& value)
{
    std::string line_trimed = bigpipe::StringUtil::trim(line);
    std::string::size_type pos = line_trimed.find_first_of('=');
    if (std::string::npos == pos) {
        return -1;
    } else {
        key = bigpipe::StringUtil::trim(line_trimed.substr(0, pos));
        if (key.empty()) {
            return -1;
        }
        if (pos != line_trimed.size() - 1) {
            value = bigpipe::StringUtil::trim(line_trimed.substr(pos + 1));
        } else {
            value = "";
        }

        return 0;
    }
}

ConfUnit* ConfLoader::push_section(ConfUnit* root, const std::vector<std::string>& paths)
{
    int32_t size = (int32_t)paths.size();
    if (0 == size) {
        return NULL;
    }

    ConfUnit* current = root;
    ConfUnit* son = NULL;
    for (int32_t i = 0; i < size - 1; ++i) {
        if (!current -> is_group() || '@' == paths[i][0]) {
            return NULL;
        }
        son = (*current)[paths[i]];
        if (NULL == son) {
            current->insert(paths[i], new(std::nothrow) ConfUnit(ConfUnit::UT_GROUP));
            son = (*current)[paths[i]];
            if (NULL == son) {
                return NULL;
            }
        }
        current = son;
    }

    if (!current->is_group()) {
        return NULL;
    }

    if ('@' == paths[size - 1][0]) {
    std::string p = paths[size - 1].substr(1);
        son = (*current)[p];
        if (NULL != son) {
            if (!son->is_array()) {
                return NULL;
            }
            return son->push_back(new(std::nothrow) ConfUnit(ConfUnit::UT_GROUP));
        }

        current->insert(p, new(std::nothrow) ConfUnit(ConfUnit::UT_ARRAY));
        son = (*current)[p];
        if (NULL == son || !son -> is_array()) {
            return NULL;
        }
        return son->push_back(new(std::nothrow) ConfUnit(ConfUnit::UT_GROUP));
    } else {
        son = (*current)[paths[size - 1]];
        if (NULL != son ) {
            return NULL;
        }
        current->insert(paths[size - 1], new(std::nothrow) ConfUnit(ConfUnit::UT_GROUP));
        son = (*current)[paths[size - 1]];
        return son;
    }
}

int32_t ConfLoader::push_item(ConfUnit* current, const std::string& key, const std::string& value)
{
    if (NULL == current) {
        return -1;
    }

    ConfUnit* tmp = (*current)[bigpipe::StringUtil::trim(key)];
    if (NULL != tmp) {
        return -1;
    }
    current->insert(bigpipe::StringUtil::trim(key), new(std::nothrow) ConfUnit(bigpipe::StringUtil::trim(value)));
    return 0;
}
}
