#include "Arduino.h"
#include "WiFiUdp.h"
#include "Metric.h"

char *_host;
int _port;

Metric::Metric(char host[], int port)
{
	_host = host;
	_port = port;
}

bool Metric::send(char metric[], int value)
{
	WiFiUDP Udp;
	char valueString[12];
	itoa(value, valueString,10);

	char cmd[] = "g";

	char buffer[strlen(metric) + strlen(valueString) + strlen(cmd) + 2 + 1];
	strcpy(buffer, metric);
	strcat(buffer, ":");
	strcat(buffer, valueString);
	strcat(buffer, "|");
	strcat(buffer, cmd);
	const uint8_t* msg = (uint8_t*)buffer;

	Udp.beginPacket(_host, _port);
	Udp.write(msg, strlen(buffer));
	Udp.endPacket();
}