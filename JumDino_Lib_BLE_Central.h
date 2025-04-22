#ifndef __POKEROBO_LAB_BLE_CENTRAL_H__
#define __POKEROBO_LAB_BLE_CENTRAL_H__

#include <ArduinoBLE.h>
#include "JumDino_Lib_BLE_Logger.h"

#define BLE_CENTRAL_BEGIN_FAILED        0x1001
#define BLE_CENTRAL_DEVICE_SCANNING     0x1002
#define BLE_CENTRAL_DEVICE_FOUND        0x1003
#define BLE_CENTRAL_CONNECTED           0x1004
#define BLE_CENTRAL_DISCONNECTED        0x1005
#define BLE_CENTRAL_CONNECTING_FAILED   0x1006
#define BLE_CENTRAL_RECEIVING_BEGIN     0x1007
#define BLE_CENTRAL_RECEIVING_DATA_READ 0x1008
#define BLE_CENTRAL_RECEIVING_END       0x1009

class PokeroboBLEReceiver {
  public:
    virtual void onReceive(int32_t value) {}
};

class PokeroboBLECentral {
  public:
    PokeroboBLECentral(String charactId, PokeroboBLEReceiver *receiver = NULL, PokeroboBLELogger *logger = NULL);
    void begin(String localName);
    void check(PokeroboBLEReceiver *receiver = NULL);
  protected:
    virtual void receive(BLECharacteristic &charact);
  private:
    String _charactId;
    String _localName;
    PokeroboBLEReceiver *_receiver = NULL;
    PokeroboBLELogger *_logger = NULL;
};

class PokeroboBLECentralDebugLogger: public PokeroboBLELogger {
  public:
    void log(uint16_t type, BLEDevice *device = NULL, int32_t value = 0) {
      switch (type) {
        case BLE_CENTRAL_BEGIN_FAILED:
          Serial.println("BLE khởi động thất bại!");
          break;
        case BLE_CENTRAL_DEVICE_SCANNING:
          Serial.println("Đang quét thiết bị BLE...");
          break;
        case BLE_CENTRAL_DEVICE_FOUND:
          Serial.print("Tìm thấy thiết bị: ");
          Serial.println(device->localName());
          break;
        case BLE_CENTRAL_CONNECTED:
          Serial.println("Đã kết nối!");
          break;
        case BLE_CENTRAL_DISCONNECTED:
          Serial.println("Ngắt kết nối!");
          break;
        case BLE_CENTRAL_CONNECTING_FAILED:
          Serial.println("Kết nối thất bại!");
          break;
        case BLE_CENTRAL_RECEIVING_BEGIN:
          Serial.println("Nhận dữ liệu...");
          break;
        case BLE_CENTRAL_RECEIVING_DATA_READ:
          Serial.print("Nhận giá trị: ");
          Serial.println(value);
          break;
        case BLE_CENTRAL_RECEIVING_END:
          Serial.println("Nhận dữ liệu kết thúc");
          break;
        default:
          Serial.println("Log chưa phân loại");
      }
    }
};

#endif
