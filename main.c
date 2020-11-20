//
//  main.c
//  BadApple
//
//  Created by flqy on 2020/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>



#define FRAME_WIDTH     80
#define FRAME_HEIGHT    32

// 头
#define DATA_TOKEN_SIZE    ( 5 + 1 )    //    $0000\n

// 后面接入换行
#define DATA_PITCH_SIZE    ( FRAME_WIDTH + 1 )        // ###...\n

// 一帧
#define DATA_FRAME_SIZE    ( DATA_TOKEN_SIZE + ( DATA_PITCH_SIZE * FRAME_HEIGHT ) )

// 总帧
#define FRAME_COUNT    3271

#define VIDEO_TIME    218000.0f    // 3:38 (218000ms)





int main(int argc, const char * argv[]) {
    // insert code here...
    
    FILE *fp;
    // 记录标签
    int index = 0;
    int size = DATA_FRAME_SIZE * FRAME_COUNT;
    
    char *buf = malloc(size);
    memset(buf,0,size);
    
    fp = fopen("/Users/flqy/Desktop/BadApple/BadApple/BADAPPLE.txt", "rb");
    if (fp == NULL) {
        printf("文件打开失败");
        return 1;
    }
    
    if (fread(buf, size - 1, 1, fp) != 1) {
        printf("文件读取失败");
        return 1;
    }
    char *cur;
    cur = malloc(DATA_FRAME_SIZE - DATA_TOKEN_SIZE);
    while (1) {

        
        char *temp;

        temp = &buf[ ( DATA_FRAME_SIZE * index ) + DATA_TOKEN_SIZE ];
        
        
        memset(cur, 0, DATA_FRAME_SIZE - DATA_TOKEN_SIZE);
        
        memcpy(cur, temp, DATA_FRAME_SIZE - DATA_TOKEN_SIZE);
        
        printf("%s",cur);
        
        
        index ++;
        usleep(60 * 1000); // Sleep(60); 60毫秒
        
        if (index == FRAME_COUNT) {
            // 播放完成
            break;
        }
        
    }
    free(cur);
    cur = NULL;
    return 0;
}
