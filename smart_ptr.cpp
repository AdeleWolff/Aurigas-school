#include <iostream>
#include <cassert>

class A{
    public:
    int data;

    A() : data() {}
    A(int x) : data(x) {}

    void print_out(){
        std::cout << data << std::endl;
    }
};

template<class Type>
struct Shared_ptr {
    Type * get() const {
        if (stored) {
            return stored->ptr;
        }
        return NULL;
    }

    std::size_t count() const {
        if (stored) {
            return stored->count;
        }
        return 0;
    }

    bool empty() const {
        return !get();
    }

    Type& operator*() const {
        assert( !empty() );
        return *get();
    }

    Type* operator->() const {
        assert(stored);
        return stored->ptr;
    }

    Shared_ptr() : stored(NULL) {}

    explicit Shared_ptr(Type* const ptr) : stored(new storage(ptr) ) {}

    Shared_ptr(Shared_ptr const &other) : stored(other.stored) {
        increment();
    }

    Shared_ptr& operator=(Shared_ptr const &other) {
        if (stored != other.stored) {
            decrement();
            stored = other.stored;
            increment();
        }
        return *this;
    }

    ~Shared_ptr() {
        decrement();
    }


private:
    void increment() {
        if (stored) {
            ++stored->count;
        }
    }

    void decrement() {
        if (stored && (--stored->count <= 0)) {
            delete stored->ptr;
            delete stored;
            stored = NULL;
        }
    }

    struct storage {
        explicit storage(Type* const ptr) : ptr(ptr), count(1) {}
        Type* const ptr;
        std::size_t count;
    };

    storage* stored;
};

int main(){
    Shared_ptr<A> ptr(new A(42));
    assert(ptr.count() == 1);
    assert(ptr->data == 42);

    Shared_ptr<A> copy(ptr);
    assert(copy.count() == 2);
    assert(copy->data == 42);

    Shared_ptr<A> empty;
    assert(empty.empty());

    empty = copy;
    assert(empty.count() == 3);
    assert(empty->data == 42);

    empty = Shared_ptr<A>();
    assert(empty.empty());

    Shared_ptr<A> emptyCopy(empty);
    assert(emptyCopy.empty());
}