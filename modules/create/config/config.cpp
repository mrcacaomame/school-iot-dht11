#include "config.h"

void create::config(const std::string &file_path){
    bool flag;
    std::filesystem::path dir_path;
    std::ofstream o_file;

    try{
        // ディレクトリのパスを取得する
        dir_path = std::filesystem::path (file_path).parent_path ();
        
        // ディレクトリがない場合は新規に作成する必要がある
        flag = (std::filesystem::exists (dir_path) && std::filesystem::is_directory (dir_path));
        if (!flag){
            flag = std::filesystem::create_directories (dir_path);
            if (!flag){
                throw CreateException ("Failed to read or create the configuration file directory. Please check the permissions of the parent. ("+dir_path.string ()+")");
            }
        }

        o_file.open (file_path, std::ios::out);

        // ファイルを開く
        if (!o_file){
            // ファイルを開くことに失敗しました
            throw CreateException ("Failed to load configuration file. Please check the permissions of the parent.");
        }

        o_file << "# Temperature and Humidity Acquisition Software Configuration File\n";
        o_file << "#\n";
        o_file << "\n";
        o_file << "# Interval for acquiring temperature and humidity (1 minute or more)\n";
        o_file << CONF_INTERVAL_MINUTES << "=\n";
        o_file << "\n";
        o_file << "# DHT11 pin number. (wPi (gpio readall))\n";
        o_file << CONF_DHT11_PIN << "=\n";
        o_file << "# Database Information Configuration\n";
        o_file << "#\n";
        o_file << "\n";
        o_file << "# Database Hostname\n";
        o_file << CONF_DB_HOSTNAME << "=localhost\n";
        o_file << "# Database Port Number\n";
        o_file << CONF_DB_PORT << "=5432\n";
        o_file << "# Database Username\n";
        o_file << CONF_DB_USERNAME << "=\n";
        o_file << "# Database User Password\n";
        o_file << CONF_DB_PASSWORD << "=\n";
        o_file << "# Database Name\n";
        o_file << CONF_DB_DATABASE << "=\n";


        // 閉じる
        o_file.close ();

    }catch (const std::filesystem::filesystem_error &e){
        // ファイル関係のエラーが発生しました
        throw CreateException ("Failed to read or create the configuration file directory. Please check the permissions of the parent. ("+(std::string)e.path1 ()+")");
    }
}
