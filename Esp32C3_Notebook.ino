#include <SPI.h>
#include <Ethernet_Generic.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 1, 100);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);

#define SCK_PIN   6
#define MISO_PIN  1
#define MOSI_PIN  0
#define CS_PIN    7

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  Ethernet.init(CS_PIN);
  delay(500);

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(1000);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("❌ ไม่พบ W5500"); while (true);
  }

  Serial.print("IP: ");     Serial.println(Ethernet.localIP());
  Serial.print("Subnet: "); Serial.println(Ethernet.subnetMask());
  Serial.print("Link: ");   Serial.println(Ethernet.linkStatus() == LinkON ? "ON ✅" : "OFF ❌");
}

void loop() {
  delay(5000);
  Serial.print("IP: "); Serial.println(Ethernet.localIP());
}
