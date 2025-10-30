#include <CAN.h>

#define CAN_STBY  13
#define CAN_RX    14
#define CAN_TX    15

void setup() {
  Serial.begin(9600);
  while (!Serial);

  digitalWrite(CAN_STBY, LOW);
  CAN.setPins(CAN_RX, CAN_TX);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  int packetSize = CAN.parsePacket();

  uint8_t data[6];
  uint8_t i = 0;

  int16_t x_raw;
  int16_t y_raw;
  int16_t z_raw;

  uint16_t spd_raw;

  uint16_t u_raw;
  uint16_t i_raw;
  uint16_t e_raw;

  float accel_x;
  float accel_y;
  float accel_z;

  float spd;

  float voltage;
  float current;
  float energy;

  if (packetSize) {
    switch (CAN.packetId()) {
      case 0xED:
        Serial.println("Received speed package: ");

        while(CAN.available()){
          data[i] = CAN.read();
          i++;
        }

        spd_raw = (data[0] << 8) | data[1];

        spd = spd_raw / 100.0;

        Serial.print("V:");
        Serial.print(spd);
        Serial.println("km/h");
        break;

      case 0xC3:
        Serial.println("Received acceleration package: ");

        while(CAN.available()){
          data[i] = CAN.read();
          i++;
        }

        x_raw = (data[0] << 8) | data[1];
        y_raw = (data[2] << 8) | data[3];
        z_raw = (data[4] << 8) | data[5];

        accel_x = x_raw / 100.0;
        accel_y = y_raw / 100.0;
        accel_z = z_raw / 100.0;

        Serial.print("X: ");
        Serial.print(accel_x);
        Serial.print(" g  Y:");
        Serial.print(accel_y);
        Serial.print(" g  Z:");
        Serial.print(accel_z);
        Serial.println(" g");
        break;

      case 0x12:
        Serial.println("Received power supply package: ");

        while(CAN.available()){
          data[i] = CAN.read();
          i++;
        }

        u_raw = (data[0] << 8) | data[1];
        i_raw = (data[2] << 8) | data[3];
        e_raw = (data[4] << 8) | data[5];

        voltage = u_raw / 100.0;
        current = i_raw / 100.0;
        energy = e_raw / 1000.0;

        Serial.print("U: ");
        Serial.print(voltage);
        Serial.print(" V  I:");
        Serial.print(current);
        Serial.print(" A  E:");
        Serial.print(energy);
        Serial.println(" Wh");
        break;
    }
  }
}

