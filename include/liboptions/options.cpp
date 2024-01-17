#include "options.h"

Options::Options(void){

}

Options::Options(const int argc, char *argv[]){
    this->set (argc, argv);
}

Options::~Options(void){

}

void Options::set(const int argc, char *argv[]) noexcept{
    std::map <uint8_t, std::map <std::string, std::vector <std::string>>>().swap (this->options_);
    
    std::string &absolute_file_path = this->file_path_;
    std::string relative_file_path = argv[0];

    std::string key = LIB_OPTIONS_DEFAULT_KEY;
    std::string value;
    uint8_t count = 1;

    std::map<uint8_t, std::map<std::string, Options::Values>>::const_iterator iter1;

    this->relativeToAbsolute (relative_file_path, absolute_file_path);

    for (int j = 1; j < argc; j ++){
        char *argv_p = &argv[j][0];
        if (*argv_p == '-'){
            count = 1;
            size_t c_len = strlen (argv[j]);
            if (c_len >= 1){
                argv_p ++;
            }
            for (int j = 1; j < c_len; j ++){
                if (*argv_p == '-'){
                    argv_p ++;
                    count ++;
                }else{
                    break;
                }
            }
            key = argv_p;
            if ((iter1 = this->options_.find (count)) != this->options_.end ()){
                if (iter1->second.find (key) != iter1->second.end ()){
                    continue;
                }
            }

            this->options_[count][key] = Options::Values ();
        }else{
            value = argv[j];
            this->options_[count][key].emplace_back (value);
        }
    }
}

bool Options::getFlag(const uint8_t bar, const std::string &key) const noexcept{
    std::map <uint8_t, std::map <std::string, std::vector <std::string>>>::const_iterator f_iter;
    std::map <std::string, std::vector <std::string>>::const_iterator s_iter;
    if ((f_iter = this->options_.find (bar)) == this->options_.end ()){
        return false;
    }
    if ((s_iter = f_iter->second.find (key)) == f_iter->second.end ()){
        return false;
    }
    return true;
}

bool Options::getValues(const uint8_t bar, const std::string &key, Options::Values &values) const noexcept{
    std::map <uint8_t, std::map <std::string, std::vector <std::string>>>::const_iterator f_iter;
    std::map <std::string, std::vector <std::string>>::const_iterator s_iter;
    if ((f_iter = this->options_.find (bar)) == this->options_.end ()){
        return false;
    }
    if ((s_iter = f_iter->second.find (key)) == f_iter->second.end ()){
        return false;
    }
    values = s_iter->second;
    return true;
}

void Options::getKey(Keys &keys) const noexcept{
    keys.clear ();

    for (const auto &v1 : this->options_){
        for (const auto &v2 : v1.second){
            keys[v1.first].insert (v2.first);
        }
    }
}

bool Options::getAbsFilePath(std::string &file_path) const noexcept{
    if (this->file_path_.empty ()){
        return false;
    }
    file_path = this->file_path_;
    return true;
}

bool Options::getAbsDirPath(std::string &directory_path) const noexcept{
    if (this->file_path_.empty ()){
        return false;
    }
    directory_path = std::filesystem::path (this->file_path_).parent_path ().string ();
    // directory_path.erase (directory_path.begin () + directory_path.length () - 1);
    return true;
}

void Options::clear(void) noexcept{
    this->options_.clear ();
    this->file_path_.clear ();
}

void Options::relativeToAbsolute(const std::string &relative, std::string &absolute) noexcept{
    std::filesystem::path result = std::filesystem::absolute (relative);
    absolute = result.string ();
}
