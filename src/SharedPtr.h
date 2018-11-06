#ifndef CXX_PRACTICE_SHARED_PTR_H
#define CXX_PRACTICE_SHARED_PTR_H

#include <mutex>
#include <utility>

class RefBlockBase
{
public:
    RefBlockBase() : usr_count(1) {}

    void IncCnt()
    {
        std::lock_guard< std::mutex > lk(mtx);
        ++usr_count;
    }

    bool DecCnt()
    {
        std::lock_guard< std::mutex > lk(mtx);
        if(--usr_count == 0)
        {
            DeleteRef();
            return true;
        }

        return false;
    }

protected:
    virtual void DeleteRef() = 0;

protected:
    size_t usr_count;
    std::mutex mtx;
};

template< typename T >
class RefBlock : public RefBlockBase
{
public:
    RefBlock(T* ptr) : ref_pointer(ptr) {}

    void DeleteRef() override
    {
        delete ref_pointer;
    }

private:
    T* ref_pointer;
};

template< typename T >
class RefBlock< T[] > : public RefBlockBase
{
public:
    RefBlock(T* ptr) : ref_pointer(ptr) {}

    void DeleteRef() override
    {
        delete[] ref_pointer;
    }

private:
    T* ref_pointer;
};

template< typename T >
class SharedPtr
{
public:
    using Type = typename std::remove_extent< T >::type;

    SharedPtr() : pointer(nullptr), ref_block(nullptr) {}

    SharedPtr(Type* ptr)
        : pointer(ptr)
    {
        ref_block = new RefBlock< T >(ptr);
    }

    SharedPtr(const SharedPtr& sp)
    {
        CopyConstruct(sp);
    }

    SharedPtr& operator=(const SharedPtr& sp)
    {
        CopyConstruct(sp);
        return (*this);
    }

    SharedPtr(SharedPtr&& sp)
    {
        MoveConstruct(std::move(sp));
    }

    SharedPtr& operator=(SharedPtr&& sp)
    {
        MoveConstruct(std::move(sp));
        return (*this);
    }

    ~SharedPtr()
    {
        if(ref_block != nullptr && ref_block->DecCnt())
        {
            delete ref_block;
        }
    }

    void Swap(SharedPtr& sp)
    {
        std::swap(pointer, sp.pointer);
        std::swap(ref_block, sp.ref_block);
    }

private:
    void CopyConstruct(const SharedPtr& sp)
    {
        if(sp.ref_block)
        {
            sp.ref_block->IncCnt();
        }

        pointer = sp.pointer;
        ref_block = sp.ref_block;
    }

    void MoveConstruct(SharedPtr&& sp)
    {
        pointer = sp.pointer;
        ref_block = sp.ref_block;

        sp.pointer = nullptr;
        sp.ref_block = nullptr;
    }

private:
    Type* pointer;
    RefBlockBase* ref_block;
};

#endif // CXX_PRACTICE_SHARED_PTR_H