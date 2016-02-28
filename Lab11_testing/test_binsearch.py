from pytest import raises
from amath import myaverage, mymedian

"""
1. We should test with wierd data, ie a wierd array: does it have NANs, is it numeric? Does it have 0 elelemts? 1 element? 2?...ie test the boundaries
2. Then think of how the needle relates to the above. Try needles less than or greter than the range in the sorted array,
besides needles inbetween (in both cases the needle not being in the array). Try needles at the extremes of the array.
3. test the integration of 1 and 2 to make sure something has not gone wrong there.

Note: you can always compare your answers with linear search implemented in python.
"""

def test_mymath_mean():
    assert myaverage([9,3]) == 6

def test_char():
    with raises(TypeError):
        myaverage(['a',3])

def test_mymath():
    assert mymedian([9,3, 6]) == 6

def test_zero_median():
    with raises(ValueError):
        mymedian([])

def test_char_median():
    with raises(TypeError):
        mymedian(['a', 3])