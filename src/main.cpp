
#include <ginkgo.h>
#include "welcome.h"

using namespace std;

class MyGame : public Game
{
public:
    MyGame() : Game()
    {
        setTitle("Ginkgo2 Test");
        SceneWelcome *welcome = new SceneWelcome();
        replaceScene(welcome);
    }
};

int main()
{
    return MyGame().run();
}
