#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.
        auto dis = (end - start) / (num_nodes);
        for(int i = 0; i < num_nodes; i++) {
            auto *node = new Mass(start + dis * i, node_mass, false);
            masses.push_back(node);
            if(i == 0) continue;
            auto *spr = new Spring(masses[i - 1], masses[i], k);
            springs.push_back(spr);
        }
        for(auto &i: pinned_nodes) {
            masses[i]->pinned = true;
        }
//        Comment-in this part when you implement the constructor
//        for (auto &i : pinned_nodes) {
//            masses[i]->pinned = true;
//        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        int total = 0;
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            Vector2D ba = s->m2->position - s->m1->position;
            auto BA = ba.norm();
            auto force = -1 * s->k * (ba.unit()) * (BA - s->rest_length);
            s->m1->forces += force;
            s->m2->forces -= force;
        }

        for (auto &m : masses)
        {
            auto k_d = 0.1;
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                m->forces += m->velocity + m->mass * gravity;
                m->position
                // TODO (Part 2): Add global damping
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet ???solving constraints)
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                
                // TODO (Part 4): Add global Verlet damping
            }
        }
    }
}
