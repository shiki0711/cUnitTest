/*
 * sample.c
 *
 *  Created on: 2016/8/13
 *      Author: emit.yanfeng@gmail.com
 */

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "cmock.h"
#include "cmock_mock.h"


/* declaration of mock functions */
typedef struct {
    unsigned int ui_data;
    char str_data[64];
    unsigned char uc_data;
    signed int si_data;
} T_DATA;
void setUcDaraTrue(T_DATA*);
void setUcDaraFalse(T_DATA*);
void setSiData(T_DATA*, signed int);
void setUiData(T_DATA*, unsigned int);
void setStrData(T_DATA*, const char*);
signed int getSiData(T_DATA*);
const char* getStrData(const T_DATA*);
unsigned int getUiData(const T_DATA*);
unsigned char getUcData(const T_DATA*);

/* definition of mock functions */
CMOCK_NORET_FUNC1(setUcDaraTrue, void, T_DATA*);
CMOCK_NORET_FUNC1(setUcDaraFalse, void, T_DATA*);
CMOCK_NORET_FUNC2(setSiData, void, T_DATA*, signed int);
CMOCK_NORET_FUNC2(setUiData, void, T_DATA*, unsigned int);
CMOCK_NORET_FUNC2(setStrData, void, T_DATA*, const char*);
CMOCK_FUNC1(getSiData, signed int, T_DATA*);
CMOCK_FUNC1(getStrData, const char*, const T_DATA*);
CMOCK_FUNC1(getUiData, unsigned int, const T_DATA*);
CMOCK_FUNC1(getUcData, unsigned char, const T_DATA*);




/*-----------------------------------------------------------------------------------/
 * sample 1
 * basic usage of calling expectation and sequence of mock function
 *----------------------------------------------------------------------------------*/
/* test target function */
void changeUcData(T_DATA* pData) {
    unsigned char current = getUcData(pData);
    (current==0)?setUcDaraTrue(pData):setUcDaraFalse(pData);
}

/*
 * Must use "CMOCK_TESTCASE" macro to define a test driver function
 * and terminate it with "CMOCK_TESTCASE_END" macro
 * */
CMOCK_TESTCASE(test_changeUcData, case1_current_true) {
    T_DATA data;

    /* setup calling expectation */
    CMOCK_EXPECTCALL_FUNCTION(getUcData, expectcall_getUcData);
    /* set calling times expectation of mock */
    CMOCK_EXPECTCALL_TIMES(getUcData, expectcall_getUcData, cmock_expectcalls_eq, 1);
    /* set arg value expectation of mock */
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(getUcData, expectcall_getUcData, 1, &data);
    /* set return value of mock */
    CMOCK_EXPECTCALL_RET_VAL(getUcData, expectcall_getUcData, 1);

    CMOCK_EXPECTCALL_FUNCTION(setUcDaraFalse, expectcall_setUcDaraFalse);
    CMOCK_EXPECTCALL_TIMES(setUcDaraFalse, expectcall_setUcDaraFalse, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setUcDaraFalse, expectcall_setUcDaraFalse, 1, &data);

    /* setup calling sequence */
    CMOCK_EXPECTCALL_SEQUENCE(s1);
    /* calling of setUcDaraFalse must after calling of getUcData */
    CMOCK_EXPECTCALL_ADD(s1, expectcall_getUcData);
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setUcDaraFalse);

    /* call target function */
    changeUcData(&data);
}
CMOCK_TESTCASE_END




/*-----------------------------------------------------------------------------------/
 * sample 2
 * how to setup arg matcher and action hook of mock function
 *----------------------------------------------------------------------------------*/
/* test target function */
signed int setSiAndStrAndReturnSi(T_DATA* pData, signed int si, const char* str) {
    setSiData(pData, si);
    setStrData(pData, str);
    return getSiData(pData);
}

