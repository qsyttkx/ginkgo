
#include <ginkgo.h>
#include "welcome.h"

using namespace std;

class MyGame : public Game
{
public:
    MyGame() : Game()
    {
        setTitle("Ginkgo2 Test");
        SceneLoading *loading = new SceneLoading();
        replaceScene(loading);
    }
};

int main()
{
    return MyGame().run();
}
