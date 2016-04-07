# Mission Populate
Problem :
Give a list of minimum school sites to be built such that at least one school is within 1Km of every house.

Solution :
The program takes an input file which defines a connected graph of house and school vertices. After graph validation, a set is made for each school containing house vertices within 1Km of the school using Dijkstra's SSSP implementing the heap module. Then, set cover is used to output a minimum number of sets such that it covers all houses.
The solution is the school vertex corresponding to the selected sets. 
