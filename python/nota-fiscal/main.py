from browserClass import browser
from selenium.webdriver.common.by import By
from GUIClass import captchaGUI

navegador = browser()
    
def getCaptcha(): # função que cria a GUI do captcha e retorna o valor da entry
    GUICaptcha = captchaGUI()
    GUICaptcha.mainloop()

    if GUICaptcha.buttonVar == True:
        captcha = GUICaptcha.entryVar
        print("Captcha code:", captcha)
        return captcha

def login(): #Função responsável por acessar e efetuar o login no site
    navegador.driver.get(url=navegador.url)
    navegador.click(navegador.loginButtonXPATH, By=By.XPATH)
    navegador.sendKeys(navegador.IDCPFInput, navegador.cpf, time=3)
    navegador.sendKeys(navegador.IDSenhaInput, navegador.senha)

    navegador.captchaString = getCaptcha()

    navegador.sendKeys(navegador.IDCaptchaInput, navegador.captchaString)
    navegador.click(navegador.IDCaptchaButton)