#define TEST_DATA_UI    (10)
#define TEST_DATA_SI    (-10)
/* mock arg matcher callback */
static char argMatcherCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_setSiData_arg_2(
        const char* arg, const char* expection) {
    return (strcmp(arg, expection)==0);
}
/* mock action callback */
static void actionCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_setSiData(T_DATA *pData, signed int si){
    pData->si_data = si;
}
static signed int actionCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_getSiData(T_DATA *pData){
    return pData->si_data;
}

/*
 * Must use "CMOCK_TESTCASE" macro to define a test driver function
 * and terminate it with "CMOCK_TESTCASE_END" macro
 * */
CMOCK_TESTCASE(test_setSiAndStrAndReturnSi, case1_si_eq_100) {
    T_DATA data;
    signed int si = TEST_DATA_SI;
    const char* str = "test_str_of_case1_si_eq_100";

    CMOCK_EXPECTCALL_FUNCTION(setSiData, expectcall_setSiData);
    CMOCK_EXPECTCALL_TIMES(setSiData, expectcall_setSiData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData, 2, si);
    /* set action callback function of mock, this function will called at end of this mock if all expectation matched */
    CMOCK_EXPECTCALL_RET(setSiData, expectcall_setSiData, actionCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_setSiData);

    CMOCK_EXPECTCALL_FUNCTION(setStrData, expectcall_setStrData);
    CMOCK_EXPECTCALL_TIMES(setStrData, expectcall_setStrData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setStrData, expectcall_setStrData, 1, &data);
    /* set arg value expectation callback of mock */
    CMOCK_EXPECTCALL_ARG_MATCHER(setStrData, expectcall_setStrData, 2, argMatcherCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_setSiData_arg_2, str);

    CMOCK_EXPECTCALL_FUNCTION(getSiData, expectcall_getSiData);
    CMOCK_EXPECTCALL_TIMES(getSiData, expectcall_getSiData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(getSiData, expectcall_getSiData, 1, &data);
    /* set action callback function of mock, this function will called at end of this mock if all expectation matched */
    CMOCK_EXPECTCALL_RET(getSiData, expectcall_getSiData, actionCbOf_test_setSiAndStrAndReturnSi_case1_si_eq_100_getSiData);

    /* setup calling sequence */
    CMOCK_EXPECTCALL_SEQUENCE(s1);
    /* calling of setUcDaraFalse must after calling of getUcData */
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setSiData);
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setStrData);
    CMOCK_EXPECTCALL_ADD(s1, expectcall_getSiData);

    /* call target function */
    si = setSiAndStrAndReturnSi(&data, si, str);
    /* return value of target function */
    cmock_ctx_fprintf(stderr, "setSiAndStrAndReturnSi return %d\n", si);
}
CMOCK_TESTCASE_END




/*-----------------------------------------------------------------------------------/
 * sample 3
 * controlling multi sequence
 *----------------------------------------------------------------------------------*/
/* test target function */
void setStrAndSiOrUiAndUcTrue(T_DATA* pData, const char* str, signed int si, unsigned int ui) {
    setStrData(pData, str);
    int r = time(NULL)%2;
    cmock_ctx_fprintf(stderr, "%s r %d\n", __func__, r);
    if(r == 0){
        setSiData(pData, si);
    }else{
        setUiData(pData, ui);
    }
    setUcDaraTrue(pData);
}
/* global variable for calling expectation and sequence context */
static CMOCK_S_SEQUENCE     *g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData = NULL;
static CMOCK_S_SEQUENCE     *g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData = NULL;
static CMOCK_S_EXPECT_CALL  *g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData = NULL;
static CMOCK_S_EXPECT_CALL  *g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData = NULL;
/* mock action callback */
static void actionCbOf_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData(T_DATA *pData, signed int si){
    CMOCK_EXPECTCALL_DEL(*g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData,
            *g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData);
}
static void actionCbOf_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData(T_DATA *pData, unsigned int ui){
    CMOCK_EXPECTCALL_DEL(*g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData,
            *g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData);
}

