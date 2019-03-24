#include "vector.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    byte* data;
    size_t size;
    size_t capacity;
    int size_of_element;
    delete_function deleter;
} VectorImp;

byte* vector_imp_at(Vector* vector, size_t pos){
    VectorImp* vector_imp = (VectorImp*)vector;
    return &(vector->data[pos*(vector_imp->size_of_element)]);
}

/* Creates a new Vector for elements with size `elementSize`. */
int vector_new(Vector** vector, const size_t elementSize)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (elementSize<0)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    return vector_sized_new(vector, elementSize, 0);
    }

/* Creates a new Vector with `count` number of elements preallocated */
int vector_sized_new(Vector** vector, const size_t elementSize,
                            const size_t count)
{
    //BAD_ARG
    if ((elementSize<0) || (count<0))
    {
        return STATUS_ERROR_BAD_ARG;
    }

    void* memory = malloc(elementSize*count);
    VectorImp* vector_imp = (VectorImp*)memory;
    //NO_MEMORY
    if (memory == NULL)
    {
       free(vector_imp);
       return STATUS_ERROR_NO_MEMORY;
    }
    

    vector_imp->data = (byte*)memory;
    vector_imp->size = 0;
    vector_imp->capacity = count;
    vector_imp->size_of_element = elementSize;
    vector_imp->deleter = free;
    *vector = (Vector*)vector_imp;

    return STATUS_OK;

}

/* Sets delete function for an element of vector. The deleter will be called when the
Vector is freed and memory deallocated as well.*/
int vector_set_delete_function(Vector* vector, delete_function deleter)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    VectorImp* vector_imp = (VectorImp*)vector;
    vector_imp->deleter = deleter; 
    return STATUS_OK;
}

/* Frees the memory allocated for the Vector.
If vetor elements contain dynamically-allocated memory, they should be freed by passed `delete_function`.
If `delete_function` is not set it leads to memory leak.*/
int vector_free(Vector* vector)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }
    
    VectorImp* vector_imp = (VectorImp*)vector;
    for(size_t i; i < vector_imp->size; i++){
        vector_imp->deleter(vector_imp_at(vector, i));
    } 
    free(vector->data);
    free(vector);
    return STATUS_OK;
    
}

/* Replaces the content of the vector with value.  */
int vector_fill(Vector* vector, const size_t count, const_ptr value)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }
    
    if (count == 0)
    {
        return STATUS_OK;
    }

    VectorImp* vector_imp = (VectorImp*)vector;

    if (count > vector_imp->capacity) 
    {
        vector_reserve(vector, count*(vector_imp->size_of_element));
        vector_imp->size=count;

    }
     
    if(count>=vector_imp->size)
    {
        vector_imp->size=count;
    }
    
    for(int i = 0; i<count; i++)
    {
        memcpy(vector_imp_at(vector,i),value,vector_imp->size_of_element);  //where,what,how ma
    }
    return STATUS_OK;           
}

/* Increase the capacity of the vector to a value that's greater or equal to new_cap.
If new_cap is greater than the current capacity, new storage is allocated, otherwise the method does nothing. */   
int vector_reserve(Vector* vector, const size_t newCapacity)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }
    
    VectorImp* vector_imp = (VectorImp*)vector;
    if (vector_imp->capacity < newCapacity)
    {
        realloc(vector->data, (vector_imp->size_of_element)*newCapacity);
    }
    //NO_MEMORY
    if (vector_imp->capacity != newCapacity)
    {
        return STATUS_ERROR_NO_MEMORY;
    }
    return STATUS_OK;
}

/* Adds the value pointed by the `element` to the end of the array.
The vector will grow in size automatically if necessary. */    
int vector_push_back(Vector* vector, const_ptr element)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    VectorImp* vector_imp = (VectorImp*)vector;

    if (vector->size)        
    {
           vector_reserve(vector, vector_imp->size_of_element);
    }
    
    //vector->data[vector->size-1]=element;
    memcpy(&vector->data[vector->size-1], &element, vector_imp->size_of_element);//where,what,how ma
    
    return STATUS_OK;
}

/* Removes the last element of the vector.
Calling this function on empty container should lead to error.*/ 
int vector_pop_back(Vector* vector, const_ptr* element)    
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    if (vector->size == 0)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    VectorImp* vector_imp = (VectorImp*)vector;
    void* last_element;
    vector_imp->deleter(vector_imp_at(vector, vector->size-1));
    vector_imp->size--;
    return STATUS_OK;
}

/* Inserts an element in a vector at the given index. */ 
int vector_insert(Vector* vector, const size_t index, const_ptr element)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (index<0)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    VectorImp* vector_imp = (VectorImp*)vector;
    vector_reserve(vector,vector_imp->size_of_element);
    vector_imp->size++;
    memmove(vector + index + 1,vector + index, (vector->size)-index); //where|from|how much
    //vector->data[index-1]=element;
    memcpy(&vector->data[index-1], &element, vector_imp->size_of_element);//where,what,how ma
    return STATUS_OK;
}

/* Requests the removal of unused capacity. */   
int vector_shrink_to_fit(Vector* vector)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    realloc(vector->data, vector->size);
    return STATUS_OK;
}

/* Returns the number of elements that the vector has currently allocated space for. */ 
int vector_capacity(Vector* vector, size_t* capacity)
{
    //BAD_ARG
    if (vector == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    //BAD_ARG
    if (vector->data == NULL)
    {
        return STATUS_ERROR_BAD_ARG;
    }

    VectorImp* vector_imp = (VectorImp*)vector;
    *capacity = vector_imp->capacity;
    return STATUS_OK;
}