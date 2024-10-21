TINAPE
======

This is not a Physics engine but a Collision engine.

This Project aims to create an efficient collision engine for a 2D scene.
It is optimized for a niche scenario and does not want to be general.
But within this scenario it aims to be very efficient.

Scenario
--------

TINAPE is a collision engine that handles the collision between:

- static circles
- static polygons
- dynamic circles

### Scene

*dynamic circles*:
amount: ~2^14
diameter: between 1 and 4 units
velocity: between 0 and 4 units/update

*dynamic circles*:
t.b.d.

*static polygons*:
t.b.d.

*region*:
density: 1 element per cell
=> min width: 2^7
=> min height: 2^7

The aim for TIMAPE is to handle more or less uniformly distributed
with at least 40 FPS (25 ms per update) on decent server hardware.
TINAPE is optimized to be single threaded as it is not optimized for
performance at any cost, but enough performance at good efficiency.

Strategy
--------

TINAPE uses a broad phase and a narrow phase to resolve collisions.

### Broad Phase

Takes all dynamic circles and creates islands of dynamic circles that are possible to collide.
Uses a dense grid structure to reduce aabb comparisons.
Then uses a graph structure from the local aabb comparisons and a dfs to detect islands.

The dense grid assumes that the velocity is not bigger than the diameter of a circle
and a minimum diameter of not less than a fourth of the max diameter.
Assuming that circles do not overlap the amount of circles per grid cell is limited to 16.
Together with all neighbour cells this means at max:

1. 16 * 16 / 2 = 128 comparisons in local cell for 16 elements.
   (amortized 8 comparisons per element)
2. 16 * 16 comparisons per neighbour cell for 16 + 16 = 32 elements.
   (amortized 8 comparisons per element per neighbour)

Leading to a maximum of 72 comparisons per element.

In benchmarks most circles will have a diameter of 2 leading to max 36 comparisons per element.
With the assumption of a uniform distribution at most 1 circle per cell is expected leading to
average 8 comparisons per element.
Optimizing further than 8 comparisons makes not much of a sense as
every neighbour cell must be fetched in the dense grid what is probably
the bottleneck for the broad phase.

Input/Pass:

- static circles (location optimized collection of circles)
- static polygons (location optimized collection of polygons)
- dynamic circles (iteration + random access optimize collection of dynamic circles)
- delta time

Output:

- islands (collections of dynamic circles that might collide)

### Narrow Phase

Makes a collision resolution per island.

Input:

- everything from the broad phase

Update:

- dynamic circles
