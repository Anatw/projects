from selenium import webdriver
from selenium.webdriver.common.keys import Keys

def test_setup():
    global driver
    driver = webdriver.Firefox(executable_path="/home/anat/anat-wax/Django/selenium/geckodriver-v0.28.0-linux64/geckodriver")
    driver.get("http://www.python.org")
    assert "Python" in driver.title


def test_search():
    elem = driver.find_element_by_name("q")
    elem.clear()
    elem.send_keys("pycon")
    elem.send_keys(Keys.RETURN)
    assert "No results found." not in driver.page_source


def test_teardown():
    driver.close()
