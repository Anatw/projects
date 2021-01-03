from selenium import webdriver
from pytest_postgresql import factories
import pytest
import psycopg2

Chrome_path = "/home/anat/anat-wax/Django/selenium/chromedriver_linux64/chromedriver"
server_add = "http://127.0.0.1:8000/"
postgresql_my_proc = factories.postgresql_proc(port=5432, unixsocketdir='/var/run/postgresql')
postgresql_my = factories.postgresql('postgresql_my_proc')



@pytest.fixture()
def test_setup():
    '''Setup a nre test environment fo the Employee microservice'''
    global driver
    driver = webdriver.Chrome(executable_path=Chrome_path)
    driver.get(server_add)
    yield
    driver.close()


def test_insert_new_employee(test_setup):
    driver.find_element_by_id("id_fullname").send_keys("selenium")
    driver.find_element_by_id("id_country").send_keys("Test")
    driver.find_element_by_id("id_city").send_keys("LLL")
    driver.find_element_by_id("id_salary").send_keys("12345678")
    driver.find_element_by_xpath('//button[text()="Submit"]').click()

def test_check_new_insertion_to_database(postgresql):
    conn = psycopg2.connect(host="localhost", port=5432, database="Employees", user="anat", password="anat")
    cur = conn.cursor()
    cur.execute("""SELECT * FROM employee_register_employee""")



# def test_edit_existing_employee(test_setup):
