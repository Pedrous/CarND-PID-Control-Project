#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error = 0;
  double i_error = 0;
  double d_error = 0;
  double total_error = 0;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  
  bool twiddle;
	int step;
	int eval_steps;
	double p[3];
	double dp[3];
	double tol;
	int i = 0;
	double best_err;
	bool try_first;
	bool second_run;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  void Twiddle();
};

#endif /* PID_H */
