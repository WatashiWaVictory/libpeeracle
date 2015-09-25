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

#import "objc/public/FileDataStream.h"

#include "objc/FileDataStream+Internal.h"

namespace peeracle {
  FileDataStream::FileDataStream(NSString* path) {
    _bigEndian = true;
    _handle = [NSFileHandle fileHandleForReadingAtPath:path];
    [_handle seekToEndOfFile];
    _handleSize = [_handle offsetInFile];
    [_handle seekToFileOffset:0];
  }
  
  FileDataStream::~FileDataStream() {
    [_handle closeFile];
  }
  
  std::streamsize FileDataStream::length() {
    return _handleSize;
  }
  
  std::streamsize FileDataStream::seek(std::streamsize position) {
    if (_handle == nil) {
      return 0;
    }
    
    if ((unsigned long long)position > _handleSize) {
      [_handle seekToFileOffset:_handleSize];
      return [_handle offsetInFile];
    }
    
    [_handle seekToFileOffset:(unsigned long long)position];
    return (std::streamsize)[_handle offsetInFile];
  }
  
  std::streamsize FileDataStream::tell() {
    return (std::streamsize)[_handle offsetInFile];
  }
  
  std::streamsize FileDataStream::vread(char *buffer, std::streamsize length) {
    if (_handle == nil || length < 1)
      return 0;

    std::streamsize cursor = (std::streamsize)[_handle offsetInFile];
    if (cursor + length > (std::streamsize)_handleSize)
      length = (std::streamsize)_handleSize - cursor;
    
    NSData *read = [_handle readDataOfLength:(NSInteger)length];
    memcpy((void*)buffer, [read bytes], length);
    return length;
  }
  
  std::streamsize FileDataStream::vpeek(char *buffer, std::streamsize length) {
    if (_handle == nil || length < 1)
      return 0;
    
    std::streamsize cursor = (std::streamsize)[_handle offsetInFile];
    if (cursor + length > (std::streamsize)_handleSize)
      length = (std::streamsize)_handleSize - cursor;
    
    NSData *read = [_handle readDataOfLength:(NSInteger)length];
    memcpy((void*)buffer, [read bytes], length);
    [_handle seekToFileOffset:[_handle offsetInFile] - (unsigned long long)length];
    return length;
  }
  
  std::streamsize FileDataStream::vwrite(const char *buffer, std::streamsize length) {
    if (_handle == nil)
      return 0;

    NSString *data = [NSString stringWithUTF8String:buffer];
    NSData *buff = [data dataUsingEncoding:NSUTF8StringEncoding];
    [_handle writeData:buff];
    return length;
  }
};

@implementation FileDataStream {
  peeracle::FileDataStream *_nativeFileDataStream;
}

-(id)initWithFilePath:(NSString*)filePath{
  _nativeFileDataStream = new peeracle::FileDataStream(filePath);
  return [super initWithDataStream:_nativeFileDataStream];
}

-(NSInteger)length {
  return (NSInteger)_nativeFileDataStream->length();
}

-(NSInteger)seek:(NSInteger)position {
  return (NSInteger)_nativeFileDataStream->seek((std::streamsize)position);
}

-(NSInteger)tell {
  return (NSInteger)_nativeFileDataStream->tell();
}

-(NSInteger)vread:(char*)buffer :(NSInteger)length {
  
  return (NSInteger)_nativeFileDataStream->vread(buffer, (std::streamsize)length);
}

-(NSInteger)vpeek:(char*)buffer :(NSInteger)length {
  return (NSInteger)_nativeFileDataStream->vpeek(buffer, (std::streamsize)length);
}

-(NSInteger)vwrite:(char*)buffer :(NSInteger)length {
  return (NSInteger)_nativeFileDataStream->vwrite(buffer, (std::streamsize)length);
}

@end

@implementation FileDataStream (Internal)

- (id) init:(char *)path {
  NSString *file = [NSString stringWithUTF8String:path];
  return [super initWithDataStream:new peeracle::FileDataStream(file)];
}

@end
