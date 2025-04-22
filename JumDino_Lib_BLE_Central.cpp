#include "JumDino_Lib_BLE_Central.h"

PokeroboBLECentral::PokeroboBLECentral(String charactId, PokeroboBLEReceiver *receiver,
      PokeroboBLELogger *logger) {
  _charactId = charactId;
  _receiver = receiver;
  _logger = (logger != NULL) ? logger : new PokeroboBLELogger();
}

void PokeroboBLECentral::begin(String localName) {
  uint8_t limit = 5;
  while (--limit >= 0) {
    if (BLE.begin()) {
      break;
    }
  }
  if (limit < 0) {
    _logger->log(BLE_CENTRAL_BEGIN_FAILED);
    return;
  }

  _localName = localName;

  BLE.scan();

  _logger->log(BLE_CENTRAL_DEVICE_SCANNING);
}

void PokeroboBLECentral::check(PokeroboBLEReceiver *receiver) {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    _logger->log(BLE_CENTRAL_DEVICE_FOUND, &peripheral);

    if (peripheral.localName() == this->_localName) {
      BLE.stopScan();

      if (peripheral.connect()) {
        _logger->log(BLE_CENTRAL_CONNECTED, &peripheral);

        if (peripheral.discoverAttributes()) {
          BLECharacteristic counterChar = peripheral.characteristic(this->_charactId.c_str());

          if (counterChar) {
            _logger->log(BLE_CENTRAL_RECEIVING_BEGIN, &peripheral);

            while (peripheral.connected()) {
              // if (counterChar.valueUpdated()) {
                this->receive(counterChar);
              // }
              if (_receiver != NULL) {
                int32_t value;
                counterChar.readValue(value);
                _logger->log(BLE_CENTRAL_RECEIVING_DATA_READ, &peripheral, value);
                _receiver->onReceive(value);
              }
            }

            _logger->log(BLE_CENTRAL_RECEIVING_END, &peripheral);
          }
        }

        _logger->log(BLE_CENTRAL_DISCONNECTED, &peripheral);
      } else {
        _logger->log(BLE_CENTRAL_CONNECTING_FAILED);
      }

      BLE.scan(); // Quét lại nếu ngắt kết nối
    }
  }
}

void PokeroboBLECentral::receive(BLECharacteristic &charact) {}
