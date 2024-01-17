#include "check_options.h"

CheckOptions::CheckOptions (void) noexcept{

}

CheckOptions::~CheckOptions (void) noexcept{

}

bool CheckOptions::setOptions(int argc, char *argv[]){
    bool flag;
    Options opt;
    Options::Keys keys;
    Options::Values values;

    opt.set (argc, argv);

    opt.getKey (keys);

    opt.getAbsDirPath (this->abs_dir_path_);

    try{
        // フラグ系の値を取得する
        flag = this->checkViewOptions (opt, keys);
        if (!flag){
            return flag;
        }

        flag = this->checkCreateConfigOptions (opt, keys);
        if (!flag){
            // 無駄な引数が含まれています
            throw CheckOptionsException ("Includes useless options.");
        }

        flag = this->checkConfigOptions (opt, keys);
        if (!flag){
            // 無駄な引数が含まれています
            throw CheckOptionsException ("Includes useless options.");
        }

        return flag;
    }catch (const CheckOptionsException &e){
        throw e;
    }
}

bool CheckOptions::getVersionFlag(void) const noexcept{
    return this->version_flag_;
}

bool CheckOptions::getHelpFlag(void) const noexcept{
    return this->help_flag_;
}

const std::string &CheckOptions::getConfigFilePath (void) const noexcept{
    return this->config_file_path_;
}

const std::vector<std::string> &CheckOptions::getCreateConfigFilePath(void) const noexcept{
    // TODO: insert return statement here
    return this->create_config_file_path_;
}

bool CheckOptions::checkViewOptions(const Options &opt, Options::Keys &keys){
    bool flag;
    uint8_t bar;
    Options::Values values;

    // バージョンフラグが立っているかを確かめる
    this->version_flag_ = false;

    flag = opt.getValues ((bar = 1), OPT_VERSION_1, values);
    if (flag){
        if (!values.empty ()){
            // 引数情報が含まれてはいてほしくありません
            throw CheckOptionsException ("Do not specify any arguments for the version option.");
        }
        keys[bar].erase (OPT_VERSION_1);

        if (!this->version_flag_){
            this->version_flag_ = true;
        }
    }

    flag = opt.getValues ((bar = 2), OPT_VERSION_2, values);
    if (flag){
        if (!values.empty ()){
            // 引数情報が含まれてはいてほしくありません
            throw CheckOptionsException ("Do not specify any arguments for the version option.");
        }
        keys[bar].erase (OPT_VERSION_2);

        if (!this->version_flag_){
            this->version_flag_ = true;
        }
    }

    // ヘルプフラグが立っているかを確かめる
    this->help_flag_ = false;

    flag = opt.getValues ((bar = 1), OPT_HELP_1, values);
    if (flag){
        if (!values.empty ()){
            // 引数情報が含まれてはいてほしくありません
            throw CheckOptionsException ("Do not specify any arguments for the help option.");
        }
        keys[bar].erase (OPT_HELP_1);

        if (!this->help_flag_){
            this->help_flag_ = true;
        }
    }

    flag = opt.getValues ((bar = 2), OPT_HELP_2, values);
    if (flag){
        if (!values.empty ()){
            // 引数情報が含まれてはいてほしくありません
            throw CheckOptionsException ("Do not specify any arguments for the help option.");
        }
        keys[bar].erase (OPT_HELP_2);

        if (!this->help_flag_){
            this->help_flag_ = true;
        }
    }
    if (this->version_flag_ || this->help_flag_){
        for (const auto &v1 : keys){
            if (!v1.second.empty ()){
                throw CheckOptionsException ("Do not use the display and creation options at the same time.");
            }
        }
    }else{
        flag = false;
        for (const auto &v1 : keys){
            if (!v1.second.empty ()){
                flag = true;
                break;
            }
        }
        if (!flag){
            // バージョンとヘルプ情報を表示させる
            this->version_flag_ = true;
            this->help_flag_ = true;
        }else{
            return true;
        }
    }

    return false;
}

bool CheckOptions::checkCreateConfigOptions(const Options &opt, Options::Keys &keys){
    bool flag;
    uint8_t bar;
    Options::Values values;

    flag = opt.getValues ((bar = 1), OPT_CREATE_CONFIG_FILE_PATH_1, values);
    if (flag){
        if (!values.empty ()){
            this->create_config_file_path_.insert (this->create_config_file_path_.end (), values.begin (), values.end ());
        }

        keys[bar].erase (OPT_CREATE_CONFIG_FILE_PATH_1);
    }

    flag = opt.getValues ((bar = 2), OPT_CREATE_CONFIG_FILE_PATH_2, values);
    if (flag){
        if (!values.empty ()){
            this->create_config_file_path_.insert (this->create_config_file_path_.end (), values.begin (), values.end ());
        }

        keys[bar].erase (OPT_CREATE_CONFIG_FILE_PATH_2);
    }

    flag = true;
    if (!this->create_config_file_path_.empty ()){
        for (const auto &v1 : keys){
            if (!v1.second.empty ()){
                flag = false;
            }
        }
    }

    return flag;
}

bool CheckOptions::checkConfigOptions(const Options &opt, Options::Keys &keys){
    bool flag;
    uint8_t bar;
    Options::Values values;

    flag = opt.getValues ((bar = 1), OPT_CONFIG_FILE_PATH_1, values);
    if (flag){
        if (values.size () == 1){
            this->config_file_path_ = *values.begin ();
        }else{
            throw CheckOptionsException ("There was more than one path to the configuration file.");
        }
        
        keys[bar].erase (OPT_CONFIG_FILE_PATH_1);
    }

    flag = opt.getValues ((bar = 2), OPT_CONFIG_FILE_PATH_2, values);
    if (flag){
        if (values.size () == 1 && this->config_file_path_.empty ()){
            this->config_file_path_ = *values.begin ();
        }else{
            throw CheckOptionsException ("There was more than one path to the configuration file.");
        }

        keys[bar].erase (OPT_CONFIG_FILE_PATH_2);
    }

    flag = true;
    for (const auto &v1 : keys){
        if (!v1.second.empty ()){
            flag = false;
        }
    }
    return flag;
}
