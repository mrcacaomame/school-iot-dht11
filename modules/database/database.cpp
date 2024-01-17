#include "database.h"

void Database::setConfig(const Config &conf) noexcept{
    conf.get (CONF_DB_HOSTNAME, this->host_name_);
    conf.get (CONF_DB_PORT, this->port_);
    conf.get (CONF_DB_USERNAME, this->user_name_);
    conf.get (CONF_DB_PASSWORD, this->password_);
    conf.get (CONF_DB_DATABASE, this->database_);
}

void Database::insertData(const RaspberryPi::DHT11_DATA &dht11_data){
    std::string sql;
    bool flag;

    try{
        Postgresql psql;
        // 情報を設定する
        psql.setHostName (this->host_name_);
        psql.setPort (std::stoi (this->port_));
        psql.setUserName (this->user_name_);
        psql.setPassword (this->password_);
        psql.setDatabase (this->database_);

        // データベースと接続を試みる
        psql.connect ();

        sql = (std::string)"INSERT INTO info ("
            + (std::string)"hum,"
            + (std::string)"tem"
            + (std::string)") VALUES "
            // + (std::string)"("+std::to_string (dht11_data.hum)+", "+std::to_string (dht11_data.tem)+");";
            + (std::string)"("+std::to_string (dht11_data.hum)+","+std::to_string (dht11_data.tem)+");";

        flag = psql.exec (sql);
        if (!flag){
            throw DatabaseException ("Database insert failed.");   
        }

        psql.clear ();
    }catch (const PostgresqlException &e){
        throw DatabaseException (e.what ());
    }catch (const std::invalid_argument &e){
        throw DatabaseException (e.what ());
    }
}
