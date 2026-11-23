// Experiment 14 - Program A: Binary Semaphore Event Signaling (ESP32, 115200 baud)
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t binarySemaphore;

void BinaryProducerTask(void *pvParameters) {
  int eventNumber = 0;
  while (1) {
    eventNumber++;
    Serial.printf("[BINARY] Producer generated event %d\n", eventNumber);
    if (xSemaphoreGive(binarySemaphore) == pdTRUE)
      Serial.println("[BINARY] Event signal sent");
    else
      Serial.println("[BINARY] Signal not added; semaphore already full");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void BinaryConsumerTask(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(binarySemaphore, portMAX_DELAY) == pdTRUE)
      Serial.println("[BINARY] Consumer received signal");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("BINARY SEMAPHORE EVENT SIGNALING");

  binarySemaphore = xSemaphoreCreateBinary();
  if (binarySemaphore == NULL) {
    Serial.println("ERROR: Binary semaphore creation failed");
    while (1) vTaskDelay(pdMS_TO_TICKS(1000));
  }

  xTaskCreate(BinaryProducerTask, "BinProd", 4096, NULL, 2, NULL);
  xTaskCreate(BinaryConsumerTask, "BinCons", 4096, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
// Experiment 14 - Program B: Counting Semaphore (max count 3, initial 0) (ESP32, 115200 baud)
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t countingSemaphore;

void CountingProducerTask(void *pvParameters) {
  int eventNumber = 0;
  while (1) {
    eventNumber++;
    if (xSemaphoreGive(countingSemaphore) == pdTRUE)
      Serial.printf("[COUNTING] Event %d generated; count = %lu\n",
                    eventNumber,
                    (unsigned long)uxSemaphoreGetCount(countingSemaphore));
    else
      Serial.println("[COUNTING] Semaphore full; signal not added");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void CountingConsumerTask(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(countingSemaphore, portMAX_DELAY) == pdTRUE) {
      Serial.printf("[COUNTING] Signal consumed; remaining = %lu\n",
                    (unsigned long)uxSemaphoreGetCount(countingSemaphore));
      vTaskDelay(pdMS_TO_TICKS(2500));   // slow consumer -> count accumulates
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("COUNTING SEMAPHORE");

  countingSemaphore = xSemaphoreCreateCounting(3, 0);
  if (countingSemaphore == NULL) {
    Serial.println("ERROR: Counting semaphore creation failed");
    while (1) vTaskDelay(pdMS_TO_TICKS(1000));
  }

  xTaskCreate(CountingProducerTask, "CntProd", 4096, NULL, 2, NULL);
  xTaskCreate(CountingConsumerTask, "CntCons", 4096, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
