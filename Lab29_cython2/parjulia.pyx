# distutils: extra_compile_args = -fopenmp
# distutils: extra_link_args = -fopenmp
#your code here
# TODO

cimport cython
import numpy as np
cimport numpy as np
from cython.parallel cimport prange

cdef inline double norm2(double complex z) nogil:
    return z.real*z.real + z.imag*z.imag

cdef int escape(int maxiter, double complex z, double complex c) nogil:
    cdef int n=0
    while n < maxiter and norm2(z) < 4:
        z=z*z+c
        n+=1
    return n

@cython.boundscheck(False)
@cython.wraparound(False)
cpdef run_cython_amalgamated2(int gridsize, box, double complex c, int maxiter):
    # TODO
    #your code here

    cdef double xstep = (box.x2 - box.x1)/(gridsize - 1.0)
    cdef double ystep = (box.y2 - box.y1)/(gridsize - 1.0)
    cdef complex[:] zs = np.zeros(gridsize * gridsize, dtype=complex)
    cdef unsigned int[:] output = np.empty(len(zs), dtype=np.uint32)

    cdef double xstart = box.x1
    cdef double ystart = box.y1
        
    cdef int i, j
    cdef double x, y
    # use prange here
    for i in prange(gridsize, nogil=True,
                    schedule='static', chunksize=1):
        x = xstart + i*xstep
        for j in range(gridsize):
            
            y = ystart + i*ystep
            
            output[gridsize * i + j] = escape(maxiter, x + 1j*y, c)
            
            zs[gridsize * i + j] = x + 1j*y
            
    # This function should return a tuple of memoryviers zs, output.
    return zs, output