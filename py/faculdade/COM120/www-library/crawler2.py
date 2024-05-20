from urllib.request import urlopen
from urllib.parse import urljoin
from html.parser import HTMLParser

class crawler(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.links = []
        self.content = ''
        self.url = ''
        self.visitados = set()

    def seturl(self, url):
        if url != '': 
            self.url = url
        self.setcontent()

    def setcontent(self):
        html = urlopen(self.url)
        self.content = html.read().decode()
    
    def geturl(self):
        return self.url

    def getcontent(self):
        return self.content

    def getlinks(self):
        return self.links

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for attr in attrs:
                if attr[0] == 'href':
                    link = attr[1]
                    if link[:4] == 'http':
                        self.links.append(link)
                    else:
                        self.links.append(urljoin(self.url, link))
    def analyse(self):
        if self.content != '':
            self.feed(self.content)
        else:
            self.setcontent()
            self.feed(self.content)

        return self.getlinks()

    def craw(self, url = False):
        if url != False:
            self.seturl(url)
            links = self.analyse()
        
    
        for link in self.links:
            if link not in self.visitados:
                try:
                    print(f'visitando: {link}')
                    self.visitados.add(link)
                    self.craw()
                except:
                    pass

c = crawler()
c.craw('https://www.w3.org/')
