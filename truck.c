#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "truck.h"
#include "mapping.h"

struct Truck getBlueTruck() {
    return (struct Truck) { 0, 0, getBlueRoute() };
}

struct Truck getYellowTruck() {
    return (struct Truck) { 0, 0, getYellowRoute() };
}

struct Truck getGreenTruck() {
    return (struct Truck) { 0, 0, getGreenRoute() };
}

/**
 * Check the validity of the given `Shipment` structure. Attributes of the
 * `Shipment` structure will be validated in the following order: `weight`,
 * `volume`, `point`.
 * @param s - The `Shipment` structure to validate
 * @returns - 1 if valid, 0 otherwise.
*/
int isValidInput(const struct Shipment* s) {
    // weight -> volume -> point
    return s->weight <= MAX_WEIGHT &&
        s->volume <= MAX_VOL &&
        s->point.row <= MAP_ROWS &&
        s->point.col <= MAP_COLS;
}

/**
 * Calculate the percentage of filled space in the given `Truck` structure..
 * @param t - The `Truck` structure for which the percentage of filled space
 * is calculated.
 * @returns - The percentage of how full the truck is.
*/
double calTruckFilledPercent(const struct Truck* t) {
    // Calculate the percentage of weight and volume
    double wPercent = t->weight / MAX_WEIGHT;
    double vPercent = t->volume / MAX_VOL;

    // Returns the bigger one
    return wPercent > vPercent ? wPercent : vPercent;
}

/**
 * Helper function
 * Retrieve the index of the point on the original route where starting
 * from this index, shortest path differs from the original route.
*/
int getDivergenceIndex(const struct Route* r, const struct Point* p) {
    int i = 0;
    for (; i < r->numPoints; ++i) {
        if (r->points[i].row == p->row && r->points[i].col == p->col) return i + 1;
    }
    return -1;
}

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
void updateTruckRoute(struct Truck* t, const struct Route* r) {
    struct Route* route = &(t->route);

    int divIndex = getDivergenceIndex(route, &(r->points[0]));

    /**
     * Update numPoints
     * 0 1 2 3 4 5
     *       *
     * oNumPoints - divIndex + rNumPoints
     *     6      -    4     +     1      = 5
     *     6      -   (4     -     1)     = 5
     *
     * route->numPoints = route->numPoints - (divIndex - r->numPoints);
    */
    route->numPoints -= (divIndex - r->numPoints);

    // Replace part of the original route with the shortest path
    int i = 1;
    // for (; i < r->numPoints; ++divIndex, ++i) {
    //     route->points[divIndex] = r->points[i];
    // }
    while (i < r->numPoints) {
        route->points[divIndex++] = r->points[i++];
    }
}