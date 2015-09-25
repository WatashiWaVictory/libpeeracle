/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#import <Foundation/Foundation.h>
#import "objc/public/FileDataStream.h"
#import "objc/DataStream+Internal.h"

#include <fstream>
#include "peeracle/DataStream/DataStream.h"

namespace peeracle {
  class FileDataStream : public DataStream {
   public:
    explicit FileDataStream(NSString *path);
    ~FileDataStream();
    
    std::streamsize length();
    std::streamsize seek(std::streamsize position);
    std::streamsize tell();
    
   public:
    std::streamsize vread(char *buffer, std::streamsize length);
    std::streamsize vpeek(char *buffer, std::streamsize length);
    std::streamsize vwrite(const char *buffer, std::streamsize length);
    
   protected:
    NSInputStream *_stream;
    std::streamsize _cursor;
    std::fstream  _isStream;
    std::streamsize _fileSize;
    
    NSFileHandle *_handle;
    unsigned long long _handleSize;
  };
}

@interface FileDataStream (Internal)

@end
