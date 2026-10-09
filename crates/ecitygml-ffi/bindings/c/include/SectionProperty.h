#ifndef SectionProperty_H
#define SectionProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Section.d.h"

#include "SectionProperty.d.h"






const Section* ecitygml_SectionProperty_object(const SectionProperty* self);

const HRef* ecitygml_SectionProperty_href(const SectionProperty* self);

void ecitygml_SectionProperty_destroy(SectionProperty* self);





#endif // SectionProperty_H
