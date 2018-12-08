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

enum Conddition { fog = 0, rain = 1, snow = 2, sunny = 3 };

class Weather {
private:
	double temperature;
	int light, humidity;											//intensity of light coming from LDR
	Conddition cond;
public:
	double getTemp() { return temperature; }

	int getHumd() { return humidity; }

	int getLight() { return light; }

	void setTemp(double temperature) { this->temperature = temperature; }

	void setHumd(int humidity) { this->humidity = humidity; }

	void setLight(int light) { this->light = light; }

	void currentWeather(double temperature, double humidity, int light) {
		if (humidity > 60 && temperature < 75 && light > 7) {
			this->cond = Conddition::fog;
		}
		else if (temperature < 60 && temperature > 32 && humidity > 50) {
			this->cond = Conddition::rain;
		}
		else if (temperature < 32 && humidity > 30) {
			this->cond = Conddition::snow;
		}
		else {
			this->cond = Conddition::sunny;
		}
	}

		Conddition getCond() { return this->cond; }
};

	int main() {
		double t = 30.0;
		int l = 0, h = 30;
		Weather weather;
		int speed;

		for (int i = 0; i < 100; i++) {
			if (i % 2 == 0) {
				t += 5.0;
				h += 5;
			}
			if (i % 4 == 0) {
				l++;
			}

			weather.currentWeather(t, h, l);

			if (weather.getCond() == Conddition::fog) {
				speed = 50;
			}
			else if (weather.getCond() == Conddition::rain) {
				speed = 55;
			}
			else if (weather.getCond() == Conddition::snow) {
				speed = 40;
			}
			else {
				speed = 65;
			}

			std::cout << "Temperature: " << weather.getTemp() << " Humdity: " << weather.getHumd() << " Light Intensity : " << weather.getLight() << " Speed: " << speed << "\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		return 0;
	}
