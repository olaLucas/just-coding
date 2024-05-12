from urllib.request import urlopen

def getHTML(URL = ""):
    response = urlopen(URL)
    html = response.read()
    return html.decode()


# type: <class 'http.client.HTTPResponse'>
response = urlopen("http://w3.org/Consortium/facts.html")

# pega a URL requisitada
print(response.geturl())

# para pegar todos os headers, use:

for headers in response.getheaders():
    print(f'header: {headers}, variable type: {type(headers)}')

# para extrair o html:
html = response.read()
print(f'html type: {type(html)}')

html = html.decode()
print("HTML: ", html)


