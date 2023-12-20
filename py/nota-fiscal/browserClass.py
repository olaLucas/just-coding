from selenium import webdriver
from selenium.webdriver.common.by import By
from time import sleep

class browser:
    def __init__(self) -> None:
        self.driver = webdriver.Firefox()
        self.url = 'https://nfe.etransparencia.com.br/sp.caieiras/nfe/principal.aspx'
        self.cpf = '152.158.868.65'
        self.senha = 'rony123'
        self.captchaString = None

        self.loginButtonXPATH = '/html/body/form/div[2]/div[2]/table/tbody/tr[2]/td/table[2]/tbody/tr/td/div/div/table/tbody/tr[3]/td/table/tbody/tr/td[1]/table/tbody/tr[1]/td/div/div/ul/li[2]/a'
        self.IDCPFInput = 'W0045vUSUARIO' 
        self.IDSenhaInput = 'W0045vSENHA'
        self.IDCaptchaInput = 'W0045vCAPTCHAUSUARIO'
        self.IDCaptchaButton = 'W0045BTNENTER'
        pass
        

    def findElement(self, ByString, By=By.ID, time=0):
        """
        Função responsável por localizar um webelement \n
        Bystring = sting de localização (ID, XPATH, etc...) \n
        By = método de localização (default: By.ID) \n 
        time = tempo de delay (default: 0) \n
        """

        sleep(time)
        return self.driver.find_element(By, ByString)
    
    
    def sendKeys(self, ByString, text, By=By.ID, time=0):
        """
        Função responsável por localizar e enviar uma string para um elemento \n
        ByString = sting de localização (ID, XPATH, etc...). \n
        By = método de localização. (default: By.ID) \n
        text = texto a ser inserido. \n
        time = tempo de delay. (default: 0)\n
        """  

        self.findElement(ByString, By, time).send_keys(text)

    def click(self, ByString, By=By.ID,time=0):
        """
        Função responsável por localizar e clicar em um elemento \n
        ByString = sting de localização. (ID, XPATH, etc...) \n
        By = método de localização. (default: By.ID) \n
        time = tempo de delay. (default: 0) \n
        """

        self.findElement(ByString, By, time).click()
        