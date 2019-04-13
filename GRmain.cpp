#include "graph.cpp"
#include "gtest/gtest.h" 
#include <gmock/gmock.h>

MatrixGraph graph1;

std::vector<std::vector<bool> Matrix;
Matrix[0][0]=1;
Matrix[0][1]=1;
Matrix[1][0]=0;
Matrix[0][1]=1;


TEST(TestingMatrizGraph,TestVertex)
{
    graph1.input(Matrix);
    ASSERT_EQ(1, Matrix[0][0]);//=
    ASSERT_NE(0, Matrix[0][1]);//!=
    ASSERT_LE(0, Matrix[1][0]);//<=
    ASSERT_GE(1, Matrix[1][1]);//>=
}

class MockVertexListGraph : public VertexListGraph
{
    public:
    MOCK_METHOD1(input, void(std::vector<std::vector<bool>));
};


TEST(TestingMockVartexListGraph,TestVertex)
{
    MockVartexListGraph graph2;
    graph2.input(Matrix);
    ASSERT_EQ(1, Matrix[0][0]);//=
    ASSERT_NE(0, Matrix[0][1]);//!=
    ASSERT_LE(0, Matrix[1][0]);//<=
    ASSERT_GE(1, Matrix[1][1]);//>=

}


int main(int argc, char const *argv[])
{

    return RUN_ALL_TESTS();
    return 0;
}
