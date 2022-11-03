## Leading Question

Given a dataset of airports and their connection to other airports around the world, we will construct a program that outputs the shortest distances between an airport and airports to other locations - such as paths 

- Main goal is to take a data set of airports in order to give a user the ability to find the shortest path between two airports
- Types of ideas will be the path between each of the airports in the countries where the olympics took place, or visiting every capital of the world, formula 1 tracks, historic events, sports, movie locations, nuclear facilities, etc.
- The weight of each edge will be the raw distance between the two airports, calculated with the longitude and latitude.

## Data Acquisition and Processing
	
The data set we are using is the “OpenFlights” data set from 	https://openflights.org/data.html

Use DFS to traverse the graph to find the inputted airport. Call Dijsktra’s Algorithm on the found node to calculate the distance from the source location to its connected airports. 


## Data Format 

Our data is available in the ‘.dat’ format. Using this, there are simple c++ tools to read through the data and populate our data structure. We will initially read a small number of data in order to make sure our program works on smaller data. There are millions of lines of data, so will start with just one hundred, and slowly grow. The full, raw airports data set is 1MB and the routes data set is 2MB. 
 
## Data Correction (Data Cleaning) 

Because we have so many lines of data, we can afford to be very strict with the data we store. This means that if there is any field of data that is not fitting with our expectations, we will remove it entirely. Also, the longitude and latitude coordinates for each airport will be rounded to the second decimal place. 

## Data Storage

We will store the dat files locally, on our machines. This is enough for our task because the data itself is constant, there is little to no benefit to storing it on the internet. Reading the data and populating the correct data structures will be linear with respect to the length of the data. Reading each airport will take linear time, and then making the routes for each airport will be at worst squared time.
 


## Graph Algorithms

Our first function would build the graph from the csv input file that contains nodes and edges. After building our graph with all nodes as airports and establishing edge connections, we will be using DFS to check if the source and target nodes exist. If they exist, Dijkstra's algorithm finds the distance between a target node and the current source node. We will finally graphically project our created graph onto a world map using map API. The map will show each airport and the connections that it has to the rest of the airports. Once the shortest path between two airports is found, we will highlight the edges for that path.

## Function Inputs

Our first function will have the two CSV files, airport.dat and routes.dat as inputs and will build the graph based on the given nodes and edges. The second major function will take the source node and target node as an input and check if there exists a path using DFS. Thirdly, the final Dijkstra’s algorithm will take the source and target nodes as an input to locate the shortest path that exists between the source and target nodes. Lastly, our graphical output function will take in the connected graph and output it using an API.

## Function Outputs

Our first function will create airport nodes and establish connections between them using routes.dat. We might store the airports in a vector to access them in O(1) time.We will also have an airport subclass and we will assign values to the instance variables with the first airport as the root/start node of the graph. Each Airport object will have the Airport ID, Name, Latitude, Longitude, and a vector of neighbor airports. The second function will output a boolean to check if the source and target nodes exist, and the third one will output the length of the shortest path between the source and target node. The fourth one will output the graph on an API. 


## Function Efficiency

The function that builds our graph will have O(n^2) runtime and O(n) storage. The second function should have O(m+n) runtime where m is the number of edges and n is the number of airport nodes. Our target storage efficiency for this one is O(n). The third function implements Dijkstra’s algorithm, so it should have O(n2) time complexity and O(n) space complexity. Our fourth and graphical output function will have O(n) time complexity and O(1) space complexity.
 
## Timeline

We will aim to finish the data input and cleaning done by the 11th of November. We will try to finish the searching algorithms by the end of Fall break, the 27th of November. We are also aiming to output this onto a graph visually. We estimate that this will take us the rest of the time till the deadline. All of these deadlines are tentative.
