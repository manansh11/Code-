import bs4
import requests
from bs4 import BeautifulSoup

x = 1
while x == 1:
	ticker = input("Enter a Stock Ticker Symbol: ")
	link = f'https://finance.yahoo.com/quote/{ticker}?p={ticker}&.tsrc=fin-srch'

	def parcePrice():
		r = requests.get(link)
		soup = bs4.BeautifulSoup(r.text, 'html.parser')
		price = soup.find_all('div', {'class':'My(6px) Pos(r) smartphone_Mt(6px)'})[0].find('span').text
		return price

	pricePerShare = parcePrice()
	print(f'The current price of {ticker} is ${pricePerShare}')
	numOfShares = input('How many shares would you like to buy?')
	if numOfShares != 0:
		totalCost = int(numOfShares) * float(pricePerShare)
		print(f'Total cost will be ${totalCost}')


