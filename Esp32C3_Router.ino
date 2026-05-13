#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define SCK_PIN   6
#define MISO_PIN  5
#define MOSI_PIN  7
#define CS_PIN    10

void setup() {
  Serial.begin(115200);
  delay(1000);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  Ethernet.init(CS_PIN);

  Serial.println("กำลังขอ IP จาก DHCP...");

  if (Ethernet.begin(mac, 10000, 4000) == 0) {
    Serial.println("DHCP ล้มเหลว");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("❌ ไม่พบ W5500 - เช็คสายต่อ SPI");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("❌ ไม่มีสาย LAN เสียบ");
    }
    while (true);
  }

  Serial.print("✅ IP Address : "); Serial.println(Ethernet.localIP());
  Serial.print("   Subnet    : "); Serial.println(Ethernet.subnetMask());
  Serial.print("   Gateway   : "); Serial.println(Ethernet.gatewayIP());
}

void loop() {
  Ethernet.maintain();
  delay(5000);
  Serial.print("IP: "); Serial.println(Ethernet.localIP());
}
