__kernel void saxpy(float a, __global float *x, __global float *y)
{
   uint id = get_global_id(0);
   y[id] = a * x[id] + y[id];
}
