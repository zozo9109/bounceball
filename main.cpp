#include <bangtal.h>
#include <stdio.h>
#include "game.h"


const int G = 1;
const int TPS = 20;


enum class STATE { YELLOW, BLUE, RED, PURPLE };


SceneID scene1, scene2, scene3, scene4;
ObjectID play, exit, back1, back2, back3, blank, home, how_to_play, lock, next, sound, soundx, step1, step2, step3, step2x, step3x;
ObjectID player;

ObjectID blocks[32][18];

TimerID timer;

int arr[32][18];

int x, y;
int x_speed;
int y_speed;
int stage = 0;

bool isPlay = false;
bool isStarted = false;
bool issound = true;
bool isclear;
bool isAllStar;
STATE player_state = STATE::YELLOW;

SoundID sound1;


void tick() {
    if (isStarted) {
        setTimer(timer, 1.f / TPS);
        startTimer(timer);
    }
}

void start() {
    if (!isStarted) {
        isStarted = true;
        setTimer(timer, 1.f / TPS);
        startTimer(timer);
    }
}

void end() {
    if (stage == 0) endGame();
    else if (stage == 1) {
        showMessage("1단계 클리어");
        showObject(blank);
        showObject(home);
        showObject(next);
    }
    else if (stage == 2) {
        showMessage("2단계 클리어");
        showObject(blank);
        showObject(home);
        showObject(next);
    }
    endGame();
}

void map_load(int stage) {
    if (stage == 1) {
        for (int x = 0; x < 32; x++) {
            for (int y = 0; y < 18; y++) {
                arr[x][y] = map1[x][y];
            }
        }
        x = map1_x;
        y = map1_y;
    }
    else if (stage == 2) {
        for (int x = 0; x < 32; x++) {
            for (int y = 0; y < 18; y++) {
                arr[x][y] = map2[x][y];
            }
        }
        x = map2_x;
        y = map2_y;
    }
    else if (stage == 3) {
        for (int x = 0; x < 32; x++) {
            for (int y = 0; y < 18; y++) {
                arr[x][y] = map3[x][y];
            }
        }
        x = map3_x;
        y = map3_y;
    }

    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 18; y++) {
            if (arr[x][y] == 0) hideObject(blocks[x][y]);
            else if (arr[x][y] == 1) {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/block.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
            else if (arr[x][y] == 2) {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/up_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
            else if (arr[x][y] == 3) {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/down_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40 - 12);
            }
            else if (arr[x][y] == 4) {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/left_b.png");
                locateObject(blocks[x][y], scene3, x * 40 - 12, (17 - y) * 40);
            }
            else if (arr[x][y] == 5) {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/right_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
        }
    }
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    if (object == play)
    {
        enterScene(scene2);
    }
    else if (object == exit)
    {
        end();
    }
    else if (object == sound)
    {

        if (issound)
        {
            playSound(sound1);
            setObjectImage(sound, "Images/soundx.png");
            issound = false;
        }
        else if (issound == false)
        {
            stopSound(sound1);
            setObjectImage(sound, "Images/sound.png");
            issound = true;
        }
    }
    else if (object == how_to_play)
    {
        enterScene(scene4);
    }
    else if (object == back1)
    {
        enterScene(scene1);
    }
    else if (object == back2)
    {
        enterScene(scene1);
    }
    else if (object == back3)
    {
        enterScene(scene2);
    }
    else if (object == soundx)
    {
        issound = false;
        stopSound(sound1);
        showObject(soundx);
    }
    else if (object == step2x)
    {
        showMessage("1단계를 먼저 클리어 하세요");
    }
    else if (object == step3x)
    {
        showMessage("2단계를 먼저 클리어 하세요");
    }
    else if (object == step1)
    {
        stage = 1;
        enterScene(scene3);
        map_load(stage);

    }
    else if (object == step2)
    {
        stage = 2;
        enterScene(scene3);
        map_load(stage);
    }
    else if (object == step3)
    {
        stage = 3;
        enterScene(scene3);
        map_load(stage);
    }


}

void keyboardCallback(int keycode, KeyState state) {

    if (keycode == 28)
    {
        setObjectImage(player, "Images/yellow.png");
        player_state = STATE::YELLOW;
    }
    else if (keycode == 29)
    {
        setObjectImage(player, "Images/blue.png");
        player_state = STATE::BLUE;
    }
    else if (keycode == 30)
    {
        setObjectImage(player, "Images/red.png");
        player_state = STATE::RED;
    }
    else if (keycode == 31)
    {
        setObjectImage(player, "Images/purple.png");
        player_state = STATE::PURPLE;
    }

}

void timerCallback(TimerID timer) {
    tick();
}



ObjectID createObject(const char* image, const SceneID scene, int  x, int  y, bool isshown)
{
    ObjectID ob = createObject(image);
    locateObject(ob, scene, x, y);
    if (isshown)
        showObject(ob);
    return ob;
}

int main() {
    setMouseCallback(mouseCallback);
    setKeyboardCallback(keyboardCallback);
    setTimerCallback(timerCallback);

    timer = createTimer(1.f / TPS);


    scene1 = createScene("main", "Images/home_background.png");


    scene2 = createScene("main", "Images/background.png");


    scene3 = createScene("game", "Images/background.png");
    scene4 = createScene("game", "Images/background.png");
    sound1 = createSound("Images/배경음.mp3");

    play = createObject("Images/play.png", scene1, 600, 300, true);
    exit = createObject("Images/exit.png", scene1, 850, 300, true);
    back1 = createObject("Images/back.png", scene2, 30, 650, true);
    back2 = createObject("Images/back.png", scene4, 30, 650, true);
    back3 = createObject("Images/back.png", scene3, 30, 650, true);
    home = createObject("Images/home.png", scene3, 600, 300, false);
    how_to_play = createObject("Images/how_to_play.png", scene1, 1100, 70, true);
    next = createObject("Images/next.png", scene3, 600, 300, false);
    sound = createObject("Images/sound.png", scene1, 70, 70, true);
    soundx = createObject("Images/soundx.png", scene1, 70, 70, false);
    step1 = createObject("Images/step1.png", scene2, 50, 250, true);
    step2 = createObject("Images/step2.png", scene2, 450, 250, false);
    step3 = createObject("Images/step3.png", scene2, 850, 250, false);
    step2x = createObject("Images/step2x.png", scene2, 450, 250, true);
    step3x = createObject("Images/step3x.png", scene2, 850, 250, true);
    blank= createObject("Images/blank.png", scene3, 600, 300, false);
    player = createObject("Images/yellow.png", scene3, 500, 500, true);

    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 18; y++) {
            blocks[x][y] = createObject("Images/blocks.png");
        }
    }

    startGame(scene1);
    return 0;
}
