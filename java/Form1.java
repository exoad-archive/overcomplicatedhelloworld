package magic;
import org.lwjgl.opencl.Util;
import org.lwjgl.opencl.CLMem;
import org.lwjgl.opencl.CLCommandQueue;
import org.lwjgl.BufferUtils;
import org.lwjgl.PointerBuffer;
import org.lwjgl.opencl.CLProgram;
import org.lwjgl.opencl.CLKernel;

import java.nio.IntBuffer;
//Source: https://codegolf.stackexchange.com/a/26610

import java.util.List;

import org.lwjgl.opencl.CL;
import org.lwjgl.opencl.CLContext;
import org.lwjgl.opencl.CLDevice;
import org.lwjgl.opencl.CLPlatform;

import static org.lwjgl.opencl.CL10.*;

public class OpenCLHello {
static String letters = "HeloWrd ";

// The OpenCL kernel
static final String source =
    ""
    + "kernel void decode(global const int *a, global int *answer) { "
    + "  unsigned int xid = get_global_id(0);"
    + "  answer[xid] = a[xid] -1;" 
    + "}";

// Data buffers to store the input and result data in
static final IntBuffer a = toIntBuffer(new int[]{1, 2, 3, 3, 4, 8, 5, 4, 6, 3, 7});
static final IntBuffer answer = BufferUtils.createIntBuffer(11);

public static void main(String[] args) throws Exception {
    // Initialize OpenCL and create a context and command queue
    CL.create();
    CLPlatform platform = CLPlatform.getPlatforms().get(0);
    List<CLDevice> devices = platform.getDevices(CL_DEVICE_TYPE_GPU);
    CLContext context = CLContext.create(platform, devices, null, null, null);
    CLCommandQueue queue = clCreateCommandQueue(context, devices.get(0), CL_QUEUE_PROFILING_ENABLE, null);

    // Allocate memory for our input buffer and our result buffer
    CLMem aMem = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, a, null);
    clEnqueueWriteBuffer(queue, aMem, 1, 0, a, null, null);

    CLMem answerMem = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, answer, null);
    clFinish(queue);

    // Create our program and kernel
    CLProgram program = clCreateProgramWithSource(context, source, null);
    Util.checkCLError(clBuildProgram(program, devices.get(0), "", null));
    // sum has to match a kernel method name in the OpenCL source
    CLKernel kernel = clCreateKernel(program, "decode", null);

    // Execution our kernel
    PointerBuffer kernel1DGlobalWorkSize = BufferUtils.createPointerBuffer(1);
    kernel1DGlobalWorkSize.put(0, 11);
    kernel.setArg(0, aMem);
    kernel.setArg(1, answerMem);
    clEnqueueNDRangeKernel(queue, kernel, 1, null, kernel1DGlobalWorkSize, null, null, null);

    // Read the results memory back into our result buffer
    clEnqueueReadBuffer(queue, answerMem, 1, 0, answer, null, null);
    clFinish(queue);
    // Print the result memory

    print(answer);

    // Clean up OpenCL resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(aMem);
    clReleaseMemObject(answerMem);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    CL.destroy();
}





/** Utility method to convert int array to int buffer
 * @param ints - the float array to convert
 * @return a int buffer containing the input float array
 */
static IntBuffer toIntBuffer(int[] ints) {
    IntBuffer buf = BufferUtils.createIntBuffer(ints.length).put(ints);
    buf.rewind();
    return buf;
}


/** Utility method to print an int buffer as a string in our optimized encoding
 * @param answer2 - the int buffer to print to System.out
 */
static void print(IntBuffer answer2) {
    for (int i = 0; i < answer2.capacity(); i++) {
        System.out.print(letters.charAt(answer2.get(i) ));
    }
    System.out.println("");
}

}
