#pragma once
#include <string>

// include
#include "liboptions/options.h"
#include "libconfig/config.h"
#include "define/define.h"

// modules
#include "define/define.h"

#include "check_options_exception.h"

#pragma once
#include "check_options_exception.h"
#include "liboptions/options.h"
#include "define/define.h"

#include <stdint.h>

class CheckOptions{
    private: // Space to hold variables for use in classes.
        // ディレクトリのカレントパス
        std::string abs_dir_path_;
        // ATRSデータファイルパス
        std::string atrs_file_path_;
        // output_directory_path
        std::string output_dir_path_;
        // urlの値
        std::string url_;
        // 設定ファイルのパス
        std::string config_file_path_;
        // 作成する設定ファイルパス
        std::vector <std::string> create_config_file_path_;
        // スレッド数
        uint16_t max_thread_;

        // バージョンフラグ
        bool version_flag_;
        // ヘルプフラグ
        bool help_flag_;
        
    public:  // Space for operator.
        // CheckOptions &operator= (const CheckOptions &op) noexcept;
        // CheckOptions &operator+ (const CheckOptions &op);
        // CheckOptions &operator- (const CheckOptions &op);
        // CheckOptions &operator* (const CheckOptions &op);
        // CheckOptions &operator/ (const CheckOptions &op);


    public:  // Space for constructors and destructors.
        CheckOptions (void) noexcept;
        ~CheckOptions (void) noexcept;


    public:  // Space for public function.
        // オプション情報を設定する
        // 1: int -> オプションの数
        // 2: char*[] -> オプション
        // throw: CheckOptionsException
        bool setOptions (int argc, char *argv[]);
    
    public:
        // バージョンフラグを取得する
        // r: bool -> バージョンフラグ
        bool getVersionFlag (void) const noexcept;

        // ヘルプフラグを取得する
        // r: bool -> ヘルプフラグ
        bool getHelpFlag (void) const noexcept;



    public:
        // ログ情報を出力するファイルパスを取得する
        // r: const std::string& -> ログ情報を出力するディレクトリパス
        const std::string &getOutputDirectoryPath (void) const noexcept;

        // 設定ファイルのパスを取得する
        // r: const std::string& -> 設定ファイルのパス
        const std::string &getConfigFilePath (void) const noexcept;

        // 作成する設定ファイルのパスを取得する
        // r: const std::vector <std::string>& -> 作成する設定ファイルのパス
        const std::vector <std::string> &getCreateConfigFilePath (void) const noexcept;

        
    private: // Space for private function.
        // フラグ系の情報をチェックする
        // 1: const Options& -> オプション情報
        // 2: Optoins::Keys& -> キー情報
        // throw: CheckOptionsException
        bool checkViewOptions (const Options &opt, Options::Keys &keys);

        // 設定ファイルを作成するためのオプション情報をチェックする
        // 1: const Coptions& -> オプション情報
        // 2: Options::Keys& -> キー情報
        // throw: CheckOptionsException
        bool checkCreateConfigOptions (const Options &opt, Options::Keys &keys);


        // その他の設定系のオプション情報をチェックする
        // 1: const Coptions& -> オプション情報
        // 2: Options::Keys& -> キー情報
        // throw: CheckOptionsException
        bool checkConfigOptions (const Options &opt, Options::Keys &keys);

};
