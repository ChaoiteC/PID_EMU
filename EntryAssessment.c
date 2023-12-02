/* 参赛考核的任务是：
 *     在此文件的基础上进行修改，加入你的PID相关代码。
 *     读取emuBall.position与emuBall.speed作为PID
 *     的反馈，将PID输出作为ball_calculate函数的参数
 *     来推动小球，在30秒内使小球位置于-2.5~2.5内并
 *     保持10秒。
 * 
 * 提交你的文件时要做好接受提问的准备:)
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INTERVAL_TIME 0.05  // 两次物理模拟的间隔时间

typedef struct {
    float position;  // 位置，左负右正
    float speed;     // 速度，左负右正
    float ref;       // 期望
    float force;     // 受力（输出），左负右正
    float force_i;   // 恒力
    float mass;      // 质量
} ball;

ball emuBall;

/**
 * @brief 物理模拟计算，每INTERVAL_TIME秒运行一次
 *
 * @param myBall 参与物理模拟的小球结构体的地址
 * @param force  推动小球的力量
 *
 * @return void
 */
void ball_calculate(ball *myBall, float force) {
    emuBall.force = force;

    // 使用牛顿的第二定律 F = ma 来计算加速度
    float acceleration = (myBall->force + myBall->force_i) / myBall->mass;

    // 使用匀变速直线运动的位移公式 s = ut + (1/2)at^2 来计算位移
    float initialSpeed = myBall->speed;
    float displacement = (initialSpeed * INTERVAL_TIME) + (0.5 * acceleration * INTERVAL_TIME * INTERVAL_TIME);

    // 更新小球的位置和速度
    myBall->position += displacement;
    myBall->speed = initialSpeed + (acceleration * INTERVAL_TIME);
}

/**
 * @brief 模拟小球各参数初始化
 *
 * @param myBall 参与物理模拟的小球结构体的地址
 * @param initialPosition 初始位置
 * @param initialSpeed 初始速度
 * @param ref 期望
 * @param initialForce 初始速度
 * @param mass 重量
 *
 * @return void
 */
void ball_init(ball *myBall, float initialPosition, float initialSpeed, float ref, float initialForce, float mass) {
    myBall->position = initialPosition;
    myBall->speed = initialSpeed;
    myBall->ref = ref;
    myBall->force = initialForce;
    myBall->mass = mass;
}

/*在这里编写你的PID相关代码*/



/*在这里编写你的PID相关代码*/

void draw_display(float time) {
    char line[] = "|--------------------0--------------------|";
    if (emuBall.position < -105) {
        line[0] = '*';
    } else if (emuBall.position > -2.5 && emuBall.position < 2.5) {
        line[21] = '*';
    } else if (emuBall.position < 105) {
        line[1 + ((int)emuBall.position + 105) / 5] = '*';
    } else {
        line[42] = '*';
    }
    line[43] = '\0';
    printf("%s\t", line);
    printf("T:%.2f,P=%.2f,F=%.2f,V=%.2f\n", time, emuBall.position, emuBall.force, emuBall.speed);
}

int main() {
    printf("  <PID Simulation System>\n");
    printf("Copyright (C) 2023  408 Lab.\n");

    srand((unsigned)time(NULL));
    float position_random;

    /*在这里编写你的PID初始化代码*/



    /*在这里编写你的PID初始化代码*/

    do {
        position_random = (rand() % 3600) - 1800;
    } while (!(position_random < -800 || position_random > 800));

    ball_init(&emuBall, position_random, 0, 0, 0, 1);

    float time = 0;
    float pass = 0;
    draw_display(time);

    while (1) {

        time += INTERVAL_TIME;
        /*在这里编写你的PID计算代码*/
        


        /*在这里编写你的PID计算代码*/
        ball_calculate(&emuBall, /*将你的PID输出输入到这里*/);
        draw_display(time);

        if (emuBall.position > -2.5 && emuBall.position < 2.5) {
            pass += INTERVAL_TIME;
            if (pass >= 10.0) {
                printf("The BALL converges on REFEENCE in %.2f seconds! Congratulations!", time - 10.0);
                system("pause");  // 此行如果报错或不工作可以删去。
                return 0;
            }
        } else {
            pass = 0;
            if (time > 30.0) {
                printf("You have not made the BALL converge at the REFEENCE point within 30 seconds.");
                system("pause");  // 此行如果报错或不工作可以删去。
                return -1;
            }
        }

        Sleep(20);  // 将此行删去会使模拟几乎瞬间完成.如果报错或不工作可以删去。
    }
}
