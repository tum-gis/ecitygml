#ifndef ImplicitGeometry_H
#define ImplicitGeometry_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryProperty.d.h"
#include "Envelope.d.h"
#include "Id.d.h"
#include "MimeTypeValue.d.h"
#include "PointProperty.d.h"
#include "TransformationMatrix4x4.d.h"

#include "ImplicitGeometry.d.h"






const Id* ecitygml_ImplicitGeometry_object_id(const ImplicitGeometry* self);

const TransformationMatrix4x4* ecitygml_ImplicitGeometry_transformation_matrix(const ImplicitGeometry* self);

const MimeTypeValue* ecitygml_ImplicitGeometry_mime_type(const ImplicitGeometry* self);

typedef struct ecitygml_ImplicitGeometry_library_object_result {union {DiplomatStringView ok; }; bool is_ok;} ecitygml_ImplicitGeometry_library_object_result;
ecitygml_ImplicitGeometry_library_object_result ecitygml_ImplicitGeometry_library_object(const ImplicitGeometry* self);

const PointProperty* ecitygml_ImplicitGeometry_reference_point(const ImplicitGeometry* self);

const AbstractGeometryProperty* ecitygml_ImplicitGeometry_relative_geometry(const ImplicitGeometry* self);

Envelope* ecitygml_ImplicitGeometry_compute_envelope(const ImplicitGeometry* self);

void ecitygml_ImplicitGeometry_destroy(ImplicitGeometry* self);





#endif // ImplicitGeometry_H
