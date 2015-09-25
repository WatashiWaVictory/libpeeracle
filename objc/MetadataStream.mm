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

#import "MetadataStream+Internal.h"

#include "peeracle/Metadata/MetadataStreamInterface.h"

@implementation MetadataStream {
  peeracle::MetadataStreamInterface *_nativeMetadataStream;
}

-(peeracle::MetadataStreamInterface*)nativeMetadataStream {
  return _nativeMetadataStream;
}

/*
-(instancetype)initWithInterface:(id)MetadataStreamInterface {
  if (self = [super init]) {
    _nativeMetadataStream = (peeracle::MetadataStreamInterface*)(MetadataStreamInterface);
  }
  return self;
}
*/

-(uint8_t*)getInitSegment {
  return _nativeMetadataStream->getInitSegment();
}

-(uint32_t) getInitSegmentLength {
  return _nativeMetadataStream->getInitSegmentLength();
}

@end

@implementation MetadataStream (Internal)

-(peeracle::MetadataStreamInterface*)nativeMetadataStream {
  return _nativeMetadataStream;
}

-(instancetype)initWithMetadataStream:(peeracle::MetadataStreamInterface*)metadataStream {
  if (self = [super init]) {
    _nativeMetadataStream = metadataStream;
  }
  return self;
}

@end
