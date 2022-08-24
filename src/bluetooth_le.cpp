#include "bluetooth_le.h"

// void BLE::setup() {

//     Serial.println("Setup BLE Sever");
//     NimBLEDevice::init(BT_DEVICENAME);
//     NimBLEDevice::setPower(ESP_PWR_LVL_P9);
//     // NimBLEDevice::setMTU(256);
    
    
//     BLE::server_ptr = NimBLEDevice::createServer();
//     NimBLEService* service_ptr = server_ptr->createService(BLE_SERVICEUUID);
//     NimBLECharacteristic* characteristic_ptr = service_ptr->createCharacteristic(
//                                                             "Test", 
//                                                             NIMBLE_PROPERTY::WRITE |
//                                                             NIMBLE_PROPERTY::READ |
//                                                             NIMBLE_PROPERTY::NOTIFY);

//     // BLE::characteristic_ptr->setValue("Hello BLE");
//     characteristic_ptr->createDescriptor("2902");

//     // Start Servies after creating all Characteristics and Descriptors
//     service_ptr->start();

//     NimBLEAdvertising* advertising_ptr = NimBLEDevice::getAdvertising();
//     // Add services to advertisement data
//     advertising_ptr->addServiceUUID(BLE_SERVICEUUID);
//     advertising_ptr->setScanResponse(true);
//     advertising_ptr->start();
    
//     Serial.println("BLE Setup finished - advertising...");
// }   



void BLE::setup() {

  Serial.println("Startup BLE Server!");

  BLEDevice::init("LED-Lampe");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                        BLE_CHARACTERISTIC_UUID,
                                        NIMBLE_PROPERTY::READ |
                                        NIMBLE_PROPERTY::WRITE 
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMaxPreferred(0x12);

  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

NimBLEServer* BLE::server_ptr;