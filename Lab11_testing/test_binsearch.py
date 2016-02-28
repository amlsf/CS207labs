from pytest import raises
from binsearch import binary_search
import numpy as np


input = list(range(10))


def test_1():
    assert binary_search(input, 5) == 5


def test_2():
    assert binary_search(input, 4.5) == -1


def test_3():
    assert binary_search([5], 5) == 0


def test_4():
    assert binary_search([5], 4) == -1


def test_5():
    binary_search([], 4) == -1


def test_6():
    binary_search(input, 11) == -1


def test_not_alist():
    with raises(TypeError):
        binary_search('a', 1)


def test_missing_args():
    with raises(TypeError):
        binary_search([1, 2])


def test_not_numeric():
    assert binary_search(['a', 'b'], 'b') == 1


def test_other():
    assert binary_search(['hello', 'there', 'you', 'abc'], 'abc') == -1


# TODO this is a problem
def test_nan():
    assert binary_search([np.nan, 0, 2, 3, 4], np.nan) == 2


def test_needle_1():
    assert binary_search(input, 5, 2, 2) == -1


def test_needle_2():
    assert binary_search(input, 2, 2, 2) == 2


def test_needle_3():
    assert binary_search(input, 2, 1,3) == 2


def test_needle_4():
    assert binary_search(input, 2, 3, 1) == -1


def test_needle_5():
    assert binary_search(input, 9) == 9


def test_both():
    assert binary_search([5], 7) == -1