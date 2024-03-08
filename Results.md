## Results
### Carla simulator after implementation of PID class
![CarlaSimulator](project/pid_controller/screenshot/xxx)


## Questions:
### 1. Add the plots to your report and explain them (describe what you see)
### Tested configurations
|  TEST  | KP_STEER | KI_STEER | KD_STEER | KP_THROTTLE | KI_THROTTLE | KD_THROTTLE |
|:------:|:--------:|:--------:|:--------:|:-----------:|:-----------:|:-----------:|
|Reference|  0.10   |   0.00   |   0.00   |     0.10    |    0.00     |     0.00    |
| Test 1 |   0.25   |   0.001  |   0.25   |     0.2     |    0.001    |     0.10    |
| Test 2 |   0.40   |   0.01   |   0.25   |     0.2     |    0.01     |     0.15    |
| Test 3 |   0.40   |   0.01   |   0.25   |     0.2     |    0.15     |     0.15    |
| Test 4 |   0.25   |   0.02   |   0.40   |     0.2     |    0.01     |     0.3     |
| Test 5 |   0.40   |   0.02   |   0.40   |     0.2     |    0.01     |     0.3     |
| Test 6 |   0.50   |   0.02   |   0.25   |     0.2     |    0.01     |     0.15    |
| Test 7 |   0.60   |   0.02   |   0.25   |     0.2     |    0.01     |     0.15    |
| Test 9 |   0.25   |   0.02   |   0.40   |     0.2     |    0.01     |     0.3     |
| Test 10|   0.40   |   0.02   |   0.40   |     0.2     |    0.01     |     0.3     |
| Test 11|   0.50   |   0.02   |   0.25   |     0.2     |    0.01     |     0.15    |
| Test 12|   0.60   |   0.02   |   0.25   |     0.2     |    0.01     |     0.15    |


### Plots
|TEST|STEER|THROTTLE|
|:--:|:---:|:------:|
Reference|![reference1](project/pid_controller/screenshot/)| ![reference2](project/pid_controller/screenshot/)
Test 1|![test1_pic1](project/pid_controller/screenshot/) | ![test1_pic2](project/pid_controller/screenshot/)
Test 2|![test2_pic1](project/pid_controller/screenshot/) | ![test2_pic2](project/pid_controller/screenshot/)
Test 3|![test3_pic1](project/pid_controller/screenshot/) | ![test3_pic2](project/pid_controller/screenshot/)
Test 4|![test4_pic1](project/pid_controller/screenshot/) | ![test4_pic2](project/pid_controller/screenshot/)
Test 5|![test5_pic1](project/pid_controller/screenshot/) | ![test5_pic2](project/pid_controller/screenshot/)
Test 6|![test6_pic1](project/pid_controller/screenshot/) | ![test6_pic2](project/pid_controller/screenshot/)
Test 7|![test7_pic1](project/pid_controller/screenshot/) | ![test7_pic2](project/pid_controller/screenshot/)

### Observations/Approach
I applied the approach described here: [PID Regler einstellen in der Praxis](https://tlk-energy.de/blog/pid-regler-einstellen)
First, the proportional part has to be adjusted by setting the integral and derivative values to 0. Then the proportional has to be increased until the controller starts to become unstable and oscillate. The proportional has to be set below the oscillation starts, thus a small overshoot is allowed.
Secondly, the integral value gets found by constantly increasing the gain. The goal of tuning the integral value is to achieve an adequate controller response or reaction time. If the controller starts to oscillate or becomes unstable, the value gets adjusted in the opposite direction.
For a lot of applications a well calibrated PI controller satisfies a good controlling. The derivative value should only be used, if the application befenfits from the dampening effects of the derivative. As before, increase the derivative until the overshoot has been dampened to an acceptable level. 

The approach is difficult to apply, because the setpoint in the Carla simulator constantly changes for every timestep. Therefore, the oszillating point is difficult to find.
Also, the controller impacts the path planning of the next step, which in turn affects the steering and throttle error and thus the controller's input. For this reason, it is difficult to predict behavioral changes for a definite change in the controller's parametrization.


### 2. What is the effect of the PID according to the plots, how each part of the PID affects the control command?
- Proportional term `P`: a value that is proportional to the current error. A large `P` value will result in a large change in the control output. 
- Integreal term `I`: a value that is proportional to the cumulative error over time. A large `I` value speeds up the elimination of the residual steady state error produced by the system bias.
- Derivative term `D`: a value that is proportional to the rate of change of error over time. The `D` term predicts system behavior and thus improves the settling time of the controller.
The different effects can seen in the shown plots.

### 3. How would you design a way to automatically tune the PID parameters?
If we have identical setpoint behaviour for every "controller-run", the "twiddle algorithm" or "coordinate ascent" algorithm can be used, as shown in Sebastian's lesson.


### 4. PID controller is a model free controller, i.e. it does not use a model of the car. Could you explain the pros and cons of this type of controller?
From the expriments, we can see PID has two main advantages
- PID can be used and has decent performance when there is no model available
- Easy to implement and compute, making it suitable to run basic platforms
However, PID might have poor performance since it only uses single reference point

Pros:
* PID controller is easy to understand, easy to implement (no knowledge of the system needed);
* PID controller is widely-used in industry, widely-studied in academia;
* PID controller is easy to maintain (i.e., modify the parameters).

Cons:
* PID controller does not take into account the system / process (i.e., environment / vehicle dynamics);
* PID controller parameter tuning is less of a science than an art (i.e., discovering optimal values is more or less done through [trial-and-error](https://en.wikipedia.org/wiki/Trial_and_error));
* PID controller cannot easily handle complex scenarios (e.g., sharp right-turns);
* PID controllers are limited in their ability to handle high-dimensional nonlinear equations of motion that are characteristic of self-driving vehicles.


### 5. What would you do to improve the PID controller?
- Using coordinate ascent to improve the controller calibration automatically
