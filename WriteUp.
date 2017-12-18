### Compiling

The code can be compiled by using `cmake` and `make`.

---
### Implementation

The algorithm is the same as thaught in the lessons, and the twiddle is used to optimize the values.

---
### Reflection

The proportional term steers the car proportional to the error, the derivative term steers it according to the change of the crosstrack error and integral term reacts to the overall crostrack error. The effect is as expected, by controlling only the steering, the steering is relatively hard in the curves but easy in the straight parts. I first trained my PID controller manually and found the values P = 0.05, D = 0.5 and I = 0.005 functional. Then I started twiddling from these values to find more optimal ones.

---
### Simulation

With the trained values no tyre leaves the drivable portion of the road.
