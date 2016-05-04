/**
 * Copyright (c) 2015 - The CM Authors <legal@clickmatcher.com>
 *   All Rights Reserved.
 *
 * This file is CONFIDENTIAL -- Distribution or duplication of this material or
 * the information contained herein is strictly forbidden unless prior written
 * permission is obtained.
 */
#pragma once
#include <eventql/util/random.h>
#include <eventql/util/io/fileutil.h>

namespace zbase {

template <typename T>
ProtoSSTableSink<T>::ProtoSSTableSink(
    const String& tempdir) :
    output_file_(
        FileUtil::joinPaths(
            tempdir,
            "tmp." + Random::singleton()->hex64() + ".sst")) {}

template <typename T>
void ProtoSSTableSink<T>::open() {
  sstable_writer_ = sstable::SSTableEditor::create(
      output_file_,
      sstable::IndexProvider{},
      nullptr,
      0);
}

template <typename T>
void ProtoSSTableSink<T>::addRow(const String& key, const T& val) {
  Buffer buf;
  msg::encode<T>(val, &buf);

  if (buf.size() > 0) {
    sstable_writer_->appendRow(
        key.data(),
        key.size(),
        buf.data(),
        buf.size());
  }
}

template <typename T>
RefPtr<VFSFile> ProtoSSTableSink<T>::finalize() {
  sstable_writer_->finalize();

  return new io::MmappedFile(
      File::openFile(output_file_, File::O_READ | File::O_AUTODELETE));
}

} // namespace zbase
