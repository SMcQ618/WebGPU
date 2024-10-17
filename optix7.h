//
// Created by steph on 9/22/2024.
//

#ifndef RAY_TRACING_OPTIX7_H
#define RAY_TRACING_OPTIX7_H

#pragma once

//optix 7
#include <cuda_runtime.h>
#include <optix.h>
#include <optix_stubs.h>
#include <optix_function_table_definition.h>

#define OPTIX_CHECK( call) {
    OptixResult  res = call;
    if (res != OPTIX_SUCCESS) {
        cout<< stderr << "Optix call (%s) failed with code %d (line %d)\n" << #call << res << __LINE__ << endl;
        exit(2);
    }
}
#endif //RAY_TRACING_OPTIX7_H
