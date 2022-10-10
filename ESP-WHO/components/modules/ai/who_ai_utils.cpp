#include "who_ai_utils.hpp"

#include "esp_log.h"
#include "esp_camera.h"

#include "dl_image.hpp"

static const char *TAG = "ai_utils";

// +-------+--------------------+----------+
// |       |       RGB565       |  RGB888  |
// +=======+====================+==========+
// |  Red  | 0b0000000011111000 | 0x0000FF |
// +-------+--------------------+----------+
// | Green | 0b1110000000000111 | 0x00FF00 |
// +-------+--------------------+----------+
// |  Blue | 0b0001111100000000 | 0xFF0000 |
// +-------+--------------------+----------+

//sdkconfigs.h
#define CONFIG_SERVO_C_MIN_PULSEWIDTH 500
#define CONFIG_SERVO_C_MAX_PULSEWIDTH 3000
#define CONFIG_SERVO_C_MAX_DEGREE 180

#define CONFIG_SERVO_D_MIN_PULSEWIDTH 500
#define CONFIG_SERVO_D_MAX_PULSEWIDTH 3000
#define CONFIG_SERVO_D_MAX_DEGREE 180
//end sdkconfigs.h


//servo.c

//servo.h
#ifndef SERVO_H
#define SERVO_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "esp_attr.h"

// #include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"

//pin_defs.h
#define CHECK(x)                \
    do                          \
    {                           \
        esp_err_t __;           \
        if ((__ = x) != ESP_OK) \
            return __;          \
    } while (0)
#define CHECK_LOGE(err, x, tag, msg, ...)      \
    do                                         \
    {                                          \
        if ((err = x) != ESP_OK)               \
        {                                      \
            ESP_LOGE(tag, msg, ##__VA_ARGS__); \
            return err;                        \
        }                                      \
    } while (0)

/////////// servos //////////
#define SERVO_C 15
#define SERVO_D 14
/////////////////////////////
//end pin_defs.h 

typedef struct
{
    int servo_pin;
    int min_pulse_width;
    int max_pulse_width;
    int max_degree;
    int angle;
    mcpwm_unit_t mcpwm_num;
    mcpwm_timer_t timer_num;
    mcpwm_generator_t gen;
} servo_config;

/** @struct servo_config
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
 */

/**
 * @brief Enables Servo port on the sra board, sets up PWM for the three pins in servo port.
 *
 * @return esp_err_t - returns ESP_OK if servo pins initialised, else it returns ESP_ERR_INVALID_ARG
 **/
esp_err_t enable_servo();

/**
 * @brief Set the angle of the servos attached to the servo port of SRA Board
 *
 * @param config pointer to the servo_config struct
 * @param degree_of_rotation angle to which the servo must be set, depends on value of MAX_DEGREE macro
 * @return esp_err_t
 */
esp_err_t set_angle_servo(servo_config *config, unsigned int degree_of_rotation);

/**
 * @brief Get the angle of the servos
 * @return esp_err_t
 */
int read_servo(servo_config *config);

#endif
//end servo.h

//servo.c
static const char *TAG_SERVO = "servo";
static int enabled_servo_flag = 0;
#define STR(A) #A

esp_err_t enable_servo()
{
    esp_err_t err;
    // CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_A), TAG_SERVO, "error: servo A: %s", esp_err_to_name(err));
    // CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, SERVO_B), TAG_SERVO, "error: servo B: %s", esp_err_to_name(err));
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, SERVO_C), TAG_SERVO, "error: servo C: %s", esp_err_to_name(err));
    CHECK_LOGE(err, mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, SERVO_D), TAG_SERVO, "error: servo D: %s", esp_err_to_name(err));

    mcpwm_config_t pwm_config;
    // sets the pwm frequency = 50
    pwm_config.frequency = 50;
    // sets the initial duty cycle of PWMxA = 0
    pwm_config.cmpr_a = 0;
    // sets the initial duty cycle of PWMxB = 0
    pwm_config.cmpr_b = 0;
    // sets the pwm counter mode
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    // sets the pwm duty mode
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

    // init pwm 0a, 1a, 2a with the above settings

    esp_err_t err_A = mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    esp_err_t err_B = mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);

    if (err_A == ESP_OK && err_B == ESP_OK)
    {
        enabled_servo_flag = 1;
        ESP_LOGI(TAG_SERVO, "enabled servos");

        return ESP_OK;
    }
    else
    {
        enabled_servo_flag = 0;
        return ESP_FAIL;
    }
}

