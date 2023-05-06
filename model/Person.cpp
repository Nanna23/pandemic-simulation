#include "PersonState.cpp"
#include "Position.cpp"

namespace Model
{
    class Person
    {
        Position position;
        PersonState state;

    public:
        Person() {
            this->state = SUSCETIBLE;
        }
        void setPosition(Position position) {
            this->position = position;
        }
        void evolveState() {
            if (state == SUSCETIBLE) {
                state = INFECTED;
            }
            else if (state == INFECTED) {
                state = REMOVED;
            }
        }
    };
}