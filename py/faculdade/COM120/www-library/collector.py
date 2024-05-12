from urllib.request import urlopen
from urllib.parse import urljoin
from html.parser import HTMLParser

class collector(HTMLParser):
    def __init__(self, url):
        HTMLParser.__init__(self)

        self.url = url 
        self.content = ''
        self.links = []

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for attr in attrs:
                if attr[0] == 'href':
                    if attr[1].find('http') >= 0:
                        self.links.append(attr[1])
                    else:
                        self.links.append(urljoin(self.url, attr[1]))

    def getsource(self):
        if self.url != '':
            html = urlopen(self.url)
            self.content = html.read().decode()
        else:
            print('url is empty')

    def parse(self):
        if self.content != '':
            self.feed(self.content)
        else:
            if self.url != '':
                self.getsource()
                self.feed(self.content)
            else:
                print('url is empty')

    def getlinks(self):
        return self.links

    def geturl(self):
        return self.url

    def getcontent(self):
        return self.content

col = collector('https://www.w3.org')
col.parse()

for i in col.getlinks():
    print(i)
