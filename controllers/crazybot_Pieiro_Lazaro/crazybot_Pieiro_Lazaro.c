/*
 * File:          crazybot_Pieiro_Lazaro.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <stdio.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define PI 3.1416

double b=0;
double b1=0;

//double pos_final;
//double ObsSen_Pos;

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);
 
  
  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
   WbDeviceTag ps_left = wb_robot_get_device("position_left");
   WbDeviceTag ps_right = wb_robot_get_device("position_left");
   
   wb_position_sensor_enable(ps_left, TIME_STEP);
   wb_position_sensor_enable(ps_right, TIME_STEP);
   
   ///////////distance sensor/////////7
   WbDeviceTag ds_r = wb_robot_get_device("distance_sensor");
   
   wb_distance_sensor_enable(ds_r, TIME_STEP);
  
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {
  
  double pos_final, pos_final1;
  double a, a1;
  double left_RPM, right_RPM;
  
  ////rueda izquierda//////////////
  a = wb_position_sensor_get_value(ps_left);
          pos_final = ((a - b)*-1)/0.064;
          left_RPM= (pos_final*60)/(2*PI);
          b = a;
          
  //////rueda derecha////////////
  a1 = wb_position_sensor_get_value(ps_right);
          pos_final1 = ((a1 - b1)*-1)/0.064;
          right_RPM= (pos_final1*60)/(2*PI);
          b1 = a1;
          
  /////////velocidad lineal del robot///////
  float rad=0.075; //radio de la llanta
  double vel, vel1;//velocidad lineal por llanta
  double vel_rob; //velocidad lineal del robot
  
  vel=pos_final*rad;
  vel1=pos_final1*rad;
  vel_rob=(vel+vel1)/2;
   
  int key=wb_keyboard_get_key();
    
    if (key==WB_KEYBOARD_UP){
    //double speed = -1;
    wb_motor_set_position(wheel_right, INFINITY);
    wb_motor_set_velocity(wheel_right, -40);
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, -40);
    }
    
    if(key==WB_KEYBOARD_DOWN){
    //double speed = -1;
    wb_motor_set_position(wheel_right, INFINITY);
    wb_motor_set_velocity(wheel_right, 1.33);
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, 1.33);
    }
    
    else if(key==WB_KEYBOARD_LEFT){
    wb_motor_set_position(wheel_right, INFINITY);
    wb_motor_set_velocity(wheel_right, -15);
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, 0);
    }
   
    if(key==WB_KEYBOARD_RIGHT){
    wb_motor_set_position(wheel_right, INFINITY);
    wb_motor_set_velocity(wheel_right, 0);
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, -15);
    }
    
    if(key==WB_KEYBOARD_END){
    wb_motor_set_position(wheel_right, INFINITY);
    wb_motor_set_velocity(wheel_right, 0);
    wb_motor_set_position(wheel_left, INFINITY);
    wb_motor_set_velocity(wheel_left, 0);
    }
    
     //printf("Left velocity: %f RPM\n",pos_final);
     printf("LW_RPM= %f RPM\tRW_RPM= %f RPM\t\tlinear velocity= %f\n",left_RPM,right_RPM,vel_rob);
     //printf("RW_RPM %f RPM\n",right_RPM);
     fflush(stdout);
    

    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