/*
 * Must use "CMOCK_TESTCASE" macro to define a test driver function
 * and terminate it with "CMOCK_TESTCASE_END" macro
 * */
CMOCK_TESTCASE(test_setStrAndSiOrUiAndUcTrue, case1_rand) {
    T_DATA data;
    signed int si = -100;
    unsigned int ui = 100;
    const char* str = "test_str_of_case1_rand";

    CMOCK_EXPECTCALL_FUNCTION(setStrData, expectcall_setStrData);
    CMOCK_EXPECTCALL_TIMES(setStrData, expectcall_setStrData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setStrData, expectcall_setStrData, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setStrData, expectcall_setStrData, 2, str);

    CMOCK_EXPECTCALL_FUNCTION(setSiData, expectcall_setSiData);
    CMOCK_EXPECTCALL_TIMES(setSiData, expectcall_setSiData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData, 2, si);
    /* assign calling expectation context to a global variable */
    g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData = &expectcall_setSiData;

    CMOCK_EXPECTCALL_FUNCTION(setUiData, expectcall_setUiData);
    CMOCK_EXPECTCALL_TIMES(setUiData, expectcall_setUiData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setUiData, expectcall_setUiData, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setUiData, expectcall_setUiData, 2, ui);
    /* assign calling expectation context to a global variable */
    g_expect_call_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData = &expectcall_setUiData;

    CMOCK_EXPECTCALL_FUNCTION(setUcDaraTrue, expectcall_setUcDaraTrue);
    CMOCK_EXPECTCALL_TIMES(setUcDaraTrue, expectcall_setUcDaraTrue, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setUcDaraTrue, expectcall_setUcDaraTrue, 1, &data);

    /* setup calling sequence */
    CMOCK_EXPECTCALL_SEQUENCE(s1);
    CMOCK_EXPECTCALL_SEQUENCE(s2);
    /* assign sequence context to a global variable */
    g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData = &s1;
    g_sequence_of_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData = &s2;
    /*
     * There is 2 possible sequences in target function
     * s1: setStrData-->setSiData-->setUcDaraTrue (if time(NULL)%2 is 0)
     * s2: setStrData-->setUiData-->setUcDaraTrue (if time(NULL)%2 is 1)
     */
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setStrData);
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setSiData);
    CMOCK_EXPECTCALL_ADD(s1, expectcall_setUcDaraTrue);
    CMOCK_EXPECTCALL_ADD(s2, expectcall_setStrData);
    CMOCK_EXPECTCALL_ADD(s2, expectcall_setUiData);
    CMOCK_EXPECTCALL_ADD(s2, expectcall_setUcDaraTrue);

    /* Only one sequence will be executed
     * so if setSiData matched, setUiData should be deleted
     * otherwise setSiData should be deleted
     *  */
    CMOCK_EXPECTCALL_RET(setSiData, expectcall_setSiData, actionCbOf_test_setStrAndSiOrUiAndUcTrue_case1_rand_setSiData);
    CMOCK_EXPECTCALL_RET(setUiData, expectcall_setUiData, actionCbOf_test_setStrAndSiOrUiAndUcTrue_case1_rand_setUiData);

    /* call target function */
    setStrAndSiOrUiAndUcTrue(&data, str, si, ui);
}
CMOCK_TESTCASE_END




/*-----------------------------------------------------------------------------------/
 * sample 4
 * do not use a sequence
 *----------------------------------------------------------------------------------*/
/*
 * Must use "CMOCK_TESTCASE" macro to define a test driver function
 * and terminate it with "CMOCK_TESTCASE_END" macro
 * */
