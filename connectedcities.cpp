#include "connectedcities.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

/**
 * <p>
 * Part A
 * ---------------------------------------------------------------------------------------
 * For each city in a city list, find the list of reachable cities starting from
the city
 * following the train routes, and sort the cities in the descending order based
on the
 * number of their reachable cities.
 *
 * Required specifications -
 *
 * Given a list of cities, and a list of one-way train routes from one city to
another:
 *
 * 1) Create a graph with each node in the graph as an instance of the CityNode
class,
 *    the graph can use any STL collection by your choice.
 *
 * 2) Populate the direct routes information to each CityNode's
directRoutedCities collection.
 *    This is like an adjacency list graph representation.
 *
 * 3) For each city node in the graph, use Depth First Search algorithm to find
all reachable
 *    cities starting from the city following the train routes and store those
reachable cities to
 *    the CityNode's reachableCities collection.
 *
 *    IMPORTANT: The reachable cities must include the starting city itself.
 *
 *    Note: The train route can go from the starting city and stop at several
cities
 *          before reaching the destination city, all cities including the
starting city and
 *          the destination city along the path would be counted as reachable
cities from
 *          the city where the train starts.
 *
 * 4) Sort the cities in the descending order based on the number of their
reachable cities,
 *    so that after sorting, starting from the first city in the sorted order,
the train can
 *    reach the greatest number of destination cities following the given
one-way routes.
 *
 * 5) You must use a RECURSIVE algorithm to implement the Depth First Search
part to find
 *    all reachable cities from a starting city given the train routes, using an
iterative
 *    approach would result in a 30% penalty to your assignment 4 grade.
 *
 * 6) You may add necessary helper functions as needed. Follow the comments for
hints.
 *
 * Assumptions -
 * 1) Each city is represented by a unique two-letter code like "SD", "LA",
 *    "SF", "SJ", "NY", etc.
 * 2) Each one-way train route is represented by a pair of city codes; for
example,
 *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to
 *    Los Angeles (LA).
 *
 * <p>
 * Part B
 * ---------------------------------------------------------------------------------------
 * Show the upper bound of the time complexity of this function would be O(c^2 +
c * r)
 * where:
 * c is the number of cities
 * r is the number of direct routes between cities
 *
 * ---------------------------------------------------------------------------------------
 * @param  cities  a list of cities with each city identified by a two letter
code
 * @param  routes  pairs of one-way train routes with each one-way train route
represented
 *                 by a pair of city codes; for example, route {"SD", "LA"}
means train
 *                 can go one-way from San Diego (SD) to Los Angeles (LA).
 *
 *                 NOTE: examples of routes are { {"SD", "LA"},
 *                                                {"LA", "SJ"},
 *                                                {"SJ", "SF"}
 *                                              }
 *                       refer to driver.cpp for more examples.
 *
 * @return       A list of CityNode in the descending order based on the number
of their
 *               reachable cities following the train routes

* @see
*/
void depthFirstSearchReachableCities(
    vector<CityNode> cityGraph, // a collection of a STL collection type
    string startingCity,
    vector<string> &reachableCities, // list of cities to add reachable cities
                                     // along the recursive call
    set<string> &visitedCities) {
  if (visitedCities.find(startingCity) == visitedCities.end()) {
    visitedCities.insert(startingCity);
    reachableCities.push_back(startingCity);
    for (int i = 0; i < cityGraph.size(); i++) {
      if (cityGraph[i].getCity() == startingCity) {
        for (int j = 0; j < cityGraph[i].getDirectRoutedCities().size(); j++) {
          depthFirstSearchReachableCities(
              cityGraph, cityGraph[i].getDirectRoutedCities()[j],
              reachableCities, visitedCities);
        }
      }
    }
  }
}

