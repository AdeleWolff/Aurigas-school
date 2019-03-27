#include <iostream>

class Graph
{
    public:
        int Vertex;
        std::pair Edge(int start_id;int finish_id);
        virtual int add_vertex(int Vertex);
        virtual void add_edge(int start_id,int finish_id);
        virtual void Input()=0;
        void Output();
        void Resize();
    protected:
        std::vector<std::vector<int>> VecGraph;
        int size;
};

class MatrixGraph:public Graph
{
    int add_vertex(int Vertex);
    void add_edge(int start_id,int finish_id);
    void Input();
};

class ListVertexGraph:public Graph
{
    int add_vertex(int Vertex);
    void add_edge(int start_id,int finish_id);
    void Input();
};

class ListEdgeGraph:public Graph
{
    int add_vertex(int Vertex);
    void add_edge(int start_id,int finish_id);
    void Input();
};

void MatrixGraph::Input()
{  
   for(int i=0; i<size; ++i)
   {
      for(int j=0; j<size; ++j)
      {
         if(i>j)
         {
            std::cout<<"Enter 1 for connect "<< i+1 <<" node with "<< j+1 <<" node: ";
            std::cin>>VecGraph[i][j];
         }
         if(i!=j)
         {
             VecGraph[j][i]=VecGraph[i][j];
         }
            
      }
   }
}

void ListEdgeGraph::Input()
{  
   for(int i=0; i<size; ++i)
   {
      for(int j=0; j<size; ++j)
      {
        std::cout<<"Enter 1 for connect ";
        std::cin>>start_id;
        std::cout<<"node with ";
        std::cin>>finish_id;
        VecGraph[start_id][finish_id]=finish_id;
        VecGraph[finish_id][start_id]=start_id;
      }
   }
}

void ListVertexGraph::Input()
{  
   for(int i=0; i<size; ++i)
   {
      for(int j=0; j<size; ++j)
      {
        std::cout<<"Enter 1 for connect ";
        std::cin>>start_id;
        std::cout<<"node with ";
        std::cin>>finish_id;//схоже со списком ребер, только несколько подряд finish_id
        VecGraph[start_id][finish_id]=finish_id;
        VecGraph[finish_id][start_id]=start_id;
      }
   }
}

