__global__ static void order_array_cuda_kernel(unsigned int *data, unsigned int length)
{
    /* compute thread number */
    unsigned int x, y, idx;

    x = (unsigned int)threadIdx.x + (unsigned int)blockDim.x * (unsigned int)blockIdx.x;
    y = (unsigned int)threadIdx.y + (unsigned int)blockDim.y * (unsigned int)blockIdx.y;
    idx = (unsigned int)blockDim.x * (unsigned int)gridDim.x * y + x;

    if (idx >= N_ARRAYS)
        return; // safety precaution

    /* adjust pointer to the array to be ordered */
    data += idx;

    for (unsigned int i = 0; i < length; i++)
    {

        unsigned int offset = i % 2;
        unsigned int leftIndex = 2 * idx + offset;
        unsigned int rightIndex = leftIndex + 1;

        if (rightIndex < length)
        {
            if (shouldSwap(data[leftIndex], data[rightIndex]))
            {
                swap(&data[leftIndex], &data[rightIndex]);
            }
        }
        __syncthreads();
    }
}

__host__ __device__ static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
__host__ __device__ bool ShouldSwap<int>::operator()(const int left, const int right) const
{
    return left > right;
}

//---------------------------------------------

// CUDA kernel - even comparisons
__global__ void even_swapper(int *data, int length)
{
    unsigned int x, y, idx;
    x = (unsigned int)threadIdx.x + (unsigned int)blockDim.x * (unsigned int)blockIdx.x;
    y = (unsigned int)threadIdx.y + (unsigned int)blockDim.y * (unsigned int)blockIdx.y;
    idx = (unsigned int)blockDim.x * (unsigned int)gridDim.x * y + x;

    if (idx >= N_ARRAYS)
        return; // safety precaution

    /* adjust pointer to the array to be ordered */
    data += idx;

    if (idx % 2 == 0 && idx < length - 1)
    {
        if (data[idx + 1] < data[idx])
        {
            // switch in the data array
            int temp = data[idx];
            data[idx] = data[idx + 1];
            data[idx + 1] = temp;
        }
    }
}

// CUDA kernel - odd comparisons
__global__ void odd_swapper(int *data, int length)
{
    unsigned int x, y, idx;
    x = (unsigned int)threadIdx.x + (unsigned int)blockDim.x * (unsigned int)blockIdx.x;
    y = (unsigned int)threadIdx.y + (unsigned int)blockDim.y * (unsigned int)blockIdx.y;
    idx = (unsigned int)blockDim.x * (unsigned int)gridDim.x * y + x;

    if (idx >= N_ARRAYS)
        return; // safety precaution

    /* adjust pointer to the array to be ordered */
    data += idx;

    if (idx % 2 != 0 && idx < length - 2)
    {
        if (data[idx + 1] < data[idx])
        {
            // switch in the data array
            int temp = data[idx];
            data[idx] = data[idx + 1];
            data[idx + 1] = temp;
        }
    }
}