#include "pch.h"
#include "mapping_r.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FunctionTestSuite
{

//////////////////////////////////
// The black box test cases simply check which truck is less full while assuming both have a limiting factor. 
// For example if both are maxed out in weight, it checks which has the lesser capacity. 
// The white box test cases, after implementing, we use to push the test cases. 
// It checks that if a truck has a limiting factor meaning maxed out in weight or capacity, 
// that it is automatically more full than the other truck despite it having more weight or capacity than the value that is maxed out.
//////////////////////////////////

    TEST_CLASS(truckLessFullValidationBlackBox)
    {
        struct Truck firstTruck = { 0 };
        struct Truck secondTruck = { 0 };
    public:     
        //Black box test 1
        TEST_METHOD(EqualWeightAndCapacity)
        {
            firstTruck.currentWeight = 100;    
            firstTruck.currentCapacity = 50;   

            secondTruck.currentWeight = 100;
            secondTruck.currentCapacity = 50;

            //Function should return -1 representing trucks are duplicates/equal
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), -1);
        }
        //Black box test 2
        TEST_METHOD(FirstTruckMoreAvailableSpace)
        {
            //Assume both trucks have reached max capacity but first truck has less weight
            firstTruck.currentWeight = 20;    
            firstTruck.currentCapacity = 50; //FULL CAPACITY

            secondTruck.currentWeight = 50;
            secondTruck.currentCapacity = 50; //FULL CAPACITY

            //Function should return 1 representing first truck has more available space
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 1);
        }
        //Black box test 3
        TEST_METHOD(SecondTruckMoreAvailableSpace)
        {
            //Assume both trucks have reached max capacity second truck has less weight
            firstTruck.currentWeight = 500;    
            firstTruck.currentCapacity = 50; //FULL CAPACITY

            secondTruck.currentWeight = 50;
            secondTruck.currentCapacity = 50; //FULL CAPACITY

            //Function should return 0 representing second truck has more available space
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 0);
        }
        //Black box test 4
        TEST_METHOD(CheckPercentageCalculation)
        {
            //Assume both trucks do not have a limiting factor, checks if the function
            //does the calculations to see which truck has a higher percentage of available sapce
            firstTruck.currentWeight = 500;    
            firstTruck.currentCapacity = 20;   

            secondTruck.currentWeight = 600;
            secondTruck.currentCapacity = 25;

            //Function should return 1 representing first truck has more available space 
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 1);
        }
    };
    TEST_CLASS(truckLessFullValidationWhiteBox)
    {
        struct Truck firstTruck = { 0 };
        struct Truck secondTruck = { 0 };
    public:

        // White box test cases check if limiting factors
        // decide whether truck is full or not
        
        // White box test 1
        TEST_METHOD(Truck2MaxCapacity)
        {
         
            firstTruck.currentWeight = 100;    
            firstTruck.currentCapacity = 20;   

            secondTruck.currentWeight = 50;
            secondTruck.currentCapacity = 50; //FULL CAPACITY

            //Function should return 1 representing truck 1 less full
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 1);
        }
        //White box test 2
        TEST_METHOD(Truck1MaxCapacity)
        {
            
            firstTruck.currentWeight = 50;    
            firstTruck.currentCapacity = 50; //FULL CAPACITY  

            secondTruck.currentWeight = 100;
            secondTruck.currentCapacity = 20;

            //Function should return 0 representing truck 1 is not less full
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 0);
        }
        //White box test 3
        TEST_METHOD(Truck2MaxWeight)
        {
            
            firstTruck.currentWeight = 100;    
            firstTruck.currentCapacity = 40;   

            secondTruck.currentWeight = 1200; //FULL WEIGHT
            secondTruck.currentCapacity = 20;

            //Function should return 1 representing first truck less full
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 1);
        }
        //White box test 4
        TEST_METHOD(Truck1MaxWeight)
        {
            firstTruck.currentWeight = 1200; // FULL WEIGHT    
            firstTruck.currentCapacity = 20;   

            secondTruck.currentWeight = 100;
            secondTruck.currentCapacity = 40;

            //Function should return 0 representing first truck not less full
            Assert::AreEqual(truckLessFull(&firstTruck, &secondTruck), 0);
        }
    };

