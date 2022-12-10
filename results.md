                                                  CS 225 Project Report: Team18

                               Aamir Hafiz, Alexis Serrano, Lorenzo Bujalil Silva, Aryan Malhotra

**Data Parsing:**

We needed to read the airports.dat and routes.dat csv files, and store the information about airports and routes in our Project class.

The “readRoutes” function takes in a string “path” and reads the .dat file stored at the location given by the input parameter. It stores the sources of the paths in a vector “from” and the destinations in the vector “to”. This function can be found in the ‘Project’ class in the corresponding ‘.cpp’ and ‘.h’ files in the ‘src’ folder.

The “readAirports” function takes in a string “path” and reads the .dat file stored at the location given by the input parameter. It stores all the airport IDs and 4-letter codes in the “airports” and “airportCode” vectors. The function also stores 4-letters codes and airport IDs in the “airportMap” map. The 4-letter code is the key and the airport ID is the value. It also stores the latitudes and longitudes of airports in “latitudes” and “longitudes” maps. The key of these maps is the airport ID and the value stores the latitude/longitude of that airport. This function can be found in the ‘Project’ class in the corresponding ‘.cpp’ and ‘.h’ files in the ‘src’ folder.

As mentioned in the project proposal, we said we will read the two .dat files locally on our machine and we will use it in order to make the graph’s nodes and edges. We were able to complete this successfully. Through these two file paths we are able to make all the data structures for our program.
<br/><br/>


**Graph:**

Our project utilizes the graph concept because the core of our project relies on having an airport id as a key and the neighboring airport ids as a value. 

We utilized the C++ ‘map’ feature in order to implement the graph. Also, we utilized the data parsing to make this graph. Having these two dependencies allowed the graph implementation to be useful.

The graph maps an integer to a vector of integers. The key represents the airport ID and each integer of the vector represents the airport ID of a neighboring airport. This data structure is a private member function of the ‘Project’ class in the ‘.h’ files in the ‘src’ folder. There are several other maps in our implementation, but there is only one graph. The others are to help us get other information about each airport or help us make our program more efficient.

In our proposal, we said that we would be able to populate the graph while reading the data, which we successfully completed.

<br/><br/>


**Depth First Search:**

Our program utilizes Depth First Search to determine whether a connection (or path) exists between airports. DFS is also used before calling Dijkstra’s Algorithm, which finds the shortest path, so the algorithm is not run for two nodes that have no connection. 

The “AirportConnection” function runs a helper function that performs Depth First Search recursively to traverse the graph from a string “source” to a string “destination.” Before DFS occurs, the function checks if the inputted airport codes exist as airports from the dataset. Through the traversal, each adjacent node is searched. If the “destination” node is found from one of the adjacent nodes starting from the source node, the function returns true. If the destination node was not found throughout the traversal, the function returns false. 

In the “Function Inputs” section of our project proposal, we initially planned to create a function implementing DFS to check if a path exists between a source node and destination node, then the function should return a boolean. As mentioned above, this function was created and fulfills our original goals. 

Our DFS is implemented in the AirportConnection function with a private helper function called DFSHelper . Both functions can be found in the ‘Project’ class in the corresponding ‘.cpp’ and ‘.h’ files in the ‘src’ folder. 


<br/><br/>

**Dijkstra’s Algorithm:**

Dijkstra’s is the main algorithm that we use to build the minimum spanning tree for a source airport and find the shortest path to the destination airport. It is essentially the motivation behind our project.

It uses a helper function called “minDistance” to get the airport with the minimum edge weight among all the included airports. This is basically what is done in Prim’s Algorithm. The “dijkstra's” function takes in an adjacency list, which is mentioned above, as well as a source ID. The keys of this map are airport IDs and the value is the shortest distance between the source and that airport. The “dijkstra's” function also builds the adjacency list of the minimum spanning tree (MST) which helps in the graphical representation of the spanning tree for that source airport. In the function “shortestPath”, which takes in “from” and “to” 4-letter ICAO strings, we convert them to IDs, and run the “dijkstras”  mentioned above. It accesses the value of the map returned by dijkstra's present at the key with the airport ID of the destination. Returning to the shortestPath function, we return the value of the shortest path.

