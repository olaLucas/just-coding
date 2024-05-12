from html.parser import HTMLParser
from urllib.request import urlopen

def getSource(URL):
    content = urlopen(URL)
    return content.read().decode()


class html_parser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            for attr in attrs:
                if attr[0] == 'href':
                    print(attr[1])
