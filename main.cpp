#include <bangtal.h>
#include <stdio.h>
#include "game.h"


const int G = 1;
const int TPS = 20;


enum class STATE { YELLOW, RED, BLUE, PURPLE };


SceneID scene1, scene2, scene3, scene4;
ObjectID play, exit, back1, back2, back3, blank, home, how_to_play, lock, next, sound, soundx, star, step1, step2, step3, step2x, step3x;
ObjectID player;

TimerID timer;

int x, y;
int y_speed;
int clickedStage;

bool isPlay = false;
bool isStarted = false;
bool issound = true;
bool isclear;
bool isAllStar;
STATE player_state = STATE::YELLOW;

SoundID sound1;


void draw() {

}

void tick() {
    draw();
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
    endGame();
}
void map_load(int stage) {
    if (stage == 1)
    {
        showMessage("1번맵 로드");
    }
    else if (stage == 2)
    {
        showMessage("2번맵 로드");
    }
    else if (stage == 3)
    {
        showMessage("3번맵 로드");
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
        clickedStage = 1;
        enterScene(scene3);
        map_load(clickedStage);

    }
    else if (object == step2)
    {
        clickedStage = 2;
        enterScene(scene3);
        map_load(clickedStage);
    }
    else if (object == step3)
    {
        clickedStage = 3;
        enterScene(scene3);
        map_load(clickedStage);
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
    //home = createObject("Images/home.png", scene1, 600, 300, false);
    how_to_play = createObject("Images/how_to_play.png", scene1, 1100, 70, true);
    //next = createObject("Images/next.png", scene1, 600, 300, true);
    sound = createObject("Images/sound.png", scene1, 70, 70, true);
    soundx = createObject("Images/soundx.png", scene1, 70, 70, false);
    //star= createObject("Images/star.png", scene1, 600, 300, true);
    step1 = createObject("Images/step1.png", scene2, 50, 250, true);
    step2 = createObject("Images/step2.png", scene2, 450, 250, false);
    step3 = createObject("Images/step3.png", scene2, 850, 250, false);
    step2x = createObject("Images/step2x.png", scene2, 450, 250, true);
    step3x = createObject("Images/step3x.png", scene2, 850, 250, true);
    //blank= createObject("Images/blank.png", scene1, 600, 300, true);
    player = createObject("Images/yellow.png", scene3, 500, 500, true);



    startGame(scene1);
    return 0;
}