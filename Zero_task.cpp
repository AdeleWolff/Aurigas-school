#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cassert>
void sort_ips(std::vector<std::string> &V, bool ascending)
{
    if (ascending){
        std::sort(V.begin(), V.end(), std::less<std::string>());
    }
    else{
        std::sort(V.begin(), V.end(), std::greater<std::string>());
    }
}
 
bool is_element_at_pos(std::string s, std::string element, int pos){
    std::vector<std::string> split_results;
    boost::split(split_results, s, [](char c){return c == '.';});
    if (split_results[pos] == element)
    {
        return true;
    }
    return false;    
}

void test_1(){
    std::vector<std::string> v;
    v.push_back("1.2.56.4");
    v.push_back("192.2.3.4");
    v.push_back("192.168.3.4");
    v.push_back("4.2.3.56");
    v.push_back("5.56.3.4");
   
    sort_ips(v, false);
        
    assert(v.size() == 5);
    assert(v[0] == "5.56.3.4");
    assert(v[1] == "4.2.3.56");
    assert(v[2] == "192.2.3.4");
    assert(v[3] == "192.168.3.4");
    assert(v[4] == "1.2.56.4");
}


void test_2(){
    std::vector<std::string> v;
    v.push_back("1.2.56.4");
    v.push_back("192.2.3.4");
    v.push_back("192.168.3.4");
    v.push_back("4.2.3.56");
    v.push_back("5.56.3.4");
   
    sort_ips(v, true);
        
    assert(v.size() == 5);
    assert(v[0] == "1.2.56.4");
    assert(v[1] == "192.168.3.4");
    assert(v[2] == "192.2.3.4");
    assert(v[3] == "4.2.3.56");
    assert(v[4] == "5.56.3.4");
}


void test_3(){
    std::vector<std::string> v;
    v.push_back("1.1.1.1");
    //v.push_back("1.1.0.1");
    v.push_back("2.1.1.1");
    v.push_back("3.1.1.1");
   
    std::vector<std::string> v_res;
    for (std::size_t i=0;i < v.size(); i++)
    {
        if ( is_element_at_pos(v[i], "1", 0) )
            {
                v_res.push_back(v[i]);
            }
    }  
   
    assert(v_res.size() == 1);
    assert(v_res[0] == "1.1.1.1");
}


void test_4(){
    std::vector<std::string> v;
    v.push_back("168.1.1.1");
    v.push_back("192.192.1.1");
    v.push_back("3.1.1.192");
   
    std::vector<std::string> v_res;
    for (std::size_t i=0;i < v.size(); i++)
    {
        if ( is_element_at_pos(v[i], "192", 0) )
            {
                v_res.push_back(v[i]);
            }
    }  
   
    assert(v_res.size() == 1);
    assert(v_res[0] == "192.192.1.1");
}


void test_5(){
    std::vector<std::string> v;
    v.push_back("168.192.1.1");
    v.push_back("192.168.1.1");
    v.push_back("3.192.168.192");
    v.push_back("192.168.168.192");
   
    std::vector<std::string> v_res;
    for (std::size_t i=0;i < v.size(); i++)
    {
        if ( is_element_at_pos(v[i], "192", 0) && is_element_at_pos(v[i], "168", 1))
            {
                v_res.push_back(v[i]);
            }
    }  
   
    assert(v_res.size() == 2);
    assert(v_res[0] == "192.168.1.1");
    assert(v_res[1] == "192.168.168.192");
}

void test_6(){
    std::vector<std::string> v;
    v.push_back("168.192.56.1");
    v.push_back("192.168.1.1");
    v.push_back("56.192.168.192");
    v.push_back("192.168.168.192");
   
    std::vector<std::string> v_res;
    for (std::size_t i=0;i < v.size(); i++)
    {
        if ( is_element_at_pos(v[i], "56", 0) || is_element_at_pos(v[i], "56", 1) || is_element_at_pos(v[i], "56", 2) || is_element_at_pos(v[i], "56", 3))
            {
                v_res.push_back(v[i]);
            }
    }  
   
    assert(v_res.size() == 2);
    assert(v_res[0] == "168.192.56.1");
    assert(v_res[1] == "56.192.168.192");
}
 
 
//void print_ips(V){
//}
 
//std::vector<std::string> rand_generation(int n){
//}

 
int main()
{
    int n;
    std::cout<< "Enter the number of IPs adresses" << std::endl;
    std::cin >> n;
    std::string str;
    std::vector<std::string> V;
   
    for (int i=0; i<n; i++)
    {
        std::cin>>str;
        V.push_back(str);
    }
    /*
    std::string IP;
   
    for (int i=0; i<n; i++)
    {
        std::string first = std::to_string(1 + rand() % 255);
        std::string second = std::to_string(1 + rand() % 255);
        std::string third = std::to_string(1 + rand() % 255);
        std::string fouth = std::to_string(1 + rand() % 255);
 
        IP= first + "." + second + "." + third + "." + fouth;
        V.push_back(IP);
 
        std::cout << V[i] << std::endl;
    }
    */
   
    //V.push_back("1.2.56.4");
    //V.push_back("192.2.3.4");
    //V.push_back("192.168.3.4");
    //V.push_back("4.2.3.56");
    //V.push_back("5.56.3.4");
 
    //(1):по порядку
    
    sort_ips(V, false);
    std::cout << std::endl;
 
    for (int i=0; i<n; i++)
    {
        std::cout << V[i] << std::endl;
    }
    
       
    //(2): в обратном порядке
    
    sort_ips(V, true);
    std::cout << std::endl;
 
    for (int i=0; i<n; i++)
    {
        std::cout << V[i] << std::endl;
    }
    
    
    //(3):начинающиеся с 1
    
    std::cout << std::endl; 
    for (int i=0; i<n; i++)
    {
        if (is_element_at_pos(V[i],"1",0))
            {
                std::cout << V[i] << std::endl;
            }
    }    
   
    
   //(4):начинающиеся с 192
    
    std::cout << std::endl;
    for (int i=0; i<n; i++)
    {
        if (is_element_at_pos(V[i],"192",0))
            {
                std::cout << V[i] << std::endl;
            }
    }  
   
    
    //(5):начинающиеся со 192.168
    
    std::cout << std::endl;
    for (int i=0; i<n; i++)
    {
        if (is_element_at_pos(V[i],"192",0) && is_element_at_pos(V[i],"168",1))
            {
                std::cout << V[i] << std::endl;
            }
    }  
    
   
    //(6):те,где есть 56
    
    std::cout << std::endl;
    for (int i=0; i<n; i++)
    {
        if (is_element_at_pos(V[i],"56",0) || is_element_at_pos(V[i],"56",1) || is_element_at_pos(V[i],"56",2) || is_element_at_pos(V[i],"56",3))
            {
                std::cout << V[i] << std::endl;
            }
    }  
    
    test_1();//decrease
    test_2();//increase
    test_3();//1.*
    test_4();//192*.
    test_5();//192.168.*
    test_6();//*56*
}