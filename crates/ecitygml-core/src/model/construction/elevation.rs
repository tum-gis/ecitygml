use crate::model::construction::ElevationValue;
use crate::model::construction::values::ElevationReferenceValue;

/// The elevation of a construction relative to a reference level, corresponding to `con:ElevationType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `construction.xsd`).
///
/// The value is an absolute position in a vertical reference system, so like
/// [`Height`](super::Height) it is not changed by `apply_transform` and the related methods.
#[derive(Debug, Clone, PartialEq)]
pub struct Elevation {
    elevation_reference: ElevationReferenceValue,
    elevation_value: ElevationValue,
}

impl Elevation {
    pub fn new(
        elevation_reference: ElevationReferenceValue,
        elevation_value: ElevationValue,
    ) -> Self {
        Self {
            elevation_reference,
            elevation_value,
        }
    }

    pub fn elevation_reference(&self) -> &ElevationReferenceValue {
        &self.elevation_reference
    }

    pub fn set_elevation_reference(&mut self, elevation_reference: ElevationReferenceValue) {
        self.elevation_reference = elevation_reference;
    }

    pub fn elevation_value(&self) -> &ElevationValue {
        &self.elevation_value
    }

    pub fn set_elevation_value(&mut self, elevation_value: ElevationValue) {
        self.elevation_value = elevation_value;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::basic_types::Code;

    #[test]
    fn test_new_and_setters() {
        let mut elevation = Elevation::new(
            Code::new("generalGroundSurface").into(),
            ElevationValue::new(vec![105.3]).expect("should work"),
        );
        assert_eq!(
            elevation.elevation_reference().code().value(),
            "generalGroundSurface"
        );
        assert_eq!(elevation.elevation_value().coordinates(), &[105.3]);

        elevation.set_elevation_reference(Code::new("entrancePoint").into());
        elevation.set_elevation_value(ElevationValue::new(vec![106.0]).expect("should work"));
        assert_eq!(
            elevation.elevation_reference().code().value(),
            "entrancePoint"
        );
        assert_eq!(elevation.elevation_value().coordinates(), &[106.0]);
    }
}
