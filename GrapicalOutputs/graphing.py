import pandas as pd
import geopandas as gpd
import matplotlib.pyplot as plt
from shapely.geometry import LineString
import pydot



airports = pd.read_csv("../data/raw/airports.dat",delimiter=',',names=['id', 'name', 'city', 'country', 'iata','icao', 'lat', 'long', 'altitude', 'timezone','dst', 'tz', 'type', 'source'])
routes = pd.read_csv("../data/raw/routes.dat", delimiter=',', names=['airline', 'id', 'source_airport', 'source_airport_id',
                                                               'destination_airport', 'destination_airport_id', 'codeshare',
                                                               'stops', 'equitment'])
def write_dot(f, name):
    f.write("digraph {\nlayout=neato;\n")
    
    for index, row in airports.iterrows():
        f.write(str(row["id"])+" [pos=\""+str(row["long"])+"," +str(row["lat"])+"!\"]\n")
    for index, row in routes.iterrows():
        if((str(row["source_airport_id"])=="\\N") or (str(row["destination_airport_id"])=="\\N")):
            continue
        f.write(str(row["source_airport_id"])+"->"+ str(row["destination_airport_id"])+"\n")
    f.write("}\n") 
f=open("output.dot","w")
write_dot(f,"output")
#(graph,) = pydot.graph_from_dot_file('output.dot')
#graph.write_png('output.png')
#print(airports)
#print(routes)

