#include "check_options/check_options.h"
#include "raspberry_pi/raspberry_pi.h"
#include "create/create.h"
#include "database/database.h"

#include "print/print.h"

int main (int argc, char *argv[]){
    bool flag;
    CheckOptions opt;
    RaspberryPi r_pi;
    RaspberryPi::DHT11_DATA dht11_data;
    Config conf;
    Database db;
    uint32_t milisec;
    uint8_t dht11_pin;
    
    // オプションを設定する
    flag = opt.setOptions (argc, argv);
    if (!flag){
        // Version系の描画オプションなどを行う
        flag = opt.getVersionFlag ();
        if (flag){
            print::version ();
        }
        // Help系の描画オプションなどを行う
        flag = opt.getHelpFlag ();
        if (flag){
            print::help ();
        }

        return 0;
    }

    if (!opt.getCreateConfigFilePath ().empty ()){
        // 作成する設定ファイルが存在する
        for (const auto &v1 : opt.getCreateConfigFilePath ()){
            try{
                // 設定ファイルを作成する
                create::config (v1);

                printf ("Created config file (%s)\n", v1.c_str ());

            }catch (const CreateException &e){
                printf ("%s\n", e.what ());
            }
        }

        return 0;
    }
    do{
        std::string str;
        try{
            conf.get (CONF_INTERVAL_MINUTES, str);
            milisec = std::stoi (str);

        }catch (const std::invalid_argument &e){
            milisec = 2000;
        }

        try{
            conf.get (CONF_DHT11_PIN, str);
            dht11_pin = std::stoi (str);

        }catch (const std::invalid_argument &e){
            milisec = 27;
        }

    }while (false);

    printf ("Read config file ...\n");

    flag = conf.read (opt.getConfigFilePath ());
    if (!flag){
        // 設定ファイルが存在しませんでした
        printf ("Configuration file paths may be different. (%s)\n", opt.getConfigFilePath ().c_str ());
        return 1;
    }

    try{
        db.setConfig (conf);
        printf ("Set config ...\n");

        // PIN16に設定をする
        r_pi.run ();
        r_pi.setDHT11Pin (dht11_pin);
        
        while (true){
            flag = r_pi.getDHT11 (dht11_data);
            if (flag){
                // 気温情報などを表示させる
                // printf ("tem = %f : hum = %f\n", dht11_data.tem, dht11_data.hum);
                delay (milisec);
                db.insertData (dht11_data);
            }else{
                // 気温の情報などを入手することができませんでした
                // printf ("No get ...\n");
                // printf ("tem = %f : hum = %f\n", dht11_data.tem, dht11_data.hum);
                // delay (1000);
            }
        }
    }catch (const RaspberryPiException &e){
        fprintf (stderr, "%s\n", e.what ());
    }catch (const DatabaseException &e){
        fprintf (stderr, "%s\n", e.what ());
    }
    
    return 0;
}
