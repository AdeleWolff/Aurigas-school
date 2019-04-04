#include <vector>
#include "graph.hpp"
#include <string>
#include <boost/algorithm/string.hpp>

using AdjacencyMatrix = std::vector<std::vector<bool> >;

template<class Type>
class Graph
{
    public:
        Graph();

        virtual void input() = 0;
        
        std::size_t size(){};

        void add_vertex()
        {
            int n=adjacency_matrix.size();
            for (int i=0;i<(n+1);i++)
            {
                this->adjacency_matrix[n][i]=0;
                this->adjacency_matrix[i][n]=0;
            }
        };

        void add_edge(std::size_t v1, std::size_t v2)
        {
            int n=adjacency_matrix.size();
            if ((v1>n)||(v2>n))
            {
                return 0;
            }
            else
            {
                this->adjacency_matrix[v1][v2]=1;
                this->adjacency_matrix[v2][v1]=1;
            } 
        };
        void del_vertex();
        void del_edge();

        void output()
        {
            for (int i;i<size;i++)
            {
                for (int j;j<size;j++)
                {
                    std::cout<<adjacency_matrix[i][j]<<" ";
                }
                std::cout<<std::endl;
            }
                
        };

    protected:
        //std::vector<std::vector<Type> > adjacency_matrix;
        AdjacencyMatrix adjacency_matrix;
};

template<class Type>
class MatrixGraph : public Graph<Type>
{
    void input(AdjacencyMatrix am){
        this->adjacency_matrix = am;
    }
};

template<class Type>
class VertexListGraph : public Graph<Type>
{
    void input(std::vector<std::string> v)
    {
        std::vector<int> values;
        for (int i=0;i<v.size();i++)
        {
            boost::algorithm::split(values, v[i], boost::is_any_of(","));
            this->adjacency_matrix[values[0]][values[1]] = 1;
            this->adjacency_matrix[values[1]][values[0]] = 1;
        }
    };
};

template<class Type>
class EdgeListGraph : public Graph<Type>
{
    void input()
    {
        std::vector<int> values;
        for (int i=0;i<v.size();i++)
        {
            boost::algorithm::split(values, v[i], boost::is_any_of(" "));
            boost::algorithm::split(values, v[i], boost::is_any_of(","));
                for(int j=1;j<values.size();j++)
                {
                    this->adjacency_matrix[values[0]][values[j]] = 1;
                    this->adjacency_matrix[values[j]][values[0]] = 1;

                }
        }
    };
    };
};