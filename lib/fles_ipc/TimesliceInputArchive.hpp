// Copyright 2015 Jan de Cuveland <cmail@cuveland.de>
/// \file
/// \brief Defines the fles::TimesliceInputArchive class type.
#pragma once

#include "ArchiveDescriptor.hpp"
#include "InputArchive.hpp"

namespace fles
{

class Timeslice;
class StorableTimeslice;

/**
 * \brief The TimesliceInputArchive deserializes timeslice data sets from an
 * input file.
 */
using TimesliceInputArchive =
    InputArchive<Timeslice, StorableTimeslice, ArchiveType::TimesliceArchive>;

} // namespace fles
