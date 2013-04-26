#ifndef STREAMBUFFER_H
#define STREAMBUFFER_H

#include <wx/dynarray.h>

WX_DEFINE_ARRAY(void*, StreamBufferArray);

enum BufferType
{
    FIFO,
    //LIFO,
};

// fifo based buffer
class StreamBuffer
{
    public: StreamBuffer();
    public: StreamBuffer(BufferType QueueType, size_t QueueSize);
    public: virtual ~StreamBuffer();

    private: BufferType Type;
    private: StreamBufferArray Queue;
    private: size_t Size;

    public: bool IsEmpty();
    public: bool IsFull();
    // append data to the queue -> data will be freed by Pull() recipient
    public: void Push(void* Data);
    // return pointer to the next data in queue
    // if Detach = true: detach data from the queue -> data needs to be freed by recipient
    // if Detach = false: keep data in queue -> data might be pulled and freed in the meantime by another recipient !!!
    public: void* Pull(bool Detach = true);
    // returns pointer to the data, without deteaching it
    // returns the current number of elements in the queue
    public: size_t GetCount();
};

#endif // STREAMBUFFER_H
