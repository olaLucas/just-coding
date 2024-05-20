from urllib.request import urlopen
from urllib.parse import urljoin
from html.parser import HTMLParser

class collector(HTMLParser):
    def __init__(self, url):
        HTMLParser.__init__(self)
        self.url = url
        self.links = []
        self.content = ''

    def getsource(self):
        if self.url != '':
            html = urlopen(self.url)
            self.content = html.read().decode()
        else:
            print('url is empty')

    def seturl(self, url):
        if url != '':
            self.getsource(url)
            self.url = url
        else:
            print('url is empty')

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
                    url = attr[1]
                    if url[:4] == 'http':
                        self.links.append(url)
                    else:
                        self.links.append(urljoin(self.url, url))
        
    def parse(self):
        if self.content != '':
            self.feed(self.content)
        else:
            if self.url != '':
                self.getsource()
                self.feed(self.content)
            else:
                print('url is empty')

def analyse(url):
    print(f'visitando: {url}')
    col = collector(url)
    col.parse()
    return col.getlinks()


def crawler(url, vitados):
    links = analyse(url)
    for link in links:
        try:
            if link not in visitados:
                visitados.add(link)
                crawler(link, visitados)
            else:
                pass
        except:
            pass

url = "https://reed.cs.depaul.edu/lperkovic/one.html" 
visitados = set()
crawler(url, visitados)
