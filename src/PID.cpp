#include "PID.h"
#include <limits>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Kd = Kd;
	this->Ki = Ki;
	
	// Twiddling variables
	twiddle = false;
	step = 0;
	eval_steps = 50;
	p[0] = Kp;
	p[1] = Kd;
	p[2] = Ki;
	dp[0] = 0.05;
	dp[1] = 0.5;
	dp[2] = 0.0005;
	tol = 0.001;
	i = 0;
	best_err = std::numeric_limits<double>::max();
	try_first = true;
	second_run = false;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
	total_error += cte*cte;
	
	// For twiddling
	step++;
	if ( (step == eval_steps) && twiddle) {
		Twiddle();
	}
}

double PID::TotalError() {
	return total_error;
}

void PID::Twiddle(){
	// For debugging
	std::cout << "Total Error: " << TotalError() << std::endl;
	std::cout << "P: " << Kp << std::endl;
	std::cout << "D: " << Kd << std::endl;
	std::cout << "I: " << Ki << std::endl;
	std::cout << "index: " << i << std::endl;
	std::cout << "try_first: " << try_first << std::endl;
	total_error = 0;
	step = 0;
	
	if ( (dp[0] + dp[1] + dp[2]) > tol ){
    p[i] += dp[i];
    
    if (second_run) {
			if ( (TotalError() < best_err) && try_first){
				std::cout << "try first" << std::endl;
			  best_err = TotalError();
			  dp[i] *= 1.1;
			  if (i == 2)
					i = 0;
				else
					i += 1;
			}
			else if (try_first){
				std::cout << "try second" << std::endl;
				try_first = false;
			  p[i] -= 2*dp[i];
			}
			else if (TotalError() < best_err) {
				std::cout << "try third" << std::endl;
				try_first = true;
		    best_err = TotalError();
		    dp[i] *= 1.1;
		    if (i == 2)
					i = 0;
				else
					i += 1;
			}
			else {
				std::cout << "try fourth" << std::endl;
				try_first = true;
		    p[i] += dp[i];
		    dp[i] *= 0.9;
		    if (i == 2)
					i = 0;
				else
					i += 1;
			}
		}
	}
	else
		twiddle = false;
	
	second_run = true;
	Kp = p[0];
	Kd = p[1];
	Ki = p[2];
}

