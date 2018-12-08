#include<iostream>
#include<string>
#include<thread>
#include<chrono>

//Raspberry Pi Libraries
/*#include <wiringPi.h>
#include <sys/time.h>
#include <pcf8591.h>
#include <softPwm.h>
#include <time.h>
#include <lcd.h>
#include <pcf8574.h>*/

using namespace std;

class Weather{
	private:
		double temperature;
		int light, humidity;											//intensity of light coming from LDR
		enum cond {fog = 0, rain = 1, snow = 2, sunny = 3};
	
	public:
		double getTemp(){ return temp;}
		
		int getHumd(){ return humidity;}
		
		int getLight(){ return light;}
		
		void setTemp(double temperature){ this->temperature = temperature;}
		
		void setHumd(double humidity){ this->humidity = humidity;}
		
		void setLight(int light){ this->light = light;}
		
		void currentWeather(double temperature, double humidity, int light){
			if(humidity > 60 temperature < 75 && light > 7){
				this->cond = cond::fog;
			}else if(temperature < 60 && temperature > 32 && humidity > 50){
				this->cond = cond::rain;
			}else if(temperature < 32 && humidity > 30){
				this->cond = cond::snow;
			}else{
				this->cond = cond::sunny;
		}
		
		void getCond(){ return this->cond;}
};

int main(){
	double t = 30.0;
	int l = 0 , h = 30;
	Weather weather;
	int speed;
	
	for(int i = 0; i < 100; i++){
		if(i % 2 == 0){
			t += 5.0;
			h += 5.0;
		}
		if(i %4 4 == 0){
			l++;
		}
		
		weather.currentWeather(t, h, l);
		
		if(weather.getCond() == 0){
			speed = 50;
		}else if(weather.getCond() == 1){
			speed = 55;
		}else if(weather.getCond() == 2){
			speed = 40;
		}else{
			speed = 65;
		}
		
		std::cout << "Temperature: " << weather.getTemp() << " Humdity: " << weather.getHumd() << " Light Intensity : " << weather.getLight() << " Speed: " << speed << "\n";
		
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
	return 0;
}