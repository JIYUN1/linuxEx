#include <wiringPi.h>

int main (void)
{
	//wiringPi를 쓰려면 wiringPiSetup()을 먼저선언 해야한다.
	wiringPiSetup () ;
	pinMode (0, OUTPUT) ;
	
	for (;;)
	{
		digitalWrite (0, HIGH) ; delay (500) ;
		digitalWrite (0,  LOW) ; delay (500) ;
	}
	
	return 0 ;

