#include "graph.cpp"
#include "gtest/gtest.h" 
#include <gmock/gmock.h>
using ::testing::AtLeast;

MatrixGraph graph1;

std::vector<std::vector<bool> Matrix;
Matrix[0][0]=1;
Matrix[0][1]=1;
Matrix[1][0]=0;
Matrix[0][1]=1;


TEST(TestingMatrizGraph,TestVertex)
{
    graph1.input(Matrix);
    ASSERT_EQ(1, graph1.adjacency_matrix[0][0]);//=
    ASSERT_NE(0, graph1.adjacency_matrix[0][1]);//!=
    ASSERT_LE(0, graph1.adjacency_matrix[1][0]);//<=
    ASSERT_GE(1, graph1.adjacency_matrix[1][1]);//>=
}

class MockVertexListGraph : public VertexListGraph
{
    public:
    MOCK_METHOD1(input, void(std::vector<std::vector<bool>));
};


TEST(TestingMockVertexListGraph,TestVertex)
{
    MockVartexListGraph graph2;
    
    EXPECT_CALL(graph2, in_file_print()).Times(AtLeast(1));
    graph2.input(Matrix);
   

}

int main(int argc, char const *argv[]) 
{ 
 
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS(); 
    return 0; 
}