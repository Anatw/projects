import pytest


def pytest_addoption(parser):
    parser.addoption("--nlines", action="store", type=int)


@pytest.fixture(scope='session')
def nlines(request):
    num_lines = request.config.getoption("--nlines")
    if num_lines is None:
        pytest.skip()
    return num_lines
