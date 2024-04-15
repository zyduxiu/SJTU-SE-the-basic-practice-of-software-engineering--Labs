#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <QTest>
#include "single_modee.h"
#include "double_mode.h"

class testlink:public QObject
{
    Q_OBJECT
private slots:
    void whetherlink_test_case1();
    void whetherlink_test_case2();
    void whetherlink_test_case3();
    void whetherlink_test_case4();
    void whetherlink_test_case5();
};

#endif // TEST_H
