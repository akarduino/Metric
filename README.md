# Metric

Библиотека Arduino для отправки данных statsd серверу через UDP

# Использование

```c++
#include <ESP8266WiFi.h>
#include <Metric.h>

// wifi cridentials variables
char ssid[] = "WIFISSID";
char password[] = "PASSWORD";

// wifi connection status variables
bool wifiConnected = false;
int wifiChecks = 0;
int wifiChecksBeforeReconnect = 5;

// statsd server variables
char statsdHost[] = "SERVER_IP";
int statsdPort = 8126;
Metric stat = Metric(statsdHost, statsdPort);

// metric variables
char metric[] = "some.metric";
long metricValue;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
}

void loop() {
  delay(1000);

  // collecting some value
  metricValue = micros();

  // non blocking wifi connection
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
    wifiChecks++;
    Serial.print(wifiChecks);
    Serial.println(" try to connect to wifi");

    // reset connection on max try
    if (wifiChecks == wifiChecksBeforeReconnect) {
      WiFi.disconnect();
      WiFi.begin(ssid, password);
    }
  } else {
    Serial.println("wifi connected");
    wifiChecks = 0;
    wifiConnected = true;
  }

  // send metric if connected
  if (wifiConnected) {
    stat.send(metric, metricValue);
    Serial.println("metric sent");
  }
}
```
