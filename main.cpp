#include <bangtal.h>
#include <stdio.h>
#include "game.h"


const int G = 1;
const int TPS = 20;


enum class STATE { YELLOW, BLUE, RED, PURPLE };


SceneID scene1, scene2, scene3, scene4;
ObjectID play, exit, back1, back2, back3, blank, home, how_to_play, lock, next, sound, soundx, step1, step2, step3, step2x, step3x, ex1, ex2, ex3,clear;
ObjectID player;
ObjectID stars[6];
ObjectID blocks[32][18];

TimerID timer;

int arr[32][18];
int starPoints[6][2];

int star_count;
int x, y;
int ex, ey;
int x_speed;
int y_speed;
int stage = 0;
bool eatStar[6];
bool isPlay = false;
bool isStarted = false;
bool issound = true;
bool isclear;
bool isAllStar;
STATE player_state = STATE::YELLOW;

SoundID sound1;

void end()
{
    if (stage == 0)
    {
        endGame();
    }

    else if (stage == 1)
    {
        enterScene(scene2);
        isStarted = false;
        stage = 0;
    }
    else if (stage == 2)
    {
        enterScene(scene2);
        isStarted = false;
        stage = 0;
    }
    else if (stage == 3)
    {
        enterScene(scene2);
        isStarted = false;
        stage = 0;
    }

}
void tick() 
{
    x += x_speed;
    y += y_speed;

    locateObject(player, scene3, x - 10, y - 10);

    for (int i = 0; i < 6; i++) {
        if (eatStar[i]) continue;
        if (starPoints[i][0] <= x && x <= starPoints[i][0] + 30 && starPoints[i][1] <= y && y <= starPoints[i][1] + 30) {
            eatStar[i] = true;
            hideObject(stars[i]);
        }
    }

    if (ex <= x && x <= ex + 40 && ey <= y && y <= ey + 40) end();

    if (y_speed > -10) y_speed -= G;
    
    if (arr[x / 40][(720 - y + 10) / 40] == 1) y_speed = 9;

    if (isStarted) 
    {
        setTimer(timer, 1.f / TPS);
        startTimer(timer);
    }


}

void start() 
{
    if (!isStarted) 
    {
        x_speed = 0;
        y_speed = 0;

        isStarted = true;
        setTimer(timer, 1.f / TPS);
        startTimer(timer);
    }
}



void map_load(int stage) 
{
    if (stage == 1) 
    {
        for (int x = 0; x < 32; x++) 
        {
            for (int y = 0; y < 18; y++) 
            {
                arr[x][y] = map1[x][y];
            }
        }
        
        star_count = stars1;
        for (int i = 0; i < 6; i++) {
            if (i < star_count) {
                starPoints[i][0] = starsPoint1[i][0];
                starPoints[i][1] = starsPoint1[i][1];
                showObject(stars[i]);
                locateObject(stars[i], scene3, starsPoint1[i][0], starsPoint1[i][1]);
            }
            else hideObject(stars[i]);
        }

        x = map1_xs;
        y = map1_ys;
    
        ex = map1_xe;
        ey = map1_ye;
    }
    else if (stage == 2) 
    {
        for (int x = 0; x < 32; x++) 
        {
            for (int y = 0; y < 18; y++) 
            {
                arr[x][y] = map2[x][y];
            }
        }
        star_count = stars2;
        for (int i = 0; i < 6; i++) {
            if (i < star_count) {
                starPoints[i][0] = starsPoint2[i][0];
                starPoints[i][1] = starsPoint2[i][1];
                showObject(stars[i]);
                locateObject(stars[i], scene3, starsPoint2[i][0], starsPoint2[i][1]);
            }
            else 
            {
               hideObject(stars[i]);
            }
        }
        x = map2_xs;
        y = map2_ys;

        ex = map2_xe;
        ey = map2_ye;
        
    }
    else if (stage == 3) 
    {
        for (int x = 0; x < 32; x++) 
        {
            for (int y = 0; y < 18; y++) 
            {
                arr[x][y] = map3[x][y];
            }
        }

        star_count = stars3;
        for (int i = 0; i < 6; i++) {
            if (i < star_count) {
                starPoints[i][0] = starsPoint3[i][0];
                starPoints[i][1] = starsPoint3[i][1];
                showObject(stars[i]);
                locateObject(stars[i], scene3, starsPoint3[i][0], starsPoint3[i][1]);
            }
            else hideObject(stars[i]);
        }
        x = map3_xs;
        y = map3_ys;

        ex = map3_xe;
        ey = map3_ye;
    }
    for (int i = 0; i < star_count; i++) eatStar[i] = false;
    for (int i = star_count; i < 6; i++) eatStar[i] = true;

    for (int x = 0; x < 32; x++) 
    {
        for (int y = 0; y < 18; y++) 
        {
            if (arr[x][y] == 0) hideObject(blocks[x][y]);
            else if (arr[x][y] == 1) 
            {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/block.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
            else if (arr[x][y] == 2) 
            {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/up_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
            else if (arr[x][y] == 3) 
            {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/down_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40 - 12);
            }
            else if (arr[x][y] == 4) 
            {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/left_b.png");
                locateObject(blocks[x][y], scene3, x * 40 - 12, (17 - y) * 40);
            }
            else if (arr[x][y] == 5) 
            {
                showObject(blocks[x][y]);
                setObjectImage(blocks[x][y], "Images/right_b.png");
                locateObject(blocks[x][y], scene3, x * 40, (17 - y) * 40);
            }
        }
    }
    showObject(clear);
    locateObject(clear, scene3, ex, ey);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) 
{

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
        stage = 0;
        isStarted = false;
    }
    else if (object == soundx)
    {
        issound = false;
        stopSound(sound1);
        showObject(soundx);
    }
    else if (object == step2x)
    {
        showMessage("1");
    }
    else if (object == step3x)
    {
        showMessage("2");
    }
    else if (object == step1)
    {
        stage = 1;
        enterScene(scene3);
        map_load(stage);
        start();

    }
    else if (object == step2)
    {
        stage = 2;
        enterScene(scene3);
        map_load(stage);
        start();
    }
    else if (object == step3)
    {
        stage = 3;
        enterScene(scene3);
        map_load(stage);
        start();
    }


}

