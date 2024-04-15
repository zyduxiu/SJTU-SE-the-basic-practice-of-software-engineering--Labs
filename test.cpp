#include "test.h"
#include <QTest>

void testlink::whetherlink_test_case1(){
    single_modee* sample=new single_modee;
    for(int i=0;i<7;i++){
        sample->block[i].x=i;
        sample->block[i].y=0;
        sample->block[i].lscore=0;
    }
    for(int i=7;i<14;i++){
        sample->block[i].x=i-7;
        sample->block[i].y=6;
        sample->block[i].lscore=0;
    }
    for(int i=14;i<19;i++){
        sample->block[i].x=0;
        sample->block[i].y=i-13;
        sample->block[i].lscore=0;
    }
    for(int i=19;i<24;i++){
        sample->block[i].x=6;
        sample->block[i].y=i-18;
        sample->block[i].lscore=0;
    }
    for(int i=24;i<49;i++){
        sample->block[i].x=(i-24)%5+1;
        sample->block[i].y=(i-24)/5+1;
        sample->block[i].lscore=(i-24)%10;
    }

    QCOMPARE(sample->whetherlink(2,1,2,3),true);
}
void testlink::whetherlink_test_case2(){
    single_modee* sample=new single_modee;
    for(int i=0;i<7;i++){
        sample->block[i].x=i;
        sample->block[i].y=0;
        sample->block[i].lscore=0;
    }
    for(int i=7;i<14;i++){
        sample->block[i].x=i-7;
        sample->block[i].y=6;
        sample->block[i].lscore=0;
    }
    for(int i=14;i<19;i++){
        sample->block[i].x=0;
        sample->block[i].y=i-13;
        sample->block[i].lscore=0;
    }
    for(int i=19;i<24;i++){
        sample->block[i].x=6;
        sample->block[i].y=i-18;
        sample->block[i].lscore=0;
    }
    for(int i=24;i<49;i++){
        sample->block[i].x=(i-24)%5+1;
        sample->block[i].y=(i-24)/5+1;
        sample->block[i].lscore=(i-24)%10;
    }

    QCOMPARE(sample->whetherlink(1,2,1,4),true);
}
void testlink::whetherlink_test_case3(){
    single_modee* sample=new single_modee;
    for(int i=0;i<7;i++){
        sample->block[i].x=i;
        sample->block[i].y=0;
        sample->block[i].lscore=0;
    }
    for(int i=7;i<14;i++){
        sample->block[i].x=i-7;
        sample->block[i].y=6;
        sample->block[i].lscore=0;
    }
    for(int i=14;i<19;i++){
        sample->block[i].x=0;
        sample->block[i].y=i-13;
        sample->block[i].lscore=0;
    }
    for(int i=19;i<24;i++){
        sample->block[i].x=6;
        sample->block[i].y=i-18;
        sample->block[i].lscore=0;
    }
    for(int i=24;i<49;i++){
        sample->block[i].x=(i-24)%5+1;
        sample->block[i].y=(i-24)/5+1;
        sample->block[i].lscore=(i-24)%10;
    }

    QCOMPARE(sample->whetherlink(5,1,5,3),true);
}
void testlink::whetherlink_test_case4(){
    single_modee* sample=new single_modee;
    for(int i=0;i<7;i++){
        sample->block[i].x=i;
        sample->block[i].y=0;
        sample->block[i].lscore=0;
    }
    for(int i=7;i<14;i++){
        sample->block[i].x=i-7;
        sample->block[i].y=6;
        sample->block[i].lscore=0;
    }
    for(int i=14;i<19;i++){
        sample->block[i].x=0;
        sample->block[i].y=i-13;
        sample->block[i].lscore=0;
    }
    for(int i=19;i<24;i++){
        sample->block[i].x=6;
        sample->block[i].y=i-18;
        sample->block[i].lscore=0;
    }
    for(int i=24;i<49;i++){
        sample->block[i].x=(i-24)%5+1;
        sample->block[i].y=(i-24)/5+1;
        sample->block[i].lscore=(i-24)%10;
    }

    QCOMPARE(sample->whetherlink(5,2,5,4),true);
}

void testlink::whetherlink_test_case5(){
    single_modee* sample=new single_modee;
    for(int i=0;i<7;i++){
        sample->block[i].x=i;
        sample->block[i].y=0;
        sample->block[i].lscore=0;
    }
    for(int i=7;i<14;i++){
        sample->block[i].x=i-7;
        sample->block[i].y=6;
        sample->block[i].lscore=0;
    }
    for(int i=14;i<19;i++){
        sample->block[i].x=0;
        sample->block[i].y=i-13;
        sample->block[i].lscore=0;
    }
    for(int i=19;i<24;i++){
        sample->block[i].x=6;
        sample->block[i].y=i-18;
        sample->block[i].lscore=0;
    }
    for(int i=24;i<49;i++){
        sample->block[i].x=(i-24)%5+1;
        sample->block[i].y=(i-24)/5+1;
        sample->block[i].lscore=(i-24)%10;
    }

    QCOMPARE(sample->whetherlink(3,2,3,4),false);
}

