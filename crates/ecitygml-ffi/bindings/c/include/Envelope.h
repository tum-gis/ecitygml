#ifndef Envelope_H
#define Envelope_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "DirectPosition.d.h"

#include "Envelope.d.h"






const DirectPosition* ecitygml_Envelope_lower_corner(const Envelope* self);

const DirectPosition* ecitygml_Envelope_upper_corner(const Envelope* self);

double ecitygml_Envelope_size_x(const Envelope* self);

double ecitygml_Envelope_size_y(const Envelope* self);

double ecitygml_Envelope_size_z(const Envelope* self);

double ecitygml_Envelope_volume(const Envelope* self);

bool ecitygml_Envelope_contains(const Envelope* self, const DirectPosition* point);

void ecitygml_Envelope_destroy(Envelope* self);





#endif // Envelope_H
