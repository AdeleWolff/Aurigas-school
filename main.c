#include <signal.h>
#include <time.h>

#include "test_suite.h"
#include "vector.h"

// g++ -o test .\main.c .\test_suite.c .\test_suite.h .\vector.c .\vector.h

void vectoNewTest(void)
{
    Vector* v;
    int result_status = vector_new(&v, sizeof(int));
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoSizedNewTest(void)
{
     Vector* v;
     int result_status = vector_sized_new(&v, sizeof(int), 100);
     EXPECT_EQ(result_status, STATUS_OK); 
     vector_free(v);
}

//void vectoSetDeleteFunctionTest(void)

void vectoFreeTest(void)
{
    Vector* v;
    int result_status = vector_free(v);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoFillTest(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_fill(v, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoReserveTest(void)
{
    Vector* v;
    int result_status = vector_reserve(v, 100);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoPushBackTest(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_push_back(v, &tmp);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoPopBackTest(void)
{
    Vector* v;
    const_ptr tmp;
    int result_status = vector_pop_back(v, &tmp);    
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoInsertTest(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_insert(v, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoShrinkToFitTest(void)
{
    Vector* v;
    int result_status = vector_shrink_to_fit(v);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}

void vectoCapacityTest(void)
{
    Vector* v;
    size_t tmp=100;
    int result_status = vector_capacity(v, &tmp);
    EXPECT_EQ(result_status, STATUS_OK); 
    vector_free(v);
}





// void expectEqualFail(void) { EXPECT_EQ(5, 10); }

// void expectNotNullFail(void) {
//     int* nullIntPtr = NULL;
//     EXPECT_NOT_NULL(nullIntPtr);
// }

// void expectNullSuccess(void) {
//     double* nullDblPtr = NULL;
//     EXPECT_NULL(nullDblPtr);
// }

// void expectNotEqualSuccess(void) { EXPECT_NEQ(1.0, -2.4); }

// void failOnSigSegvSignal(void) { raise(SIGSEGV); }

// void passOnEmptyTest(void){};

// void failOnSigAbrtSignal(void) { raise(SIGABRT); }

int main() {
    // // srand((unsigned int)time(NULL));
    // // TestSuite* testSuite = newTestSuite();
    // // addTestCase(testSuite, "expect_equal_fail", expectEqualFail);
    // // addTestCase(testSuite, "expect_not_null_fail", expectNotNullFail);
    // // addTestCase(testSuite, "expect_null_success", expectNullSuccess);
    // // addTestCase(testSuite, "expect_not_equal_success", expectNotEqualSuccess);
    // // addTestCase(testSuite, "sigsegv_fail", failOnSigSegvSignal);
    // // addTestCase(testSuite, "sigabrt_fail", failOnSigAbrtSignal);
    // // addTestCase(testSuite, "empty_test_success", passOnEmptyTest);
    // // runTestSuite(testSuite);
    // // destroyTestSuite(testSuite);

    TestSuite* testSuite = newTestSuite();
    addTestCase(testSuite, "new", vectoNewTest);
    addTestCase(testSuite, "sized new", vectoSizedNewTest);
    //addTestCase(testSuite, "", vectoSetDeleteFunctionTest);
    addTestCase(testSuite, "fill", vectoFillTest);
    addTestCase(testSuite, "reserve", vectoReserveTest);
    addTestCase(testSuite, "push abck", vectoPushBackTest);
    addTestCase(testSuite, "pop back", vectoPopBackTest);
    addTestCase(testSuite, "insert", vectoInsertTest);
    addTestCase(testSuite, "shrink to fit", vectoShrinkToFitTest);
    addTestCase(testSuite, "capacity", vectoCapacityTest);
    runTestSuite(testSuite);
    destroyTestSuite(testSuite);
}
