from urllib.request import urlopen
from parserClass import html_parser

def news(URL, words):
    response = urlopen(URL)
    html = response.read().decode()
    for i in range(len(words)):
        print(f'{words[i]} appears {html.count(words[i])}')

def getSource(URL):
    response = urlopen(URL)
    return response.read().decode()

URL = 'http://bbc.co.uk'

par = html_parser()
par.feed(getSource(URL))
