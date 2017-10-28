#ifndef Metric_h 
#define Metric_h

#include "Arduino.h"
#include "WiFiUdp.h"

class Metric
{
	public:
    	Metric(char host[], int port);
    	bool send(char metric[], int value);
    private:
    	char *_host;
    	int _port;
};

#endif