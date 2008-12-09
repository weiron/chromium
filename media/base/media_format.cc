// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/base/media_format.h"

namespace media {

namespace mime_type {

// Represents a URI, typically used to create a DataSourceInterface.
// Expected keys:
//   kUri             String          The URI
const wchar_t kURI[]                        = L"text/x-uri";

// Represents a generic byte stream, typically from a DataSourceInterface.
// Expected keys:
//   None
const wchar_t kApplicationOctetStream[]     = L"application/octet-stream";

// Represents encoded audio data, typically from an DemuxerStreamInterface.
// Expected keys:
//   None
const wchar_t kMPEGAudio[]                  = L"audio/mpeg";
const wchar_t kAACAudio[]                   = L"audio/aac";

// Represents encoded video data, typically from a DemuxerStreamInterface.
// Expected keys:
//   None
const wchar_t kH264AnnexB[]                 = L"video/x-h264-annex-b";

// Represents decoded audio data, typically from an AudioDecoderInterface.
// Expected keys:
//   kChannels        Integer         Number of audio channels
//   kSampleRate      Integer         Audio sample rate (i.e., 44100)
//   kSampleBits      Integer         Audio bits-per-sample (i.e., 16)
const wchar_t kRawAudio[]                   = L"audio/x-uncompressed";

// Represents decoded video data, typically from a VideoDecoderInterface.
// Other information, such as surface format (i.e., YV12), stride and planes are
// included with the buffer itself and is not part of the MediaFormat.
// Expected keys:
//   kWidth           Integer         Display width of the surface
//   kHeight          Integer         Display height of the surface
const wchar_t kRawVideo[]                   = L"video/x-uncompressed";

// Represents FFmpeg encoded packets, typically from an DemuxerStreamInterface.
// Expected keys:
//   kFfmpegCodecId   Integer         The FFmpeg CodecID identifying the decoder
const wchar_t kFFmpegAudio[]                = L"audio/x-ffmpeg";
const wchar_t kFFmpegVideo[]                = L"video/x-ffmpeg";

}  // namespace mime_type

// Common keys.
const char MediaFormat::kMimeType[]         = "MimeType";
const char MediaFormat::kURI[]              = "Uri";
const char MediaFormat::kSurfaceFormat[]    = "SurfaceFormat";
const char MediaFormat::kSampleRate[]       = "SampleRate";
const char MediaFormat::kSampleBits[]       = "SampleBits";
const char MediaFormat::kChannels[]         = "Channels";
const char MediaFormat::kWidth[]            = "Width";
const char MediaFormat::kHeight[]           = "Height";
const char MediaFormat::kFfmpegCodecId[]    = "FfmpegCodecId";

MediaFormat::MediaFormat() {
}

MediaFormat::~MediaFormat() {
  Clear();
}

bool MediaFormat::Contains(const std::string& key) const {
  return value_map_.find(key) != value_map_.end();
}

void MediaFormat::Clear() {
  for (ValueMap::iterator iter(value_map_.begin());
       iter != value_map_.end(); ++iter)
    delete iter->second;
  value_map_.clear();
}

void MediaFormat::SetAsBoolean(const std::string& key, bool in_value) {
  value_map_[key] = Value::CreateBooleanValue(in_value);
}

void MediaFormat::SetAsInteger(const std::string& key, int in_value) {
  value_map_[key] = Value::CreateIntegerValue(in_value);
}

void MediaFormat::SetAsReal(const std::string& key, double in_value) {
  value_map_[key] = Value::CreateRealValue(in_value);
}

void MediaFormat::SetAsString(const std::string& key,
                              const std::wstring& in_value) {
  value_map_[key] = Value::CreateStringValue(in_value);
}

bool MediaFormat::GetAsBoolean(const std::string& key, bool* out_value) const {
  Value* value = GetValue(key);
  return value != NULL && value->GetAsBoolean(out_value);
}

bool MediaFormat::GetAsInteger(const std::string& key, int* out_value) const {
  Value* value = GetValue(key);
  return value != NULL && value->GetAsInteger(out_value);
}

bool MediaFormat::GetAsReal(const std::string& key, double* out_value) const {
  Value* value = GetValue(key);
  return value != NULL && value->GetAsReal(out_value);
}

bool MediaFormat::GetAsString(const std::string& key,
                              std::wstring* out_value) const {
  Value* value = GetValue(key);
  return value != NULL && value->GetAsString(out_value);
}

Value* MediaFormat::GetValue(const std::string& key) const {
  ValueMap::const_iterator value_iter = value_map_.find(key);
  return (value_iter == value_map_.end()) ? NULL : value_iter->second;
}

}  // namespace media
