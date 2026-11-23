// Experiment 13: RTOS Task Creation, Task States and Priority Assignment (FreeRTOS on ESP32)
// Board: ESP32 | Serial Monitor: 115200 baud
// NOTE: The PDF gives only the expected output for this experiment (no code listing),
// so this sketch is written to match that output format and the parameter table.
#include <Arduino.h>

// Task priorities (higher number = higher priority)
#define HIGH_PRIORITY    3
#define MEDIUM_PRIORITY  2
#define LOW_PRIORITY     1
// (Assessment step 4: change these to 1, 2, 3 respectively and compare the output)

// Task delays in ms
#define HIGH_DELAY_MS    500
#define MEDIUM_DELAY_MS  1000
#define LOW_DELAY_MS     1500

void HighTask(void *pvParameters)
{
  unsigned long count = 0;
  while (1)
  {
    count++;
    Serial.printf("HIGH   | Priority: %d | Count: %lu | RUNNING -> BLOCKED (%d ms)\n",
                  HIGH_PRIORITY, count, HIGH_DELAY_MS);
    vTaskDelay(pdMS_TO_TICKS(HIGH_DELAY_MS));   // BLOCKED -> READY -> RUNNING
  }
}

void MediumTask(void *pvParameters)
{
  unsigned long count = 0;
  while (1)
  {
    count++;
    Serial.printf("MEDIUM | Priority: %d | Count: %lu | RUNNING -> BLOCKED (%d ms)\n",
                  MEDIUM_PRIORITY, count, MEDIUM_DELAY_MS);
    vTaskDelay(pdMS_TO_TICKS(MEDIUM_DELAY_MS));
  }
}

void LowTask(void *pvParameters)
{
  unsigned long count = 0;
  while (1)
  {
    count++;
    Serial.printf("LOW    | Priority: %d | Count: %lu | RUNNING -> BLOCKED (%d ms)\n",
                  LOW_PRIORITY, count, LOW_DELAY_MS);
    vTaskDelay(pdMS_TO_TICKS(LOW_DELAY_MS));
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("FreeRTOS TASK PRIORITY EXPERIMENT");
  Serial.println("========================================");

  xTaskCreate(HighTask,   "HighTask",   2048, NULL, HIGH_PRIORITY,   NULL);
  xTaskCreate(MediumTask, "MediumTask", 2048, NULL, MEDIUM_PRIORITY, NULL);
  xTaskCreate(LowTask,    "LowTask",    2048, NULL, LOW_PRIORITY,    NULL);

  Serial.println("Three tasks created successfully.");
  Serial.println("Priority: HIGH=3, MEDIUM=2, LOW=1");
  Serial.println("State: RUNNING -> BLOCKED -> READY -> RUNNING");
  Serial.println("========================================");
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
