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

#import "Metadata+Internal.h"
#import "MetadataStream+Internal.h"
#import "objc/DataStream+Internal.h"

#include "peeracle/Metadata/Metadata.h"

@implementation Metadata {
  peeracle::Metadata *_nativeMetadata;
}

- (NSString*) getHash {
  return [NSString stringWithCString:_nativeMetadata->getId().c_str()
                            encoding:[NSString defaultCStringEncoding]];
}

- (void) setHashAlgorithmName:(NSString*)hashAlgorithm {
  _nativeMetadata->setHashAlgorithmName([hashAlgorithm UTF8String]);
}

- (void) setTimecodeScale:(uint32_t)timecodeScale {
  _nativeMetadata->setTimecodeScale(timecodeScale);
}

- (void) setDuration:(double)duration {
  _nativeMetadata->setDuration(duration);
}

- (NSString *)getId {
  return [NSString stringWithCString:_nativeMetadata->getId().c_str() encoding: [NSString defaultCStringEncoding]];
}

- (uint32_t) getMagic {
  return _nativeMetadata->getMagic();
}

- (uint32_t) getVersion {
  return _nativeMetadata->getVersion();
}

- (uint32_t) getTimecodeScale {
  return _nativeMetadata->getTimecodeScale();
}

- (double) getDuration {
  return _nativeMetadata->getDuration();
}

- (NSArray *) getTrackerUrls {
  NSArray *urls = [NSArray array];
  std::vector<std::string> &nativeUrls = _nativeMetadata->getTrackerUrls();
  
  for (std::vector<std::string>::iterator it = nativeUrls.begin(); it != nativeUrls.end(); ++it) {
    std::string nativeUrl = (*it);
    NSString *url = [NSString stringWithCString:nativeUrl.c_str() encoding:[NSString defaultCStringEncoding]];
    urls = [urls arrayByAddingObject:url];
  }
  
  return urls;
}

- (NSArray *) getStreams {
  NSArray *streams = [NSArray array];
  std::vector<peeracle::MetadataStreamInterface*> &nativeStreams = _nativeMetadata->getStreams();
  
  for (std::vector<peeracle::MetadataStreamInterface*>::iterator it = nativeStreams.begin(); it != nativeStreams.end(); ++it) {
    MetadataStream *stream = [[MetadataStream alloc] initWithMetadataStream:(*it)];
    streams = [streams arrayByAddingObject:stream];
  }
  
  return streams;
}

- (NSString *) getHashAlgorithmName {
  return [NSString stringWithCString:_nativeMetadata->getHashAlgorithmName().c_str() encoding:[NSString defaultCStringEncoding]];
}

- (void) addTrackerUrl:(NSString *)url {
  _nativeMetadata->addTracker([url UTF8String]);
}

- (bool) serialize:(DataStream *)dataStream {
  return _nativeMetadata->serialize(reinterpret_cast<peeracle::DataStream*>([dataStream nativeDataStream]));
}

- (bool) unserialize:(DataStream *)dataStream {
  return _nativeMetadata->unserialize(reinterpret_cast<peeracle::DataStream*>([dataStream nativeDataStream]));
}

-(peeracle::MetadataInterface*)nativeMetadata {
  return _nativeMetadata;
}

- (id) init {
  _nativeMetadata = new peeracle::Metadata();
  return self;
}

- (void) dealloc {
  delete _nativeMetadata;
}

@end
