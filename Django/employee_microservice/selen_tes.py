from selenium import webdriver

driver = webdriver.Chrome(executable_path="/home/anat/anat-wax/Django/selenium/chromedriver_linux64/chromedriver")
driver.get("http://google.com")
driver.close()