from html.parser import HTMLParser
from urllib.request import urlopen
from urllib.parse import urljoin

class parser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for attr in attrs:
                if attr[0] == 'href':
                    if attr[1].find('http') >= 0:
                        print(attr[1])
                    else:
                        print(urljoin(self.url, attr[1]))    

    def parsehtml(self, url):
        self.url = url
        content = self.getsource(url)
        self.feed(content)

    def getsource(self, url):
        content = urlopen(url)
        return content.read().decode()

par = parser()
par.parsehtml('https://www.w3.org/mission/')
