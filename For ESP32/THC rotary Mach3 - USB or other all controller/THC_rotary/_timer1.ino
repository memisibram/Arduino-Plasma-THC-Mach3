
void Setup_Timer1() {
  // Setting structure for the timer
  esp_timer_create_args_t timer_args = {
    .callback = &onTimerCallback,
    .name = "my_periodic_timer"
  };

  // Create the timer
  ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handle));

  // Start the timer. It will repeat every 10,000 microseconds (10ms)
  ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handle, 10000));
}

void onTimerCallback(void* arg) {
  Do = true;
}
