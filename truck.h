#ifndef TRUCK_H
#define TRUCK_H

#include "mapping.h"

#define MAX_WEIGHT 1200
#define MAX_VOL 50
#define NUM_TRUCKS 3

// Box Size / Volume
#define SIZE_S 0.5
#define SIZE_M 1
#define SIZE_L 5

struct Truck {
    double weight;      // Accumulative weight in KG
    double volume;      // Accumulative volume in m3
    struct Route route;
};

struct Shipment {
    double weight;      // Weight in KG
    double volume;      // Volume in m3
    struct Point point; // Destination
};

/**
 * Retrieve a `Truck` instance initialized with default values, representing
 * an empty truck with the blue route.
 * @returns - A `Truck` instance representing an empty truck with the blue route.
*/
struct Truck getBlueTruck();

/**
 * Retrieve a `Truck` instance initialized with default values, representing
 * an empty truck with the yellow route.
 * @returns - A `Truck` instance representing an empty truck with the yellow route.
*/
struct Truck getYellowTruck();

/**
 * Retrieve a `Truck` instance initialized with default values, representing
 * an empty truck with the green route.
 * @returns - A `Truck` instance representing an empty truck with the green route.
*/
struct Truck getGreenTruck();

/**
 * Check the validity of the given `Shipment` structure. Attributes of the
 * `Shipment` structure will be validated in the following order: `weight`,
 * `volume`, `point`.
 * @param s - The `Shipment` structure to validate
 * @returns - 1 if valid, 0 otherwise.
*/
int isValidInput(const struct Shipment* s);

/**
 * Calculate the percentage of filled space in the given `Truck` structure..
 * @param t - The `Truck` structure for which the percentage of filled space
 * is calculated.
 * @returns - The percentage of how full the truck is.
*/
double calTruckFillPercent(const struct Truck* t);

/**
 * Update the route of a `Truck` structure by replacing a segment of the
 * original route with the shortest path between the original route and
 * the destination. The segment of the original route where it diverges
 * from the shortest path to the destination will be removed. The
 * shortest path will be inserted at the point of divergence to the
 * destination.
 * @param t - The `Truck` structure
 * @param s - The `Route` structure to be inserted to the truck's
 * original route.
*/
void updateTruckRoute(struct Truck* t, const struct Route* r);

#endif