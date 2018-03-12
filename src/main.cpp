
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
    printf("size of wchar_t: %ld\n",sizeof(wchar_t));
    printf("size of unsigned short: %ld\n",sizeof(unsigned short));
    return MyGame().run();
}
