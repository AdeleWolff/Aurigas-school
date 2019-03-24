#include <signal.h>
#include <time.h>

#include "test_suite.h"
#include "vector.h"

// g++ -o test .\main.c .\test_suite.c .\test_suite.h .\vector.c .\vector.h

//vector_new

void testVectorNew(void)
{
    Vector* v;
    int result_status = vector_new(&v, sizeof(int));
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_EQ(v->size, 0);
    EXPECT_NEQ(v->data, NULL);
    vector_free(v);
}

void testVectorNewBadArgV(void)
{
    Vector* null_ptr = NULL;
    int result_status = vector_new(&null_ptr, sizeof(int));
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

void testVectorNewBadArgSize(void)
{
    Vector* v;
    int result_status = vector_new(&v, 0);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(v);
}

//vector_sized_new

void testVectorSizedNew(void)
{
    Vector* v;
    int result_status = vector_sized_new(&v, sizeof(int), 100);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->size, 0);
    vector_free(v);
}

void testVectorSizeNewBadArgV(void)
{
    Vector* null_ptr = NULL;
    int result_status = vector_sized_new(&null_ptr, sizeof(int), -1);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

void testVectorSizedNewBadArgSize(void)
{
    Vector* v;
    int result_status = vector_sized_new(&v, 0, 100);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(v);
}

//vector_free

void testVectorFree(void)
{
    Vector* v;
    int result_status = vector_free(v);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, 0);
    vector_free(v);
}

void testVectorFreeBadArg(void)
{
    Vector* null_ptr = NULL;
    int result_status = vector_free(null_ptr);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

//vectorFill

void testVectorFill(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_fill(v, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    EXPECT_EQ(v->data[99], tmp);
    vector_free(v);
}

void testVectorFillBadArgV(void)
{
    Vector* null_ptr = NULL;
    int tmp=42;
    int result_status = vector_fill(null_ptr, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

void testVectorFillBadArgCount(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_fill(v, 0, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(v);
}

//vector_reserve

void testVectorReserve(void)
{
    Vector* v;
    int result_status = vector_reserve(v, 100);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->size, 0);
    EXPECT_NEQ(v->data, NULL);
    vector_free(v);
}

//vector_push_back

void testVectoPushBack(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_push_back(v, &tmp);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    EXPECT_EQ(v->data[v->size], tmp);
    vector_free(v);
}

void testVectoPushBackBadArg(void)
{
    Vector* null_ptr = NULL;
    int tmp=42;
    int result_status = vector_push_back(null_ptr, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}


//vector_pop_back

void testVectoPopBack(void)
{
    Vector* v;
    const_ptr tmp;
    int result_status = vector_pop_back(v, &tmp);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    vector_free(v);
}

void testVectoPopBackBadArg(void)
{
    Vector* null_ptr = NULL;
    const_ptr tmp;
    int result_status = vector_pop_back(null_ptr, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

//vector_insert

void testVectorInsert(void)
{
    Vector* v;
    int tmp=42;
    int result_status = vector_insert(v, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    EXPECT_EQ(v->data[99], tmp);
    vector_free(v);
}

void testVectorInsertBadArg(void)
{
    Vector* null_ptr = NULL;
    int tmp=42;
    int result_status = vector_insert(null_ptr, 100, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
}

//vector_shrink_to_fit

void testVectorShrinkToFit(void)
{
    Vector* v;
    int result_status = vector_shrink_to_fit(v);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    vector_free(v);
}

void testVectorShrinkToFitBadArg(void)
{
    Vector* null_ptr = NULL;
    int result_status = vector_shrink_to_fit(null_ptr);
    EXPECT_EQ(result_status, STATUS_OK);
    vector_free(null_ptr);
}

//vector_capacity

void testVectorCapacity(void)
{
    Vector* v;
    size_t tmp=100;
    int result_status = vector_capacity(v, &tmp);
    EXPECT_EQ(result_status, STATUS_OK);
    EXPECT_NEQ(v->data, NULL);
    EXPECT_NEQ(v->size, 0);
    vector_free(v);
}


void testVectorCapacityBadAgr(void)
{
    Vector* null_ptr = NULL;
    size_t tmp=100;
    int result_status = vector_capacity(null_ptr, &tmp);
    EXPECT_EQ(result_status, STATUS_ERROR_BAD_ARG);
    vector_free(null_ptr);
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

    addTestCase(testSuite, "New", testVectorNew);
    addTestCase(testSuite, "NewBadArgV", testVectorNewBadArgV);
    addTestCase(testSuite, "NewBadArgSize", testVectorNewBadArgSize);
    addTestCase(testSuite, "SizedNew", testVectorSizedNew);
    addTestCase(testSuite, "SizeNewBadArgV", testVectorSizeNewBadArgV);
    addTestCase(testSuite, "SizedNewBadArgSize", testVectorSizedNewBadArgSize);
    addTestCase(testSuite, "Free", testVectorFree);
    addTestCase(testSuite, "FreeBadArg", testVectorFreeBadArg);
    addTestCase(testSuite, "Fill", testVectorFill);
    addTestCase(testSuite, "FillBadArgV", testVectorFillBadArgV);
    addTestCase(testSuite, "FillBadArgCount", testVectorFillBadArgCount);
    addTestCase(testSuite, "Reserve", testVectorReserve);
    addTestCase(testSuite, "PushBack", testVectoPushBack);
    addTestCase(testSuite, "PushBackBadArg", testVectoPushBackBadArg);
    addTestCase(testSuite, "PopBack", testVectoPopBack);
    addTestCase(testSuite, "PopBackBadArg", testVectoPopBackBadArg);
    addTestCase(testSuite, "Insert", testVectorInsert);
    addTestCase(testSuite, "InsertBadArg", testVectorInsertBadArg);
    addTestCase(testSuite, "ShrinkToFit", testVectorShrinkToFit);
    addTestCase(testSuite, "ShrinkToFitBadArg", testVectorShrinkToFitBadArg);
    addTestCase(testSuite, "Capacity", testVectorCapacity);
    addTestCase(testSuite, "CapacityBadAgr", testVectorCapacityBadAgr);
    
    runTestSuite(testSuite);
    destroyTestSuite(testSuite);
}
