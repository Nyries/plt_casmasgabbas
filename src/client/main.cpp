#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    //test();
    cout << "It runs !" << endl;
    state::SuspectCard totoCard(PERVENCHE);
    if (totoCard.getSuspectName() == PERVENCHE) {
        cout << "yay!" << endl;
    }

    return 0;
}
