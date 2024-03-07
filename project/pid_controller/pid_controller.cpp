/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, double output_lim_max, double output_lim_min) {
   my_kp = Kp;
   my_ki = Ki;
   my_kd = Kd;

   my_output_lim_min = output_lim_min;
   my_output_lim_max = output_lim_max;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   if (delta_t > 0.0) {
      my_d_error = (cte - my_p_error) / delta_t;
   }
   else {
      my_d_error = 0.0;
   }   
   my_p_error = cte;
   my_i_error = my_i_error + cte * delta_t;
}

double PID::CalculateControl() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control;

   control = my_kp*my_p_error + my_kd*my_d_error + my_ki*my_i_error; 

   if (control < my_output_lim_min) {
      control = my_output_lim_min;
   }
   else if (control > my_output_lim_max) {
      control = my_output_lim_max;
   }
   
   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   
   delta_t = new_delta_time;
   return delta_t;
}