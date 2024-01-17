#pragma once
#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <set>

# define LIB_OPTIONS_DEFAULT_KEY "default"

/*
| liboptions
| 
|  このライブラリはプログラム開始時の引数を読み込みオプションデータとして取り扱うものである
*/

class Options{
    public:
        // キー情報を保持する変数
        typedef std::map <uint8_t, std::set <std::string>> Keys;
        // オプションの引数情報を複数保持する変数
        typedef std::vector <std::string> Values;
        // オプションの引数情報を保持する変数
        typedef std::string Value;

    private:
        // 代入されたオプションパスから現在のファイルパスを特定する
        std::string file_path_;
        // オプション情報を代入する変数
        // std::map <(オプションの [-] の長さ), std::map <(オプション名), std::vector <(オプション引数)>>>
        std::map <uint8_t, std::map <std::string, Values>> options_;

    public:
        // 初期化する
        Options (void);

        // 初期化時にオプション情報を代入する
        // 1: const int -> オプションの配列の長さを指定する
        // 2: char * -> オプション情報を入れる
        Options (const int argc, char *argv[]);

        // デストラクタ
        ~Options (void);

    public:
        // オプションを設定する
        // 1: const int -> オプションの配列の長さを指定する
        // 2: char * -> オプション情報を入れる
        void set (const int argc, char *argv[]) noexcept;

        // オプション情報を取得する (引数なし)
        // 1: const uint8_t -> オプションの [-] の長さ
        // 2: const std::string& -> オプションのキーの情報
        // r: true -> 処理が正常に終了しました
        // r: false -> 指定されたオプションの長さとキーの長さに一致するものを見つけることができませんでした
        bool getFlag (const uint8_t bar, const std::string &key) const noexcept;

        // オプション情報を取得する (引数あり)
        // 1: const uint8_t -> オプションの [-] の長さ
        // 2: const std::string& -> オプションのキーの情報
        // 3: Options::Values& -> 指定したキーの引数の情報を取得する
        // r: true -> 処理が正常に終了しました
        // r: false -> 指定されたオプションの長さとキーの長さに一致するものを見つけることができませんでした
        bool getValues (const uint8_t bar, const std::string &key, Options::Values &values) const noexcept;

        // オプションのキー情報を取得する
        void getKey (Keys &keys) const noexcept;

        // オプションに指定されていたファイルの現状パスから絶対パスを求める
        // 1: std::string& -> 取得したファイルパスを入れる変数
        // r: true -> 処理が正常に終了しました
        // r: false -> オプションが設定されていないため取得することができませんでした
        bool getAbsFilePath (std::string &file_path)const noexcept;

        // オプションに指定されていたファイルの現状パスからディレクトリパスを求める
        // 1: std::string& -> 取得したディレクトリパスを入れる変数
        // r: true -> 処理が正常に終了しました
        // r: false -> オプションが設定されていないため取得することができませんでした
        bool getAbsDirPath (std::string &directory_path)const noexcept;

        // 情報をクリアする
        void clear (void) noexcept;
    private:
        // 相対パスから絶対パスに変換する
        // 1: const std::string& -> 変換したい相対パス
        // 2: std::string& -> 変換した値を代入する変数
        static void relativeToAbsolute (const std::string &relative, std::string &absolute) noexcept;
};
