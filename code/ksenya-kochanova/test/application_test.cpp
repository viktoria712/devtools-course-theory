/* Copyright 2013 Ksenya Kochanova */

#include <gtest/gtest.h>

#include <string>

#include "library/TempConv_application.h"

using ::testing::internal::RE;

class AppTest: public ::testing::Test {
 protected:
    // NOTE: here you can put your init/deinit code
    // virtual void SetUp() {}
    // virtual void TearDown() {}

    void RunApp(int argc, const char* argv[]) {
        output_ = app_(argc, argv);
    }

    void Check(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    TempConvApp app_;
    std::string output_;
};

TEST_F(AppTest, can_Print_Help_Without_Arguments) {
    int argc = 1;
    const char* argv[] = {"appname"};

    RunApp(argc, argv);

    Check("This is a temperature convertor application\\..*");
}

TEST_F(AppTest, can_Check_Number_Of_Arguments) {
    int argc = 3;
    const char* argv[] = {"appname", "10", "Kelvin"};

    RunApp(argc, argv);

    Check("ERROR: Should be 3 arguments: value, oldunit, newunit\\..*");
}

TEST_F(AppTest, can_Detect_Wrong_Value_Format_for_Celsius) {
    int argc = 4;
    const char* argv[] = {"appname", "-300", "Celsius", "Kelvin"};

    RunApp(argc, argv);

    Check("Wrong data!.*");
}

TEST_F(AppTest, can_Detect_Wrong_Value_Format_for_Kelvin) {
    int argc = 4;
    const char* argv[] = {"appname", "-10", "Kelvin", "Newton"};

    RunApp(argc, argv);

    Check("Wrong data!.*");
}

TEST_F(AppTest, can_Detect_Wrong_Value_Format_for_Newton) {
    int argc = 4;
    const char* argv[] = {"appname", "-100", "Newton", "Kelvin"};

    RunApp(argc, argv);

    Check("Wrong data!.*");
}

TEST_F(AppTest, can_Detect_Wrong_Value_Format_for_Fahrenheit) {
    int argc = 4;
    const char* argv[] = {"appname", "-500", "Celsius", "Kelvin"};

    RunApp(argc, argv);

    Check("Wrong data!.*");
}
TEST_F(AppTest, can_Detect_Wrong_oldUnit_Format) {
    int argc = 4;
    const char* argv[] = {"appname", "10", "jjj", "Kelvin"};

    RunApp(argc, argv);

    Check("Wrong format!");
}

TEST_F(AppTest, can_Detect_Wrong_newUnit_Format) {
    int argc = 4;
    const char* argv[] = {"appname", "10", "Newton", "iii"};

    RunApp(argc, argv);

    Check("Wrong format!");
}

TEST_F(AppTest, can_Convert_Correct_Value_Kelvin_to_Celsius) {
    int argc = 4;
    const char* argv[] = {"appname", "0", "Kelvin", "Celsius"};

    RunApp(argc, argv);

    Check("Result = -273.15");
}

TEST_F(AppTest, can_Convert_Correct_Value_Celsius_Newton) {
    int argc = 4;
    const char* argv[] = {"appname", "0", "Celsius", "Newton"};

    RunApp(argc, argv);

    Check("Result = 1.65");
}

TEST_F(AppTest, can_Convert_Correct_Value_Fahrenheit_Celsius) {
    int argc = 4;
    const char* argv[] = {"appname", "0", "Fahrenheit", "Celsius"};

    RunApp(argc, argv);

    Check("Result = -26.4444");
}

TEST_F(AppTest, can_Convert_Correct_Value_Newton_Fahrenheit) {
    int argc = 4;
    const char* argv[] = {"appname", "0", "Newton", "Fahrenheit"};

    RunApp(argc, argv);

    Check("Result = 57.6");
}