//////////////////////////////////
//The blackbox test cases check if it is out of bounds with whole numbers while
//the whitebox test cases check with differing floating point numbers to see that
//the size must be exactly .5, 1 or 5 and the weight must be greater than 0
//////////////////////////////////

    TEST_CLASS(validatePackageTests)
    {
        struct Package p = { 0 };

    public:
        // blackbox 1
        TEST_METHOD(validWeight)
        {
            p.weight = 100;
            p.size = 1;
            Assert::AreEqual(validatePackage(&p), 1);
        }

        // blackbox 2
        TEST_METHOD(invalidWeight)
        {
            p.weight = 1201;
            p.size = 1;
            Assert::AreEqual(validatePackage(&p), 0);
        }

        // blackbox 3
        TEST_METHOD(validSize)
        {
            p.weight = 100;
            p.size = 1;
            Assert::AreEqual(validatePackage(&p), 1);
        }

        // blackbox 4
        TEST_METHOD(invalidSize)
        {
            p.weight = 100;
            p.size = 3;
            Assert::AreEqual(validatePackage(&p), 0);
        }

        // whitebox 1
        TEST_METHOD(validWeightEdge)
        {
            p.weight = 1200;
            p.size = 0.5;
            Assert::AreEqual(validatePackage(&p), 1);
        }

        // whitebox 2
        TEST_METHOD(invalidWeightEdge)
        {
            p.weight = 0;
            p.size = 1;
            Assert::AreEqual(validatePackage(&p), 0);
        }

        // whitebox 3
        TEST_METHOD(invalidSizeEdge)
        {
            p.weight = 100;
            p.size = 1.1;
            Assert::AreEqual(validatePackage(&p), 0);
        }

        // whitebox 4
        TEST_METHOD(invalidSizeEdge2)
        {
            p.weight = 0;
            p.size = 4.9;
            Assert::AreEqual(validatePackage(&p), 0);
        }

        //whitebox 5
        TEST_METHOD(negativeWeight)
        {
            p.weight = -1;
            p.size = 1;
            Assert::AreEqual(validatePackage(&p), 0);
        }
    };

    ////////////////////////
    TEST_CLASS(getNumRowsTests)
    {
        struct Map map { 0 };
        struct Map map2;

    public:
        // blackbox 1
        TEST_METHOD(normalMap)
        {
            map.numRows = 5;
            Assert::AreEqual(getNumRows(&map), 5);
        }

        // blackbox 2
        TEST_METHOD(zeroRows)
        {
            map.numRows = 0;
            Assert::AreEqual(getNumRows(&map), 0);
        }

        // blackbox 3
        TEST_METHOD(undefinedNumRows)
        {
            Assert::AreEqual(getNumRows(&map2), 0);
        }

        // whitebox 1
        TEST_METHOD(negativeNumRows)
        {
            map.numRows = -5;
            Assert::AreEqual(getNumRows(&map), 0);
        }

        //// whitebox 2
        TEST_METHOD(largeNumRows)
        {
            map.numRows = 1000;
            Assert::AreEqual(getNumRows(&map), 1000);
        }

        // whitebox 3
        TEST_METHOD(nullptrMap)
        {
            Assert::AreEqual(getNumRows(NULL), 0);
        }
    };

