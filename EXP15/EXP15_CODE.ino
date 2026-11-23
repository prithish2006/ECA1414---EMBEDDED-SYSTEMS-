// Experiment 15 - Part A: Message Queue (producer-consumer) (ESP32, 115200 baud)
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t dataQueue;

// Producer task
void ProducerTask(void *pvParameters)
{
  uint32_t data = 100;
  while (1)
  {
    data += 10;
    if (xQueueSend(dataQueue, &data, pdMS_TO_TICKS(100)) == pdPASS)
    {
      Serial.printf("[PRODUCER] Data sent: %lu\n", (unsigned long)data);
    }
    else
    {
      Serial.println("[PRODUCER] Queue full; data not sent");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Consumer task
void ConsumerTask(void *pvParameters)
{
  uint32_t receivedData;
  while (1)
  {
    if (xQueueReceive(dataQueue, &receivedData, portMAX_DELAY) == pdPASS)
    {
      Serial.printf("[CONSUMER] Data received: %lu\n", (unsigned long)receivedData);
      Serial.println("---------------------------");
      // Simulate processing time
      vTaskDelay(pdMS_TO_TICKS(1500));
    }
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("PART A: FREERTOS MESSAGE QUEUE");

  // Create queue: 5 items, each 32 bits
  dataQueue = xQueueCreate(5, sizeof(uint32_t));
  if (dataQueue == NULL)
  {
    Serial.println("ERROR: Queue creation failed");
    while (1) { vTaskDelay(pdMS_TO_TICKS(1000)); }
  }
  Serial.println("Message queue created successfully");

  xTaskCreate(ProducerTask, "Producer", 4096, NULL, 2, NULL);
  xTaskCreate(ConsumerTask, "Consumer", 4096, NULL, 1, NULL);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
// Experiment 15 - Part B: Mailbox-style communication (queue of length 1) (ESP32, 115200 baud)
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t mailbox;

// Producer task
void ProducerTask(void *pvParameters)
{
  uint32_t message = 1000;
  while (1)
  {
    message += 100;
    if (xQueueSend(mailbox, &message, pdMS_TO_TICKS(500)) == pdPASS)
    {
      Serial.printf("[MAILBOX] Message sent: %lu\n", (unsigned long)message);
    }
    else
    {
      Serial.println("[MAILBOX] Slot occupied; message not sent");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Consumer task
void ConsumerTask(void *pvParameters)
{
  uint32_t receivedMessage;
  while (1)
  {
    if (xQueueReceive(mailbox, &receivedMessage, portMAX_DELAY) == pdPASS)
    {
      Serial.printf("[MAILBOX] Message received: %lu\n", (unsigned long)receivedMessage);
      Serial.println("---------------------------");
      // Simulate message processing
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("PART B: FREERTOS MAILBOX");

  // Mailbox-style queue: one item, uint32_t size
  mailbox = xQueueCreate(1, sizeof(uint32_t));
  if (mailbox == NULL)
  {
    Serial.println("ERROR: Mailbox creation failed");
    while (1) { vTaskDelay(pdMS_TO_TICKS(1000)); }
  }
  Serial.println("One-item mailbox created successfully");

  xTaskCreate(ProducerTask, "Producer", 4096, NULL, 2, NULL);
  xTaskCreate(ConsumerTask, "Consumer", 4096, NULL, 1, NULL);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
