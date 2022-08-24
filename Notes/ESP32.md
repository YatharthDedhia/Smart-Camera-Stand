# References: [Espressif Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

># GPIO:
* General Purpose Input - Output
* Used to connect the board to different modules.
* Contains 38 I/O pins.
* [Refer to this link for further I/O info](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)

![ESP32 Pin layout](/Assets/esp32-pinout-chip-ESP-WROOM-32.jpg)

## Code:
*   **gpio_pad_select_gpio(gpio_pin_no)**
    * used to select gpio pin.
* **gpio_set_direction(gpio_pin_no, direction)**
    * used to select input/output
* **gpio_set_level(gpio_pin_no, value);**
    * used to set value of the gpio pin to either 0 or 1

---

># Servo:
* Contains 3 wires (ground, vcc, signal)
* GND_ESP connected to GND_servo
* vcc connected to VIN
* connect signal to pwm pin (13)

## Code:
Functions:
1. **esp_err_t enable_servo()**
    * Part of servo.h
    * Enables Servo port on the sra board, sets up PWM for the three pins in servo port.

     * **Returns:** esp_err_t - returns ESP_OK if servo pins initialised, else it returns ESP_ERR_INVALID_ARG
     * **syntax:** enable_servo()

2. **esp_err_t set_angle_servo(servo_config * config, unsigned int degree_of_rotation)**
    * **@brief** Set the angle of the servos attached to the servo port of SRA Board
    * **@param** config pointer to the servo_config struct
    * **@param** degree_of_rotation angle to which the servo must be set, depends on value of MAX_DEGREE macro
    * **@return** esp_err_t 
    * **syntax:** set_angle_servo(&servo_name, angle_in_degrees) 

3. **vTaskDelay(no_of_ms)**
    * adds a delay between commands in milliseconds.

4. **xTaskCreatePinnedToCore(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL, 1);**
![xTaskCreatePinnedToCore](/Assets/xtaskcreatepinnedtocore.png)

5. **typedef struct {\
    int servo_pin;\
    int min_pulse_width;\
    int max_pulse_width;\
    int max_degree;\
    mcpwm_unit_t mcpwm_num;\
    mcpwm_timer_t timer_num;\
    mcpwm_generator_t gen;  \  
} servo_config;**

 * @struct servo_config
 *  @brief This structure contains the configuration of servos
 *  @var servo_config::servo_pin
 *  Member 'servo_pin' contains the gpio pin number to which servo is connected
 *  @var servo_config::min_pulse_width
 *  Member 'min_pulse_width' contains the minimum pulse width of servo motor
 *  @var servo_config::max_pulse_width
 *  Member 'max_pulse_width' contains the maximum pulse width of servo motor
 *  @var servo_config::max_degree
 *  Member 'max_degree' contains the maximum degree servo motor can rotate
 *  @var servo_config::mcpwm_num
 *  Member 'mcpwm_num' contains MCPWM unit to use
 *  @var servo_config::timer_num
 *  Member 'timer_num' contains MCPWM timer to use
 *  @var servo_config::gen
 *  Member 'gen' contains MCPWM operator to use

6. **xTaskCreate():**
![xTaskCreate_1](/Assets/xtaskcreate_1.png)
![xTaskCreate_2](/Assets/xtaskcreate_2.png)


># Code:
* **printf**: Used to output to console/terminal when USB/computer is connected.
* **ESP_LOGI**: Used to output when USB/computer is not connected. It can output over wifi, bluetooth etc. 