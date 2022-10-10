#include "who_ai_utils.hpp"

#include "esp_log.h"
#include "esp_camera.h"

#include "dl_image.hpp"

// #include "sra_board.h"
#include "sra_board.h"

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
#define CONFIG_SERVO_C_MIN_PULSEWIDTH 500
#define CONFIG_SERVO_C_MAX_PULSEWIDTH 3000
#define CONFIG_SERVO_C_MAX_DEGREE 180

#define CONFIG_SERVO_D_MIN_PULSEWIDTH 500
#define CONFIG_SERVO_D_MAX_PULSEWIDTH 3000
#define CONFIG_SERVO_D_MAX_DEGREE 180

int x_coor = 0;
int y_coor = 0;
int x_angle = 0;
int y_angle = 0;
int curr_x_ang = 85;
int curr_y_ang = 50;

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

static void mcpwm_servo_control(void *args)
{ 
	enable_servo();

    printf("X_coor: %d\tY_coor: %d\n",x_coor,y_coor);


// 320 width in standing pos


// // Test servo
    // while(1)
    // {
    //     set_angle_servo(&servo_a, 30);
    //     set_angle_servo(&servo_b, 0);
    //     vTaskDelay(5);
    // }

                // SERVO A
    // for (int i = 0; i < 30  ; i++)
    // {
    //     set_angle_servo(&servo_c, i);
    //     vTaskDelay(1);  
    // }

    // for (int i = 30; i>0  ; i--)
    // {
    //     set_angle_servo(&servo_c, i);
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

    x_angle = (35*(160-x_coor))/320;
    printf("X Angle: %d\n",x_angle);

    if((160-x_coor)<-2)
    {
        x_angle = x_angle*-1;
        for (int i = curr_x_ang; i < curr_x_ang + x_angle ; i++)
        {
            set_angle_servo(&servo_c, i);
            vTaskDelay(1);  
        }
        curr_x_ang = curr_x_ang+ x_angle;
        printf("Current X angle: %d\n",curr_x_ang);
    }

    //angle is negative wrt midpt
    else if((160-x_coor)>2)
    {
        for (int i = curr_x_ang; i > curr_x_ang-x_angle ; i--)
        {
            set_angle_servo(&servo_c, i);
            vTaskDelay(1);  
        }
        curr_x_ang = curr_x_ang - x_angle;
        printf("Current X angle: %d\n",curr_x_ang);
    }

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

    // y_angle = (35*(120-y_coor))/240;
    // printf("Y Angle: %d\t",y_angle);

    // if((120-y_coor)<-2)
    // {
    //     y_angle = y_angle*-1;
    //     for (int i = curr_y_ang; i < curr_y_ang + y_angle ; i++)
    //     {
    //         set_angle_servo(&servo_b, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_y_ang = curr_y_ang+ y_angle;
    //     printf("Current Y angle: %d\n",curr_y_ang);
    // }

    // //angle is negative wrt midpt
    // else if((120-y_coor)>2)
    // {
    //     for (int i = curr_y_ang; i > curr_y_ang - y_angle ; i--)
    //     {
    //         set_angle_servo(&servo_b, i);
    //         vTaskDelay(1);  
    //     }
    //     curr_y_ang = curr_y_ang - y_angle;
    //     printf("Current Y angle: %d\n",curr_y_ang);
    // }  

// APPROACH 2

    y_angle = 1;
    printf("Y Angle: %d\n",y_angle);

    if((120-y_coor)>0)
    {
        for (int i = curr_y_ang; i <= curr_y_ang + y_angle ; i++)
        {
            set_angle_servo(&servo_d, i);
            vTaskDelay(1);  
        }
        curr_y_ang = curr_y_ang+ y_angle;
        printf("Current Y angle: %d\n",curr_y_ang);
    }

    //angle is negative wrt midpt
    else
    {
        for (int i = curr_y_ang; i >= curr_y_ang-y_angle ; i--)
        {
            set_angle_servo(&servo_d, i);
            vTaskDelay(1);  
        }
        curr_y_ang = curr_y_ang - y_angle;
        printf("Current Y angle: %d\n",curr_y_ang);
    } 
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

            mcpwm_servo_control(NULL);
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