static esp_err_t set_angle_servo_helper(int servo_pin, int servo_max, int servo_min_pulsewidth, int servo_max_pulsewidth, unsigned int degree_of_rotation, mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, mcpwm_generator_t gen)
{
    degree_of_rotation = degree_of_rotation > servo_max ? servo_max : degree_of_rotation;

    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (servo_min_pulsewidth + ((servo_max_pulsewidth - servo_min_pulsewidth) * (degree_of_rotation)) / (servo_max));

    esp_err_t err = mcpwm_set_duty_in_us(mcpwm_num, timer_num, gen, cal_pulsewidth);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG_SERVO, "set servo at pin %d: %ud", servo_pin, degree_of_rotation);
    }
    else
    {
        ESP_LOGE(TAG_SERVO, "error: servo at pin %d: %s", servo_pin, esp_err_to_name(err));
    }

    return err;
}

esp_err_t set_angle_servo(servo_config *config, unsigned int degree_of_rotation)
{
    if (enabled_servo_flag)
    {
        if (config->servo_pin)
        {
            config->angle = degree_of_rotation;
            return set_angle_servo_helper(config->servo_pin, config->max_degree, config->min_pulse_width, config->max_pulse_width, degree_of_rotation, config->mcpwm_num, config->timer_num, config->gen);
        }
        else
        {
            ESP_LOGE(TAG_SERVO, "error: incorrect servo pin passed to function");
            return ESP_FAIL;
        }
    }
    else
    {
        ESP_LOGE(TAG_SERVO, "error: servos not enabled, call enable_servo() before using servos");
        return ESP_FAIL;
    }
}

int read_servo(servo_config *config)
{
    return config->angle;
}
//end servo.c


//servo A configs
// #define TAG "MCPWM_SERVO_CONTROL"

servo_config servo_c = {
	.servo_pin = SERVO_C,
	.min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_C_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_A,
};

servo_config servo_d = {
	.servo_pin = SERVO_D,
	.min_pulse_width = CONFIG_SERVO_D_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_D_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_D_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_B,
};


int x_coor = 0;
int y_coor = 0;
int x_angle = 0;
int y_angle = 0;
int curr_x_ang = 85;
int curr_y_ang = 50;

