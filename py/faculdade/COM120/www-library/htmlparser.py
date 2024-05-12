from urllib.request import urlopen
from html.parser import HTMLParser

class parser(HTMLParser):
    count = 0

    def spaces(self):
        string = " "
        for i in range(self.count):
            string = string + "  "
        return string

    def handle_starttag(self, tag, attrs):
        print(f'{self.spaces()}{tag} start')
        self.count = self.count + 1

    def handle_endtag(self, tag):
        self.count = self.count - 1
        print(f'{self.spaces()}{tag} end')
        

def getsource(URL):
    content = urlopen(URL)
    return content.read().decode()

par = parser()
par.feed(getsource("https://www.bbc.co.uk"))
