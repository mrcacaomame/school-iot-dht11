#pragma once

// library
#include <wiringPi.h>

#include <string>

#include "raspberry_pi_exception.h"

#define DHT11_WAITRES_LOW 84
#define DHT11_DATAWAIT_LOW 50
#define DHT11_BITONE 68
#define DHT11_END 56

class RaspberryPi{
    private:
        // DHT11の最大読み取りタイミング
        static const uint8_t DHT11_MAX_TIMINGS;
        // DHT11の最大読み取りサイズ
        static const uint8_t DHT11_MAX_DATA; 

    public:
        struct DHT11_DATA{
            // 温度
            float tem;
            // 湿度
            float hum;
        };

    private: // Space to hold variables for use in classes.
        // DHT11のPIN情報を取得する関数
        uint8_t dht11_pin_;

    public:  // Space for operator.
        // RaspberryPi &operator= (const RaspberryPi &op) noexcept;
        // RAspberryPi &operator+ (const RAspberryPi &op);
        // RAspberryPi &operator- (const RAspberryPi &op);
        // RAspberryPi &operator* (const RAspberryPi &op);
        // RAspberryPi &operator/ (const RAspberryPi &op);
    
    
    public:  // Space for constructors and destructors.
        RaspberryPi (void) noexcept;
        ~RaspberryPi (void) noexcept;
    
    public:
        // GPIOの処理を開始させる
        void run (void) const;

        // GPIOの処理を終了させる
        void close (void) const;

    public:
        // DHT11のPINの情報を取得する関数
        // 1: const RPiGPIOPin -> ピンの値
        void setDHT11Pin (const uint8_t pin) noexcept;

    public:  // Space for public function.
        // DHT11から温度と湿度を取得する (2秒の間取得する時間が必要である)
        // 1: DHT11_DATA& -> 温度と湿度の情報を保持する変数
        bool getDHT11 (DHT11_DATA &data) const noexcept;

    private: // Space for private function.

};
