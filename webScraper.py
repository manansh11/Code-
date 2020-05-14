import requests
from bs4 import BeautifulSoup
import pprint

response = requests.get('https://news.ycombinator.com/news') #Link of website
response2 = requests.get('https://news.ycombinator.com/news?p=2') # Link of page 2 of website

soup = BeautifulSoup(response.text, 'html.parser') #Parse through the raw HTML data into somthing readable
soup2 = BeautifulSoup(response2.text, 'html.parser') # ^^

links = soup.select('.storylink') # All the links of stories on page one
subtext = soup.select('.subtext') # The Class where the score is kept

links2 = soup2.select('.storylink') # All the links of stories on page two
subtext2 = soup2.select('.subtext') # The class where the score is kept on page two

mega_links = links + links2 # Combine the links from page one and page two
mega_subtext = subtext + subtext2 # Combine all the scores from page one and page two
print(links)
'''
Class: sort_stories_by_votes
Use: Sorts the list of dictionary items "hnlist" using lambda to order the votes/

'''

def sort_stories_by_votes(hnlist):
	return sorted(hnlist, key= lambda k:k['votes'], reverse=True) ## To Sort a Dictionary


def createCustomNews(links, subtext):

	hn = [] # List that will contain dictionary

	for idx, item in enumerate(links): #idx is a reference to index 

		title = links[idx].getText() # Get just the title of the story

		href = links[idx].get('href', None) # Get just the link of the story

		vote = subtext[idx].select('.score') # Get just the score of each story

		if len(vote): # if vote != 0

			points = int(vote[0].getText().replace(' points', '')) #convert string to int and replace " points" with an empty string

			if points > 99: #We only want stories with a score higher than 99

				hn.append({'title': title, 'link': href, 'votes':points}) #Append each item to list

	return sort_stories_by_votes(hn) #return sorted list
'''
pprint.pprint(createCustomNews(mega_links, mega_subtext)) # Used Pretty Print to print it out all nice
'''
'''
if you want to add more pages then you will have to make a new request for a new page
this can be done via a new function but has not been implemented yet.
'''