void keyboardCallback(int keycode, KeyState state) 
{
    
    if (keycode == 28 && state == KeyState::KEYBOARD_PRESSED)
    {
        setObjectImage(player, "Images/yellow.png");
        player_state = STATE::YELLOW;
    }
    else if (keycode == 29 && state == KeyState::KEYBOARD_PRESSED)
    {
        setObjectImage(player, "Images/blue.png");
        player_state = STATE::BLUE;
    }
    else if (keycode == 30 && state == KeyState::KEYBOARD_PRESSED)
    {
        setObjectImage(player, "Images/red.png");
        player_state = STATE::RED;
    }
    else if (keycode == 31 && state == KeyState::KEYBOARD_PRESSED)
    {
        setObjectImage(player, "Images/purple.png");
        player_state = STATE::PURPLE;
    }
    else if (keycode == 82 && state == KeyState::KEYBOARD_PRESSED) {
        x_speed = -5;
    }
    else if (keycode == 82 && state == KeyState::KEYBOARD_RELEASED) {
        x_speed = 0;
    }
    else if (keycode == 83 && state == KeyState::KEYBOARD_PRESSED) {
        x_speed = +5;
    }
    else if (keycode == 83 && state == KeyState::KEYBOARD_RELEASED) {
        x_speed = 0;
    }
}

void timerCallback(TimerID timer) 

{
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

int main() 
{
    setMouseCallback(mouseCallback);
    setKeyboardCallback(keyboardCallback);
    setTimerCallback(timerCallback);

    timer = createTimer(1.f / TPS);


    scene1 = createScene("main", "Images/home_background.png");


    scene2 = createScene("main", "Images/background.png");


    scene3 = createScene("game", "Images/background.png");
    scene4 = createScene("game", "Images/background.png");
    sound1 = createSound("Images/sound.mp3");

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
    step2 = createObject("Images/step2.png", scene2, 450, 250, true);
    step3 = createObject("Images/step3.png", scene2, 850, 250, true);
    step2x = createObject("Images/step2x.png", scene2, 450, 250, false);
    step3x = createObject("Images/step3x.png", scene2, 850, 250, false);
    blank= createObject("Images/blank.png", scene3, 600, 300, false);
    player = createObject("Images/yellow.png", scene3, 500, 500, true);
    ex1 = createObject("Images/excellent.png", scene2,50,100, false);
    ex2 = createObject("Images/excellent.png", scene2,450,100, false);
    ex3 = createObject("Images/excellent.png", scene2, 850,100, false);
    clear = createObject("Images/clear.png");
    for (int i = 0; i< 6; i++)
    {
         stars[i] = createObject("Images/star.png");
    }


    for (int x = 0; x < 32; x++) 
    {
        for (int y = 0; y < 18; y++) 
        {
            blocks[x][y] = createObject("Images/blocks.png");
        }
    }

    startGame(scene1);
    return 0;
}
