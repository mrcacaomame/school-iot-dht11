#pragma once

// プログラム情報
#define PROGRAME_NAME "iot"
#define PROGRAME_VERSION "1.0"

// コンソールカラー
#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"      /* Black */
#define COLOR_RED     "\033[31m"      /* Red */
#define COLOR_GREEN   "\033[32m"      /* Green */
#define COLOR_YELLOW  "\033[33m"      /* Yellow */
#define COLOR_BLUE    "\033[34m"      /* Blue */
#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_CYAN    "\033[36m"      /* Cyan */
#define COLOR_WHITE   "\033[37m"      /* White */
#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// オプションの種類

// バージョン -
#define OPT_VERSION_1 "v"
// バージョン --
#define OPT_VERSION_2 "version"
// ヘルプ -
#define OPT_HELP_1 "h"
// ヘルプ --
#define OPT_HELP_2 "help"

// 設定ファイルを作成する
#define OPT_CREATE_CONFIG_FILE_PATH_1 "cc"
// 設定ファイルを作成する
#define OPT_CREATE_CONFIG_FILE_PATH_2 "create-config-file-path"

// 設定ファイルのパス
#define OPT_CONFIG_FILE_PATH_1 "c"
// 設定ファイルのパス
#define OPT_CONFIG_FILE_PATH_2 "config-file-path"

// 設定ファイル

// 気温・湿度の取得間隔 (単位)
#define CONF_INTERVAL_MINUTES "INTERVAL_MILISEC"

// ピン番号
#define CONF_DHT11_PIN "DHT11_PIN"

// データベースのホスト名
#define CONF_DB_HOSTNAME "DB_HOSTNAME"

// データベースのポート番号
#define CONF_DB_PORT "DB_PORT"

// データベースのユーザ名
#define CONF_DB_USERNAME "DB_USERNAME"

// データベースのパスワード
#define CONF_DB_PASSWORD "DB_PASSWORD"

// データベースのデータベース名
#define CONF_DB_DATABASE "DB_DATABASE"