///////////////////////
//The black and white box test cases check what the user inputs
//and ensures that it is a valid destination point on the map
////////////////////////

    TEST_CLASS(validDestinationTest)
    {
        struct Map maps = {
            //0	1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
            //A B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y
            {
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//0
            {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//1
            {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//2
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//3
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//4
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//5
            {1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},	//6
            {1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//7
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//8
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//9
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//10
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//11
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//12
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//13
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//14
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//15
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//16
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//17
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	//18
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//19
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//20
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},	//21
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},	//22
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},	//23
            {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}		//24
            },
            25, 25
        };

    public:

        //Black box test 1
        TEST_METHOD(destinationOutOfColumns)
        {
            int row = 8;
            char col = 'Z';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
        //Black box test 2
        TEST_METHOD(destinationOutOfRows)
        {
            int row = 26;
            char col = 'A';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
        //Black box test 3
        TEST_METHOD(blackLocationWithinMap)
        {
            int row = 13;
            char col = 'J';

            Assert::AreEqual(validDestination(&maps, row, col), 1);
        }
        //Black box test 4
        TEST_METHOD(whiteLocationWithinMap)
        {
            int row = 25;
            char col = 'Y';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
        //White box test 1
        TEST_METHOD(TestWithInvalidDestination)
        {
            int row = 1;
            char col = 'A';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
        //White box test 2
        TEST_METHOD(TestWithValidDestination)
        {
            int row = 1;
            char col = 'E';

            Assert::AreEqual(validDestination(&maps, row, col), 1);
        }
        //White box test 3
        TEST_METHOD(TestWithRowOutOfBounds)
        {
            int row = -1;
            char col = 'A';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
        //White box test 4
        TEST_METHOD(TestWithColomnOutOfBounds)
        {
            int row = 2;
            char col = 'Z';

            Assert::AreEqual(validDestination(&maps, row, col), 0);
        }
    };
////////////////////////
//The test cases simply determine which route length is shorter based on the number of points on the route
////////////////////////
    TEST_CLASS(compareRouteLengthsTest) {
        

    public:
        //Black box test 1 
        TEST_METHOD(T028_CompareEqualLengthRoutes) {
            Route route1{ {}, 10, 'A' }; 
            Route route2{ {}, 10, 'B' }; 

            Assert::AreEqual(0, compareRouteLengths(route1, route2));
        }

        //Black box test 2 
        TEST_METHOD(T029_EdgeCaseWithZeroLengthForBothRoutes) {
            Route route1{ {}, 0, 'A' }; 
            Route route2{ {}, 0, 'B' }; 

            Assert::AreEqual(0, compareRouteLengths(route1, route2));
        }

        //Black box test 3 
        TEST_METHOD(T030_Route1IsShorterThanRoute2) {
            Route route1{ {}, 5, 'A' }; 
            Route route2{ {}, 10, 'B' }; 

            Assert::AreEqual(-1, compareRouteLengths(route1, route2));
        }

        //Black box test 4
        TEST_METHOD(T031_Route1IsLongerThanRoute2) {
            Route route1{ {}, 10, 'A' }; 
            Route route2{ {}, 5, 'B' }; 

            Assert::AreEqual(1, compareRouteLengths(route1, route2));
        }
        
        //White box test 1
        TEST_METHOD(T013_Route1ShorterThanRoute2) {
            Route route1{ {}, 20, 'A' }; 
            Route route2{ {}, 50, 'B' }; 

            Assert::AreEqual(-1, compareRouteLengths(route1, route2));
        }

        //White box test 2
        TEST_METHOD(T014_Route2ShorterThanRoute1) {
            Route route1{ {}, 50, 'A' }; 
            Route route2{ {}, 20, 'B' }; 

            Assert::AreEqual(1, compareRouteLengths(route1, route2));
        }

        //White box test 3
        TEST_METHOD(T015_Route1AndRoute2AreEqualLength) {
            Route route1{ {}, 10, 'A' }; 
            Route route2{ {}, 10, 'B' }; 

            Assert::AreEqual(0, compareRouteLengths(route1, route2));
        }

        //White box test 4
        TEST_METHOD(T016_BothRoutesAreEmpty) {
            Route route1{ {}, 0, 'A' }; 
            Route route2{ {}, 0, 'B' }; 

            Assert::AreEqual(0, compareRouteLengths(route1, route2));
        }
    };
    
    //addPackageTrucks integrates the functions isTruckFull
    TEST_CLASS(IntegrationTestAddPackageToTruck) {
    public:
        TEST_METHOD(TruckFull) {

            //This test sends INVALID truck specs
            //to addPackageToTruck which uses another function to validate a truck first

            struct Truck truck;
            //Reset values for subsequent tests
            truck.currentCapacity = 0;
            truck.currentWeight = 0;
            //

            //Assign new values
            truck.currentCapacity = 60;
            truck.currentWeight = 1300;
            
            struct Package pkg;
            pkg.size = 5;
            pkg.weight = 50;


            Assert::AreEqual(0, addPackageToTruck(&truck, &pkg));
        }

        TEST_METHOD(TruckNotFull) {

            //This test sends VALID truck specs 
            //to addPackageToTruck which uses another function to validate a truck first

            struct Truck truck;
            truck.currentCapacity = 0;
            truck.currentWeight = 0;

            struct Package pkg;
            pkg.size = 5;
            pkg.weight = 50;


            Assert::AreEqual(1, addPackageToTruck(&truck, &pkg));
        }

        TEST_METHOD(TruckOverloaded) {

            //This test sends VALID truck specs
            //to addPackageToTruck which uses another function to validate a truck first
            
            //But adding the package even if it's valid specifications
            //will cause the truck to overflow so it should return 0

            struct Truck truck;

            //Reset values for subsequent tests
            truck.currentCapacity = 0;
            truck.currentWeight = 0;
            //

            truck.currentCapacity = 49;
            truck.currentWeight = 1160;

            struct Package pkg;
            pkg.size = 5;
            pkg.weight = 50;


            Assert::AreEqual(0, addPackageToTruck(&truck, &pkg));
        }

        TEST_METHOD(TruckRightAtCapcity) {

            //This test sends VALID truck specs
            //to addPackageToTruck which uses another function to validate a truck first
            
            //Tests if it successfully adds to truck if the truck is equal to max factors

            struct Truck truck;
            truck.currentCapacity = 0;
            truck.currentWeight = 0;

            struct Package pkg;
            pkg.size = 5;
            pkg.weight = 1200;


            Assert::AreEqual(1, addPackageToTruck(&truck, &pkg));
        }
     
    };

    // Integration test of addPackageToSelectedTruck and addPackageToTruck
    TEST_CLASS(IntegrationTestAddPackageToSelectedTruck) {

    public:
        TEST_METHOD(choiceBlueWithRoomForPkg) {
            // Blue truck is selected and it has capacity
            struct Truck blue = { 0 };
            struct Truck yellow = { 0 };
            struct Truck green = { 0 };

            struct Package p;
            p.size = 1;
            p.weight = 10;
            
            int choice = BLUE;

            Assert::AreEqual(1, addPackageToSelectedTruck(&blue, &yellow, &green, choice, &p));
        }

        TEST_METHOD(choiceBlueWithMaxWeight) {
            // Blue truck is selected but it's maxed out on weight
            struct Truck blue = { 0 };
            struct Truck yellow = { 0 };
            struct Truck green = { 0 };

            blue.currentCapacity = 20;
            blue.currentWeight = MAX_WEIGHT;

            struct Package p;
            p.size = 5;
            p.weight = 10;

            int choice = BLUE;

            Assert::AreEqual(0, addPackageToSelectedTruck(&blue, &yellow, &green, choice, &p));
        }

        TEST_METHOD(choiceBlueWithMaxCapacity) {
            // Blue truck is selected but it's maxed out on space
            struct Truck blue = { 0 };
            struct Truck yellow = { 0 };
            struct Truck green = { 0 };

            blue.currentCapacity = MAX_CAPACITY;
            blue.currentWeight = 20;

            struct Package p;
            p.size = 5;
            p.weight = 10;

            int choice = BLUE;

            Assert::AreEqual(0, addPackageToSelectedTruck(&blue, &yellow, &green, choice, &p));
        }

        TEST_METHOD(choiceBlueWithJustEnoughRoom) {
            // Blue truck is selected but it's maxed out on space
            struct Truck blue = { 0 };
            struct Truck yellow = { 0 };
            struct Truck green = { 0 };

            blue.currentCapacity = MAX_CAPACITY - 5;
            blue.currentWeight = MAX_WEIGHT - 10;

            struct Package p;
            p.size = 5;
            p.weight = 10;

            int choice = BLUE;

            Assert::AreEqual(1, addPackageToSelectedTruck(&blue, &yellow, &green, choice, &p));
        }
    };

    //ValidInput integrates two functions which validate the package specifications and the destination
    TEST_CLASS(IntegrationTestValidInput) {

    public:
        TEST_METHOD(InvalidWeight) {

           

            struct Map baseMap = populateMap();
            struct Package pkg;

            //Valid
            pkg.size = 5;
            //Invalid
            pkg.weight = 1300;

            //Valid
            int row = 8;
            //Valid
            char col = 'Y';

            Assert::AreEqual(0, validInput(&baseMap, row, col, &pkg));
        }

        TEST_METHOD(InvalidSize) {

            struct Map baseMap = populateMap();
            struct Package pkg;

            //Invalid
            pkg.size = 2;
            //Valid
            pkg.weight = 500;

            //Valid
            int row = 8;
            //Valid
            char col = 'Y';

            Assert::AreEqual(0, validInput(&baseMap, row, col, &pkg));
        }

        TEST_METHOD(InvalidCol) {

            struct Map baseMap = populateMap();
            struct Package pkg;

            //Valid
            pkg.size = 5;
            pkg.weight = 500;

            //Valid
            int row = 8;
            //Invalid
            char col = 'Z';

            Assert::AreEqual(0, validInput(&baseMap, row, col, &pkg));
        }

        TEST_METHOD(InvalidRow) {

            struct Map baseMap = populateMap();
            struct Package pkg;

            //Valid
            pkg.size = 5;
            pkg.weight = 500;

            //Invalid
            int row = -1;
            //Valid
            char col = 'Y';

            Assert::AreEqual(0, validInput(&baseMap, row, col, &pkg));
        }

    };


    // Integration test between truckLessFull and isTruckFull
    TEST_CLASS(IntegrationTruckLessFull) {

    public:
        // truck 1 reached max capacity
        TEST_METHOD(truck1Full) {
            struct Truck t1 = { 0 };
            struct Truck t2 = { 0 };
            t1.currentCapacity = MAX_CAPACITY;
            
            Assert::AreEqual(0, truckLessFull(&t1, &t2));
        }

        // truck 2 reached max capacity
        TEST_METHOD(truck2Full) {
            struct Truck t1 = { 0 };
            struct Truck t2 = { 0 };
            t2.currentCapacity = MAX_CAPACITY;

            Assert::AreEqual(1, truckLessFull(&t1, &t2));
        }

        // both trucks are empty
        TEST_METHOD(trucksBothEmpty) {
            struct Truck t1 = { 0 };
            struct Truck t2 = { 0 };

            Assert::AreEqual(-1, truckLessFull(&t1, &t2));
        }

        // both trucks reached max capacity
        TEST_METHOD(trucksBothFull) {
            struct Truck t1 = { 0 };
            struct Truck t2 = { 0 };
            t1.currentCapacity = MAX_CAPACITY;
            t2.currentCapacity = MAX_CAPACITY;

            Assert::AreEqual(-1, truckLessFull(&t1, &t2));
        }
    };
}
