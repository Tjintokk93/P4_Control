/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PID {
public:

   /**
   * TODO: Create the PID class
   **/

    double my_p_error{0.0};
    double my_i_error{0.0};
    double my_d_error{0.0};

    double my_kp;
    double my_ki;
    double my_kd;

    double my_output_lim_max;
    double my_output_lim_min;

    double delta_t{0.0};


    PID();
    virtual ~PID();

    void Init(double Kp, double Ki, double Kd, double output_lim_max, double output_lim_min);

    void UpdateError(double cte);

    double CalculateControl();
  
    double UpdateDeltaTime(double new_delta_time);
};

#endif //PID_CONTROLLER_H


