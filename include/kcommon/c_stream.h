/*
        common stream interface

    (c) livingcreative, 2015

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_util.h"


namespace c_common
{

    // stream seek origin for seek() function call
    enum class SeekOrigin
    {
        Begin,   // new position is absolute position from start of stream
        Current, // new position is offset from current position
        End      // new position is offset from end of stream towards to its start
    };

    // stream operating mode (returned from mode() functions)
    // stream mode determines stream object behaviour and method
    // availability
    //      StreamClosed
    //          Stream is in closed state and doesn't have associated underlying object
    //          All function calls (except mode()) are denied
    //
    //      StreamRead
    //          Stream is read only (calls to write()/seek() are not valid).
    //          It doesn't have size and position (calls to size()/position() are undefined*).
    //          Stream with this mode could represent network reading stream (where size
    //          of data is not limited and position inside stream doesn't matter for
    //          reading)
    //
    //      SequentialRead
    //          Stream is read only (calls to write()/seek() are not valid).
    //          It has certain size and position, so calls to functions size()/position() are
    //          valid.
    //          Stream with this mode could represent read only data source of known size
    //          without ability to freely set reading position
    //
    //      Read
    //          Stream is read only, but can be read randomly (call to write() is invalid, but
    //          call to seek() is allowed)
    //          It has certain size and position, so calls to functions size()/position() are
    //          valid.
    //          Stream with this mode could represent read only data source with random access
    //          (like read only file or block of memory)
    //
    //      StreamWrite
    //          This mode is similar to StreamRead, but for write only streams.
    //          Stream with this mode could represent network writing stream (where size
    //          of data is not limited and position inside stream doesn't matter for
    //          writing). Calls to read()/seek() are invalid. Calls to size()/position() are
    //          undefined*.
    //
    //      SequentialWrite
    //          This mode is similar to SequentialRead, but for write only streams. Calls to
    //          read()/seek() are not valid.
    //          The size and position of stream are known. The behaviour of size is
    //          defined by implementation - it could be expanded on write, or be limited
    //          to predefined value.
    //          Stream with this mode could represent write only data source without ability
    //          to freely set writing position
    //
    //      StreamReadWrite
    //          This mode allows reading and writing from/to stream. Call to seek() is
    //          invalid. Calls to position()/size() are undefined*.
    //          Stream with this mode could represent network socket.
    //
    //      ReadWrite
    //          Full random read/write mode. The only mode where all functions of
    //          stream interface are defined and their calls are valid.
    //          Stream with this mode could represent memory storage or file with
    //          full acess and random read/write.
    //
    //      * undefined means that calls to this functions may generate error or
    //      their result could be irrelevant to the state of the stream.
    enum class StreamMode
    {
        StreamClosed,
        StreamRead,
        SequentialRead,
        Read,
        StreamWrite,
        SequentialWrite,
        StreamReadWrite,
        ReadWrite
    };

    /*
     -------------------------------------------------------------------------------
     streamT<T>
     -------------------------------------------------------------------------------
         basic stream interface template

         stream defines basic interface for data reading and writing
         the underlaying data source/storage could be anything and is
         implementation dependent

         typically stream interface is used to abstract from actual data source
         like disk file, networking socket or memory storage

         primary interface functions are:
            read()     - reads certain amount data from stream
                to     - buffer which will receive data from stream
                size   - the amount of data one wants to read from stream
                result - actual data size read from stream to buffer

                if buffer size is less than requested size the behaviour is undefined and
                memory corruption could occur

                call to read is invalid for write only streams and could lead to
                underlaying implementation error. it should return 0 and keep buffer
                unchanged

                for streams with defined size and position:
                    read begins from current position
                    read always increments current position by the amount of actual
                    data read from stream (by the result of function)
                    in general, it's not possible to read outside defined size of the
                    stream, but certain implementations could define expandable streams
                    for not expandable stream, when position is equals to size read() should
                    return 0 and keep buffer unchanged.

            write()    - writes certain amount of data to stream
                from   - buffer which will be used as source of data
                size   - the amount of data one wants to write to stream
                result - actual data size written to stream

                in general if current stream position is less than current stream size
                data after current position gets overwritten
                stream size is expandable on write, but could be fixed and write out of
                stream bounds could be disallowed

                call to write is invalid for read only streams and could lead to
                underlaying imlementation error. it should return 0 and keep stream state
                unchanged (preserve current position and stream size)

                for streams with defined size and position:
                    write always starts at current position
                    write always increments current position by the amount of actual
                    data written to stream

            seek()     - change current position
                newpos - new position, resulting position is set with respect to origin
                origin - defines how to treat newpos value (see SeekOrigin description)
                result - new absolute position inside stream

                seek is only allowed on streams with defined size and position, seek is
                invalid for sequential modes

                in general seeking to position outside stream size is not allowed
                calling on stream with undefined position could lead to underlaying
                imlementation error. it should return 0 in such case

                it's recommended to avoid tricky calls to seek for getting known values
                such as current position (use position() instead of
                seek(0, SeekOrigin::Current)) and stream size (use size() instead of
                seek(0, SeekOrigin::End))

            mode()     - get current mode of the stream
                result - current stream mode (see StreamMode description)

                table for certain stream modes and valid function calls
                ------------------------------------------------------------------
                mode            | read()  | write() | seek() | position() | size()
                ------------------------------------------------------------------
                StreamRead      | +       | -       | -      | - *        | - *
                SequentialRead  | +       | -       | -      | +          | +
                Read            | +       | -       | +      | +          | +
                StreamWrite     | -       | +       | -      | - *        | - *
                SequentialWrite | -       | +       | -      | +          | +
                StreamReadWrite | +       | +       | -      | - *        | - *
                ReadWrite       | +       | +       | +      | +          | +

                * - on certain stream implementations these calls could be issued
                without any error and return actual data (typically size and position return
                same value with total amount of data read/written)

                typical set of implementations for given mode
                StreamRead      - networking read only socket, pipe or other communication
                SequentialRead  - read only data (file, memory) without random access
                Read            - read only data with random access (file, memory)
                StreamWrite     - networking write only socket, pipe or other communication
                SequentialWrite - write only data (file, memory) without random access
                StreamReadWrite - networking read/write socket, pipe or otther communication
                ReadWrite       - read/write access with random positioning (file, memory)

            position() - get current stream position
                result - current position, if defined, where reads or writes will occur

                for stream modes (StreamRead, StreamWrite, StreamReadWrite) current position
                should be totally irrelevant

                for other modes current position indicates where reading or writing occurs
                read()/write() always move position by the amount of actual data read/written

            size() - get current stream size
                result - current stream size

                for stream modes (StreamRead, StreamWrite, StreamReadWrite) stream size
                should be totally irrelevant

                for other modes:
                    in general read beyond the stream size is not allowed
                    write beyond stream size could expand stream, but also could be prohibited

         T - defines basic data type for stream position and size
    */
    template <typename T>
    class streamT
    {
    public:
        // main stream interface
        virtual T read(void *to, T size) = 0;
        virtual T write(const void *from, T size) = 0;
        virtual T seek(T newpos, SeekOrigin origin = SeekOrigin::Begin) = 0;
        virtual StreamMode mode() const = 0;
        virtual T position() const = 0;
        virtual T size() const = 0;

    protected:
        // utility functions
        static T adjustread(T readamount, T position, T size)
        {
            return c_util::umin(readamount, size - position);
        }

        static T seekposition(T newpos, SeekOrigin origin, T position, T size)
        {
            switch (origin) {
                case SeekOrigin::Begin:
                    if (newpos > size) {
                        return size;
                    } else {
                        return newpos;
                    }

                case SeekOrigin::Current:
                    if (newpos > (size - position)) {
                        return size;
                    } else {
                        return position + newpos;
                    }

                case SeekOrigin::End:
                    if (newpos > size) {
                        return 0;
                    } else {
                        return size - newpos;
                    }
            }

            return position;
        }
    };


    // common stream types
    class CStream : public streamT<size_t>
    {};

} // namespace c_common
