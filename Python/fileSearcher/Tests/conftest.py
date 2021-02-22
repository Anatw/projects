# import pytest
#
# def pytest_addoption(parser):
#     parser.addoption("--file_name", action="store")
#     parser.addoption("--string", action="store")
#
#
# def pytest_generate_tests(metafunc):
#     if "file_name" in metafunc.fixturenames:
#         metafunc.parametrize("file_name", metafunc.config.getoption(
#             "file_name"))
#     if "string" in metafunc.fixturenames:
#         metafunc.parametrize("string", metafunc.config.getoption(
#             "string"))
# #
# # @pytest.fixture
# # def file_name(request):
# #     return request.config.getoption("--file_name")
# #
# #
# # @pytest.fixture
# # def string(request):
# #     return request.config.getoption("--string")
#
#
# # def pytest_addoption(parser):
# #     parser.addoption("--file_name", action="store")
# #     parser.addoption("--string", action="store")
# #
# #
# # @pytest.fixture(scope='session')
# # def name(request):
# #     name_value = request.config.option.name
# #     if name_value is None:
# #         pytest.skip()
# #     return name_value
#
# # def pytest_generate_tests(metafunc):
# #     # This is called for every test. Only get/set command line arguments
# #     # if the argument is specified in the list of test "fixturenames".
# #     option_value = metafunc.config.option.file_name
# #     if 'file_name' in metafunc.fixturenames and option_value is not None:
# #         metafunc.parametrize("file_name", [option_value])
# #     option_value = metafunc.config.option.string
# #     if 'string' in metafunc.fixturenames and option_value is not None:
# #         metafunc.parametrize("string", [option_value])