vector<CityNode>
ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(
    vector<string> cities, vector<pair<string, string>> trainRoutes) {

  // Write your implementation here.

  // Follow the steps in the specification above to implement.

  // You may want to implement each step in the above specification in
  // a separate function.

  // Think what would be a good data structure to store the City Graph.

  // Each node/vertice represents a city and each has an adjacent list of cities
  // that can be reached directly from the city.
  // You can use a STL collection to store
  // the graph of city nodes, so that given a city code,
  // you can find the corresponding CityNode object instantaneously.
  // Think Which data structure would give you the best lookup ability
  // by using a key.

  // Build the city Graph:
  //*1) create a city graph collection, and create CityNode objects for
  //*   all cities passed in.
  //* 2) Use the one way trainRoutes to populate the directRoutedCities of
  //*   each CityNode. directRoutedCities would be the adjacency list for
  //*  each CityNode
  
  vector<CityNode> cityGraph;
  // when the number of cities is c, the number of direct routes between cities
  // is r, the time complexity of this function is O(c^2 + c * r)
  // the time complexity of this function is O(c^2 + c * r) because the time
  // complexity of the city for loop is O(c^2) and the time complexity of the
  // train for loop is O(c * r) the time complexity of the for loop is O(c^2)
  // because the time complexity of the if statement is O(c) and the time
  // complexity of the for loop is O(c) the time complexity of the for loop is
  // O(c * r) because the time complexity of the if statement is O(c) and the
  // time complexity of the for loop is O(r) the time complexity of the if
  // statement is O(c) because its complexity is O(1) and the time complexity of
  // the for loop is O(c)
  for (int i = 0; i < cities.size(); i++) {//this is the city loop
    CityNode cityNode(cities[i]);
    cityGraph.push_back(cityNode);
    for (int j = 0; j < trainRoutes.size(); j++) {//this is the train loop
      if (trainRoutes[j].first == cities[i]) {
        cityGraph[i].addADirectRoutedCity(trainRoutes[j].second);
      }
    }
  }
  // Hint for DFS:
  // You may want to use a separate function to implement the
  // recursive Depth-First-Search algorithm for finding all reachable cities
  // starting from a city using its direct routes to other cities, and their
  // connected cities, and so on and so forth until all cities along
  // reachable paths are traversed.

  // Use the general approach described in zyBook 20.6 Graphs: Depth-first
  // search Follow what Figure 20.6.1 presents

  // A suggested separate recursive function for the DFS part could be:
  // void depthFirstSearchReachableCities(
  //      cityGraph, // a collection of a STL collection type
  //      string startingCity,
  //      vector<string> &reachableCities, // list of cities to add reachable
  //      cities along the recursive call set<string> &visitedCities); // list
  //      of cities to track if a city is already visited along DFS search
  // what would be the base condition? --> the startingCity is already visited
  vector<string> reachableCities;
  set<string> visitedCities;
  int maxReachableCities[cityGraph.size()];
  for (int i = 0; i < cityGraph.size(); i++) {
    depthFirstSearchReachableCities(cityGraph, cityGraph[i].getCity(),
                                    reachableCities, visitedCities);
    // print out the reachable cities for each city
    cityGraph[i].setReachableCities(reachableCities);
    maxReachableCities[i] = reachableCities.size();
    reachableCities.clear();
    visitedCities.clear();
  }
  // Hint for sorting: descending order of number of reachable cities and
  //                   ascending alphabetical order of the city code as the
  //                   tiebreaker
  // you can leverage the std::stable_sort()
  // one way to do the two-level of sorting here is to first sort the list
  // by City code in ascending order,
  // then sort by number of reachable cities in descending order.
  // print out the city graph with their total reachable cities
  map<string, int> cityGraphMap;
  for (int i = 0; i < cityGraph.size(); i++) {
    cityGraphMap[cityGraph[i].getCity()] =
        cityGraph[i].getReachableCities().size();
    // print out the reachable cities in the city graph map
  }

  // sort the city map using the city code in ascending order and the number of
  // reachable cities in descending order
  std::sort(cityGraph.begin(), cityGraph.end(),
            [](CityNode &left, CityNode &right) {
              if (left.getReachableCities().size() ==
                  right.getReachableCities().size()) {
                return left.getCity() < right.getCity();
              } else {
                return left.getReachableCities().size() >
                       right.getReachableCities().size();
              }
            });
  return cityGraph; // vector<CityNode>() here is a placeholder, you need to
                    // change it to whichever the vector your logic comes up
                    // with and return
}
/* Part B]
  * ---------------------------------------------------------------------------------------
  * Show the upper bound of the time complexity of this function would be O(c^2
+ c * r)
  * where:
  * c is the number of cities
  * r is the number of direct routes between cities
//   to show this, you need to explain how you came up with the upper bound of
the time complexity of this function
    * ---------------------------------------------------------------------------------------
    */