CMOCK_TESTCASE(test_setStrAndSiOrUiAndUcTrue, case2_do_not_care_about_sequence) {
    T_DATA data;
    signed int si = -100;
    unsigned int ui = 100;
    const char* str = "test_str_of_case2_do_not_care_about_sequence";

    CMOCK_EXPECTCALL_FUNCTION(setStrData, expectcall_setStrData);
    CMOCK_EXPECTCALL_TIMES(setStrData, expectcall_setStrData, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setStrData, expectcall_setStrData, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setStrData, expectcall_setStrData, 2, str);


    CMOCK_EXPECTCALL_FUNCTION(setUcDaraTrue, expectcall_setUcDaraTrue);
    CMOCK_EXPECTCALL_TIMES(setUcDaraTrue, expectcall_setUcDaraTrue, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setUcDaraTrue, expectcall_setUcDaraTrue, 1, &data);

    /* Assume we don't care about calling of setSiData and setSiData
   callingwe are only interested in calling of setStrData and setUcDaraTrue
     * and we also don't care about the calling sequence
     * so here we don't declare any sequence context
     * */

    /* call target function */
    setStrAndSiOrUiAndUcTrue(&data, str, si, ui);
}
CMOCK_TESTCASE_END




/*-----------------------------------------------------------------------------------/
 * sample 5
 * retire a calling expectation
 *----------------------------------------------------------------------------------*/
/* test target function */
void setSiTwice(T_DATA* pData) {
    setSiData(pData, 1);
    setSiData(pData, 2);
}
/* mock arg matcher callback */
static char argMatcherCbOf_test_setSiTwice_case1_varify_input_gt_0_arg_2(
        signed int arg, signed int expection) {
    return (arg>expection);
}

/*
 * Must use "CMOCK_TESTCASE" macro to define a test driver function
 * and terminate it with "CMOCK_TESTCASE_END" macro
 * */
CMOCK_TESTCASE(test_setSiTwice, case1_varify_input_gt_0) {
    T_DATA data;

    CMOCK_EXPECTCALL_FUNCTION(setSiData, expectcall_setSiData1);
    CMOCK_EXPECTCALL_TIMES(setSiData, expectcall_setSiData1, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData1, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER(setSiData, expectcall_setSiData1, 2, argMatcherCbOf_test_setSiTwice_case1_varify_input_gt_0_arg_2, 0);
    /* Assume we should only varify that 2nd arg of setSiData() is greater than 0
     * so when expectcall_setSiData1 satisfied, make it retired
     * */
    CMOCK_EXPECTCALL_RETIRE_WHEN_MATCHED(setSiData, expectcall_setSiData1);

    CMOCK_EXPECTCALL_FUNCTION(setSiData, expectcall_setSiData2);
    CMOCK_EXPECTCALL_TIMES(setSiData, expectcall_setSiData2, cmock_expectcalls_eq, 1);
    CMOCK_EXPECTCALL_ARG_MATCHER_VAL_EQ(setSiData, expectcall_setSiData2, 1, &data);
    CMOCK_EXPECTCALL_ARG_MATCHER(setSiData, expectcall_setSiData2, 2, argMatcherCbOf_test_setSiTwice_case1_varify_input_gt_0_arg_2, 0);

    /* call target function */
    setSiTwice(&data);
}
CMOCK_TESTCASE_END





/*
 * Must use "CMOCK_TEST_MAIN" macro to define the main function
 * */
CMOCK_TEST_MAIN {
    CMOCK_RUN_TESTCASE(test_changeUcData, case1_current_true);
    CMOCK_RUN_TESTCASE(test_setSiAndStrAndReturnSi, case1_si_eq_100);
    CMOCK_RUN_TESTCASE(test_setStrAndSiOrUiAndUcTrue, case1_rand);
    CMOCK_RUN_TESTCASE(test_setStrAndSiOrUiAndUcTrue, case2_do_not_care_about_sequence);
    CMOCK_RUN_TESTCASE(test_setSiTwice, case1_varify_input_gt_0);
    return 0;
}


