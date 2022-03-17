// Copyright (c) 2017-2022, Lawrence Livermore National Security, LLC and other CEED contributors.
// All Rights Reserved. See the top-level LICENSE and NOTICE files for details.
//
// SPDX-License-Identifier: BSD-2-Clause
//
// This file is part of CEED:  http://github.com/ceed

#include <ceed/ceed.h>
#include <ceed/backend.h>
#include <string.h>
#include "ceed-vectorpoisson1dapply.h"

/**
  @brief Set fields for Ceed QFunction applying the 1D Poisson operator
           on a vector system with three components
**/
static int CeedQFunctionInit_Vector3Poisson1DApply(Ceed ceed,
    const char *requested,
    CeedQFunction qf) {
  int ierr;

  // Check QFunction name
  const char *name = "Vector3Poisson1DApply";
  if (strcmp(name, requested))
    // LCOV_EXCL_START
    return CeedError(ceed, CEED_ERROR_UNSUPPORTED,
                     "QFunction '%s' does not match requested name: %s",
                     name, requested);
  // LCOV_EXCL_STOP

  // Add QFunction fields
  const CeedInt dim = 1, num_comp = 3;
  ierr = CeedQFunctionAddInput(qf, "du", num_comp*dim, CEED_EVAL_GRAD);
  CeedChk(ierr);
  ierr = CeedQFunctionAddInput(qf, "qdata", dim*(dim+1)/2, CEED_EVAL_NONE);
  CeedChk(ierr);
  ierr = CeedQFunctionAddOutput(qf, "dv", num_comp*dim, CEED_EVAL_GRAD);
  CeedChk(ierr);

  return CEED_ERROR_SUCCESS;
}

/**
  @brief Register Ceed QFunction for applying the 1D Poisson operator
           on a vector system with three components
**/
CEED_INTERN int CeedQFunctionRegister_Vector3Poisson1DApply(void) {
  return CeedQFunctionRegister("Vector3Poisson1DApply", Vector3Poisson1DApply_loc,
                               1, Vector3Poisson1DApply,
                               CeedQFunctionInit_Vector3Poisson1DApply);
}
