#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// WiFi credentials
const char* ssid = "RocketTracker";

// Global variables to store GPS data
float latitude = 0.0;
float longitude = 0.0;
byte satellites = 0;

// Create an instance of the GPS class
SFE_UBLOX_GNSS myGNSS;

// Create an instance of the web server
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>GPS Tracker</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
 body { font-family: Arial, sans-serif; text-align: center; }
 #lat, #lon, #sats { font-weight: bold; }
</style>
</head>
<body>
<h1>Model Rocket GPS Tracker</h1>
<p>Latitude: <span id="lat">0.0</span></p>
<p>Longitude: <span id="lon">0.0</span></p>
<p>Satellites: <span id="sats">0</span></p>
<a href="https://www.google.com/maps/search/?api=1&query=0,0" id="map-link" target="_blank">View on Google Maps</a>

<script>
 setInterval(function() {
   fetch('/data')
     .then(response => response.json())
     .then(data => {
       document.getElementById('lat').innerText = data.lat.toFixed(6);
       document.getElementById('lon').innerText = data.lng.toFixed(6);
       document.getElementById('sats').innerText = data.sats;
       document.getElementById('map-link').href = `https://www.google.com/maps/search/?api=1&query=${data.lat.toFixed(6)},${data.lng.toFixed(6)}`;
     });
 }, 1000);
</script>
</body>
</html>
)rawliteral";

void setup() {
Serial.begin(115200);
Wire.begin();

if (!myGNSS.begin()) {
 Serial.println("u-blox GNSS not detected at default I2C address. Please check wiring.");
 while (1);
}

myGNSS.setI2COutput(COM_TYPE_UBX); // Set the I2C port to output UBX only
myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); // Save the communications port settings to flash and BBR

// Set up Wi-Fi Access Point
WiFi.softAP(ssid);
Serial.print("AP IP address: ");
Serial.println(WiFi.softAPIP());

// Set up web server routes
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send_P(200, "text/html", index_html);
});

server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
 String json = "{\"lat\":" + String(latitude, 6) + ",\"lng\":" + String(longitude, 6) + ",\"sats\":" + String(satellites) + "}";
 request->send(200, "application/json", json);
});

server.begin();
}

void loop() {
// Query the GPS module for new data
if (myGNSS.getPVT()) {
 latitude = myGNSS.getLatitude() / 10000000.0;
 longitude = myGNSS.getLongitude() / 10000000.0;
 satellites = myGNSS.getSIV();
}
}