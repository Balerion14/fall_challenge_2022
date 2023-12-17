/**
 * @authors :
 * - Sorann753 (Arthus Doriath)
 * - Balerion14
 * - Snowsdy
 * @date december 2022
 */

#include <gtest/gtest.h>
#include "inc/cinInjector.hpp"

#define TESTING
#include "../src/main.cpp"



//----------------------------------TEST POSITION----------------------------------//
TEST(PositionTest, Constructors) {
    Position p1;
    Position p2(1, 2);
    Position p3(p2);
    Position p4 = p2;

    EXPECT_EQ(p1.x, -1);
    EXPECT_EQ(p1.y, -1);

    EXPECT_EQ(p2.x, 1);
    EXPECT_EQ(p2.y, 2);

    EXPECT_EQ(p3.x, 1);
    EXPECT_EQ(p3.y, 2);

    EXPECT_EQ(p4.x, 1);
    EXPECT_EQ(p4.y, 2);
}



//----------------------------------TEST DISTANCE----------------------------------//
// TEST(DistanceTest, DistanceTest){
//     for(int i = 0; i < 100; i++){
//         Position p1(0, 0);
//         Position p2(i, i);
//         ASSERT_EQ(distance(p1, p2), i*2);

//         Position p3(i, i);
//         Position p4(-i, -i);
//         ASSERT_EQ(distance(p3, p4), i*4);

//         Position p5(1, i);
//         Position p6(1, 0);
//         ASSERT_EQ(distance(p5, p6), i);

//         Position p7(i, 1);
//         Position p8(0, 1);
//         ASSERT_EQ(distance(p7, p8), i);
//     }
// }

TEST(DistanceTest, DistanceCenterTest){
    // test the function int get_distance_center(const int x, const int y, const int width, const int height)
    ASSERT_EQ(get_distance_center(2, 2, 5, 5), 0);
    ASSERT_EQ(get_distance_center(0, 0, 5, 5), 4);
    for(int i = 0; i < 100; i++){
        if(i%2 != 0){
            // on passe les nombres pairs car les carrés d'une longueur pair ont un centre qui n'est pas sur une case
            EXPECT_EQ(get_distance_center(0, 0, i, i), i-1);
        }
        // TODO : add more tests
    }
}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