Referring to the project proposal, we mentioned that Dijsktra’s algorithm would run in squared-time and we were able to achieve that. The algorithm works correctly on the sample files we created as well as the raw dataset. As we proposed, our code displays the MST for each source node using the functionality talked about in the next section. It also highlights the source and destination airport nodes with red and green, respectively, in the graphical output of the spanning tree.


Minimum Spanning Tree for O’Hare as source airport

![MST](MST_KORD.png?raw=true "MST_KORD")




<br/><br/>
**Graph Image:**

To output our minimum spanning tree (MST) as well as our full map, we decided to display our graphs using the png format. We wanted to do this because it can visualize the connections between the airports.

In order to produce a graphical image of the airports and their respective connections, we used the C++ graphical output API “Graphviz.” We installed the graphviz package before creating graphs and instructions on how to install are featured below.  “Graphviz” requires a .dot file with proper formatting to inorder to display an image of a graph. We used C++ to write to a new file that would format the .dot file and would iterate through our previously created adjacency list to create each node and edges between each node. Each of the nodes are written to the .dot file using a force-directed placement to give the illusion of a world map visualization. Once the entire adjacency list is iterated then we call a system command that converts the .dot file to a .png file.

In the “Graph Outputs” section of our proposal, we mentioned that we would project or graph onto the world map to give the user a visual representation of all airport connections. We mentioned that we wanted to highlight the path. In our program, we outline the path between the starting and destination nodes, while also highlighting nodes the path travels. Our goal was to make a force-directed graph, which we were successfully able to complete.

The graphical representation image, which represents a graph with all airports and connections, is implemented in the “PrintFullMap” function. Another graphical representation image called “printMST”, which represents the Minimum Spanning Tree of a certain source, is implemented in the dijkstra’s algorithm. This function has the same implementation as the “PrintFullMap” function, except it iterates through a newly created adjacency list made when our dijkstra's algorithm was called, and it colors the source and destination. “printShortestPathMap” can be found in the ‘Project’ class in the corresponding ‘.cpp’ and ‘.h’ files in the ‘src’ folder. The .png image is titled “graph.png” and saved into the main, root project directory. Another .png is generated displaying the shortest path of the two nodes. This image is called “‘source’” +  “destination” + ‘shortest_path’”.png

Graph of Every Airport

![Graph](graph.png?raw=true "Full Map")

<br/><br/>


**Test Suites:**

To make sure we were confident in our program's functionality, we included test suites. We wanted to test every function separately to know our implementation was working how we expected it to, every step of the way. 

In order to ‘test’, we have to know what the expected output is. It is difficult to know how thousands of airports exist in relation to one another, so we decided on writing several smaller sample airports and routes files. These can be found in the data folder, in the sample sections. We included 9 airports and 10-15 routes in our main sample dataset.

Onto the functionality of the test suites, we decided to test the output of the function by ‘hard-writing’ what the expected output is. Finding the expected results is much easier to do on the test files rather than the large, raw files. Our strategy was to ‘hand-compute’ the expected output of each function, and create the expected output, whether that be an integer, a vector of strings, or a map of key strings and value vectors of strings. After initializing the expected output, we would check that our program’s output was identical. Although CS 225 utilizes ‘catch2’ to test their machine projects, we used the ‘assert’ feature C++ provides in order to know the output was identical. All of the test functions’ implementations can be found in the test folder (test.cpp). The corresponding header file can be found in the includes folder (test.h).

Although this work is not explicitly written in our project proposal, the assumption that our programs work as planned requires the need for test suites. If we wrote implementations without testing, our program might be faulty and if used in the real world, would cause further issues.

Minimum Spanning Tree for one test sample

![singlepath](singlepath_test.png?raw=true "singlepath")


<br/><br/>

**Result:**

All the functions that we proposed in the project proposal work correctly with the target runtimes we had in mind. We have successfully created a project that answers our leading question. Given a dataset of airports and routes, our project finds the shortest distance between two airports provided by the user, if a path exists. We used the Euclidean distance between latitudes and longitudes of airports to assign edge weights and create our graph. We run DFS and Dijkstra's algorithm to find the shortest distance between the source and destination airports and generate graphical outputs as discussed above.
