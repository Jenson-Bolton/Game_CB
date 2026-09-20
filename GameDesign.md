# CityBuilder

A gridless city building game that does more planning than building.

## Inpirations

 - Cities Skylines
 - https://www.youtube.com/@jamessimo
 - Townscraper
 - Tiny Glade
 - Manor Lords
 - Equillinox

## Technologies

 - Wave function collapse
 - Marching cubes

## Gameplay

### Overview

Based around Japanese zoning and Czech mapping, the game is played through a 
planning overlay. Your city is planned rather than placed.

### Start

The game starts buy revealing a piece of terrain surrounded by fog. Some 
external connection exist, such as roads, power, sewage. This starting area has
mainly field / forest parcels. Player start buy drawing a basic road then 
selecting some parcels to be devloped.

### Planning and Parcels

A Japanese style planning matrix is used in combination with other planning 
restrictions. Parcels will form to look like a Czech castradal map.

A parcel will likely start as a field. This will be then assigned a zoning type
defining what can be built on it, as well as restrictions such as building 
floor ratio, height limits, set backs, noise restriction (for industrial and
commercial zoning types). After the development loop the parcel will now 
reflect in the castradal view, showing subdivisions, ownership, buildings.

### Devlopment Loop

Most buildings in the game will be created through the following process: 

 - Zone parcel(s)
 - Developer is selected to utilise the parcel
 - Parcel may then be subdivided and it's usage is determined
 - Buildings are erected

Let's think of an city block as an example. The game will function as:

 - Parcel is zoned for housing, small offices and shops.
 - Height restriction, set backs, floor ratio and other restrictions are set
 - A bidding session is started between, people, companies and goverment
 - This plot is large and has high potential for an apartment block
 - Regular people lose the bid as the parcel land is too expensive
 - Goverment has no use for the land so never bids
 - A large established company has the captital to out bid and build cheap
 - This company wins
 - The company subdivides the parcel into two buildings and an alley way
 - Buildings are errected

### Constructions and Contracts

Companies will function largely with contracts. This can best be seen in
how construction works.

 - Developer requires building materials
 - A contract is sent out and, in a similar fashion as development, is bid on
 - Contracts will factor in, quality, quantity, relationship, logistics, cost
 - Once a contract is formed and delivered on (or not)

### Finances

Finances will be managed in a simplfied UK system. The local goverment (the 
player) earns money through land value taxes (council tax, business rates), 
fees, services (public transport, managed properties)

## General Ideas

 - Services, such as public transport, can be publicly, privately, combined
  managed. If the player grows the city to a sufficent size and has a zoning
  applicable to say a bbus garage then a private company could start a bus 
  company. The player could also put out a contract for a transport company, 
  a private company then bids on the contract and eventaully a tfl style bus 
  network forms where routes are contract and private companies run it. The 
  player can always start their own company, they will still have to face 
  competition if their services are not complete.
 - 
