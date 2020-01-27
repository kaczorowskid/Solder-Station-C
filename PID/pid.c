#include <avr/io.h>

#include "pid.h"

uint16_t pid(uint16_t setpoint, uint16_t temperature, pid_t *pid_s)
{
	int32_t result;

	pid_s->errors[pid_s->index & MASK] = setpoint - temperature;

	pid_s->derivative = pid_s->errors[pid_s->index & MASK] - pid_s->errors[(pid_s->index-1) & MASK];

	if (pid_s->errors[pid_s->index & MASK] > pid_s->KT || pid_s->errors[pid_s->index & MASK] < -pid_s->KT)
	{
		result = (pid_s->KP*pid_s->errors[pid_s->index & MASK] + pid_s->KD*pid_s->derivative);
	}
	else
	{
		pid_s->integral += pid_s->errors[pid_s->index & MASK];

		result = (pid_s->KP*pid_s->errors[pid_s->index & MASK] + (pid_s->KI*pid_s->integral)/100 + pid_s->KD*pid_s->derivative);
	}

	pid_s->index++;

	if (result > PID_TOP)
	{
		return (int16_t)PID_TOP;
	}
	else if (result < PID_BOTTOM)
	{
		return (int16_t)PID_BOTTOM;
	}
	else
	{
		return (int16_t)result;
	}


}

