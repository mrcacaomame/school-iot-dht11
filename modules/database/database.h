#pragma once
#include "database_exception.h"
#include <string>

#include "libconfig/config.h"

#include "define/define.h"
#include "raspberry_pi/raspberry_pi.h"
#include "libpostgresql/postgresql.h"

class Database{
    private:
        // ホスト名
        std::string host_name_;
        // ポート番号
        std::string port_;
        // ユーザ名
        std::string user_name_;
        // パスワード
        std::string password_;
        // データベース名
        std::string database_;

    
    public:
        // データベースの基本情報を設定する
        // 1: const Config& -> データベースの情報
        // r: throw: 
        void setConfig (const Config &conf) noexcept;

    public:
        // データベースに情報を代入する
        void insertData (const RaspberryPi::DHT11_DATA &dht11_data);

};