static void mcpwm_servo_control(void *args)
{ 
	enable_servo();

    printf("X_coor: %d\tY_coor: %d\n",x_coor,y_coor);

// 320 width in standing pos

// A:14:Orange:Side
// B:15:Yellow:Bottom

// // Test servo
    // while(1)
    // {
    //     set_angle_servo(&servo_c, 85);
    //     set_angle_servo(&servo_d, 50);
    //     vTaskDelay(5);
    // }

                // SERVO A
    // for (int i = 0; i < 90  ; i++)
    // {
    //     set_angle_servo(&servo_c, i);
    //     set_angle_servo(&servo_d, i);
    //     vTaskDelay(1);  
    // }

    // for (int i = 90; i>0  ; i--)
    // {
    //     set_angle_servo(&servo_c, i);
    //     set_angle_servo(&servo_d, i);
    //     vTaskDelay(1);  
    // }
                
    // //             // SERVO B
    // for (int i = 0; i < 60  ; i++)
    // {
    //     set_angle_servo(&servo_d, i);
    //     vTaskDelay(5);  
    // }

    // for (int i = 60; i>0  ; i--)
    // {
    //     set_angle_servo(&servo_d, i);
    //     vTaskDelay(5);  
    // }                


//APPROACH 1

    // GPIO 15 working
    // 15:A:BOTTOM:Yellow
    // #define SERVO_A 15
    // #define SERVO_B 14

    // x_angle = (35*(160-x_coor))/320;
    // printf("X Angle: %d\n",x_angle);

    // if((160-x_coor)<-2)
    // {
    //     x_angle = x_angle*-1;
    //     for (int i = curr_x_ang; i < curr_x_ang + x_angle ; i++)
    //     {
    //         set_angle_servo(&servo_c, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_x_ang = curr_x_ang+ x_angle;
    //     printf("Current X angle: %d\n",curr_x_ang);
    // }

    // //angle is negative wrt midpt
    // else if((160-x_coor)>2)
    // {
    //     for (int i = curr_x_ang; i > curr_x_ang-x_angle ; i--)
    //     {
    //         set_angle_servo(&servo_c, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_x_ang = curr_x_ang - x_angle;
    //     printf("Current X angle: %d\n",curr_x_ang);
    // }

// APPROACH 2
    // x_angle = 1;
    // printf("Angle: %d",x_angle);

    // if((160-x_coor)<0)
    // {
    //     for (int i = curr_x_ang; i < curr_x_ang + x_angle ; i++)
    //     {
    //         set_angle_servo(&servo_a, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_x_ang = curr_x_ang+ x_angle;
    //     printf("Current angle: %d",curr_x_ang);
    // }

    // //angle is negative wrt midpt
    // else
    // {
    //     for (int i = curr_x_ang; i > curr_x_ang-x_angle ; i--)
    //     {
    //         set_angle_servo(&servo_a, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_x_ang = curr_x_ang - x_angle;
    //     printf("Current angle: %d",curr_x_ang);
    // }




//                          SERVO B

    y_angle = (35*(120-y_coor))/240;
    printf("Y Angle: %d\t",y_angle);

    if((120-y_coor)>0)
    {
        for (int i = curr_y_ang; i < curr_y_ang + y_angle ; i++)
        {
            set_angle_servo(&servo_d, i);
            vTaskDelay(1);  
        }
        curr_y_ang = curr_y_ang+ y_angle;
        printf("Current Y angle: %d\n",curr_y_ang);
    }

    //angle is negative wrt midpt
    else if((120-y_coor)<0)
    {
        y_angle = y_angle*-1;
        for (int i = curr_y_ang; i >= curr_y_ang - y_angle ; i--)
        {
            set_angle_servo(&servo_d, i);
            vTaskDelay(1);  
        }
        curr_y_ang = curr_y_ang - y_angle;
        printf("Current Y angle: %d\n",curr_y_ang);
    }  

// APPROACH 2

    // GPIO 14 working
    // 14:A:SIDE:Orange
    // #define SERVO_A 14
    // #define SERVO_B 15

    // y_angle = 1;
    // printf("Y Angle: %d\n",y_angle);

    // if((120-y_coor)>0)
    // {
    //     for (int i = curr_y_ang; i <= curr_y_ang + y_angle ; i++)
    //     {
    //         set_angle_servo(&servo_d, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_y_ang = curr_y_ang+ y_angle;
    //     printf("Current Y angle: %d\n",curr_y_ang);
    // }

    // //angle is negative wrt midpt
    // else
    // {
    //     for (int i = curr_y_ang; i >= curr_y_ang-y_angle ; i--)
    //     {
    //         set_angle_servo(&servo_d, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_y_ang = curr_y_ang - y_angle;
    //     printf("Current Y angle: %d\n",curr_y_ang);
    // } 
}

void print_detection_result(std::list<dl::detect::result_t> &results)
{
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {
        ESP_LOGI("detection_result", "[%2d]: (%3d, %3d, %3d, %3d)", i, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);

        if (prediction->keypoint.size() == 10)
        {
            ESP_LOGI("detection_result", "      left eye: (%3d, %3d), right eye: (%3d, %3d), nose: (%3d, %3d), mouth left: (%3d, %3d), mouth right: (%3d, %3d)",
                     prediction->keypoint[0], prediction->keypoint[1],  // left eye
                     prediction->keypoint[6], prediction->keypoint[7],  // right eye
                     prediction->keypoint[4], prediction->keypoint[5],  // nose
                     prediction->keypoint[2], prediction->keypoint[3],  // mouth left corner
                     prediction->keypoint[8], prediction->keypoint[9]); // mouth right corner

            x_coor = prediction->keypoint[4];
            y_coor = prediction->keypoint[5];

            // printf("Testing servo motors\n");
            mcpwm_servo_control(NULL);
            // xTaskCreatePinnedToCore(&mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL, 1);    
        }
    }
}

void *app_camera_decode(camera_fb_t *fb)
{
    if (fb->format == PIXFORMAT_RGB565)
    {
        return (void *)fb->buf;
    }
    else
    {
        uint8_t *image_ptr = (uint8_t *)malloc(fb->height * fb->width * 3 * sizeof(uint8_t));
        if (image_ptr)
        {
            if (fmt2rgb888(fb->buf, fb->len, fb->format, image_ptr))
            {
                return (void *)image_ptr;
            }   
            else
            {
                ESP_LOGE(TAG, "fmt2rgb888 failed");
                dl::tool::free_aligned(image_ptr);
            }
        }
        else
        {
            ESP_LOGE(TAG, "malloc memory for image rgb888 failed");
        }
    }
    return NULL;
}