#include "raspberry_pi.h"

RaspberryPi::RaspberryPi (void) noexcept{

}

RaspberryPi::~RaspberryPi (void) noexcept{

}

void RaspberryPi::run(void) const{
    bool flag;
    flag = wiringPiSetup ();
    if (flag == -1){
        // 初期化失敗
        throw RaspberryPiException ("An initialization error has occurred.");
    }
}

void RaspberryPi::close(void) const{
    // bool flag;
    // flag = bcm2835_close ();
    // if (!flag){
    //     // 終了処理失敗
    //     throw RaspberryPiException ("Termination process failed.");
    // }
}

void RaspberryPi::setDHT11Pin(const uint8_t pin) noexcept{
    this->dht11_pin_ = pin;
}

bool RaspberryPi::getDHT11(DHT11_DATA &data) const noexcept{
    // BUFFER TO RECEIVE
	uint8_t bits[5];
	uint8_t cnt = 7;
	uint8_t idx = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	pinMode(this->dht11_pin_, OUTPUT);
	digitalWrite(this->dht11_pin_, LOW);
	delay(18);
	digitalWrite(this->dht11_pin_, HIGH);
	delayMicroseconds(40);
	pinMode(this->dht11_pin_, INPUT);

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(digitalRead(this->dht11_pin_) == LOW)
		if (loopCnt-- == 0) return -2;

	loopCnt = 10000;
	while(digitalRead(this->dht11_pin_) == HIGH)
		if (loopCnt-- == 0) return -2;

	// READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(digitalRead(this->dht11_pin_) == LOW)
			if (loopCnt-- == 0) return -2;

		unsigned long t = micros();

		loopCnt = 10000;
		while(digitalRead(this->dht11_pin_) == HIGH)
			if (loopCnt-- == 0) return -2;

		if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;
	}

	// WRITE TO RIGHT VARS
    // as bits[1] and bits[3] are allways zero they are omitted in formulas.
	data.hum = bits[0]; 
	data.tem = bits[2]; 
    data.hum = bits[0] + bits[1] * 0.1;
    data.tem = bits[2] + bits[3] * 0.1;

	uint8_t sum = bits[0] + bits[2];  

	if (bits[4] != sum) return false;

	return true;
}
